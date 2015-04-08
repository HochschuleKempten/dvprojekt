#define FLT_MAX  3.402823466e+38F

#define NUM_THREADS_X TILE_RES
#define NUM_THREADS_Y TILE_RES
#define NUM_THREADS_PER_TILE (NUM_THREADS_X * NUM_THREADS_Y)

//////////////////////////////////////////////////////////////////////////
// Buffers for tiling shader
Buffer<float4> g_pointLightCenterAndRadiusBuffer	: register(t0);
Buffer<float4> g_spotLightCenterAndRadiusBuffer		: register(t1);

#if(VPLS == 1)
StructuredBuffer<float4> g_VPLCenterAndRadiusBuffer : register(t2);
#endif

#if(NUM_MSAA_SAMPLES <= 1)
Texture2D<float> g_depthTexture : register(t3);
#else
Texture2DMS<float> g_depthTexture : register(t4);
#endif

//////////////////////////////////////////////////////////////////////////
// gpu shared memory

// min and max depth per tile
groupshared uint ldsZMax;
groupshared uint ldsZMin;

// per tile point light list
groupshared uint ldsPointLightIdxCounterA;
groupshared uint ldsPointLightIdxCounterB;
groupshared uint ldsPointLightIdx[2 * MAX_LIGHT_COUNT_PER_TILE];

// per tile spot light list
groupshared uint ldsSpotLightIdxCounterA;
groupshared uint ldsSpotLightIdxCounterB;
groupshared uint ldsSpotLightIdx[2 * MAX_LIGHT_COUNT_PER_TILE];

#if(VPLS)
groupshared uint ldsVPLIdxCounterA;
groupshared uint ldsVPLIdxCounterB;
groupshared uint ldsVPLIdx[2 * MAX_VPL_COUNT_PER_TILE];
#endif

//////////////////////////////////////////////////////////////////////////
// helper functions

// Hessian-normal-form plane equation from three points
float4 CreatePlaneEquation(float4 f4b, float4 f4c)
{
	float4 f4n;

	f4n.xyz = normalize(cross(f4b.xyz, f4c.xyz));
	f4n.w = 0;
	return f4n;
}

// point-plane distance
float GetSignedDistanceFromPlane(float4 f4p, float4 f4eqn)
{
	return dot(f4eqn.xyz, f4p.xyz);
}

#if(NUM_MSAA_SAMPLES <= 1)
void CalculateMinMaxDepthInLds(uint3 uGlobalIdx)
{
	float fOpaqueDepth = g_depthTexture.Load(uint3(uGlobalIdx.x, uGlobalIdx.y, 0)).x;
	float fOpaqueViewPosZ = ConvertProjDepthToView(fOpaqueDepth);
	uint uOpaqueZ = asuint(fOpaqueViewPosZ);

	if (fOpaqueDepth != 0.f)
	{
		InterlockedMax(ldsZMax, uOpaqueZ);
		InterlockedMin(ldsZMin, uOpaqueZ);
	}
}
#endif

#if(NUM_MSAA_SAMPLES > 1)
bool CalculateMinMaxDepthInLdsMSAA(uint uGlobalIdx, uint uDepthBufferNumSamples)
{
	float fMinZForThisPixel = FLT_MAX;
	float fMaxZForThisPixel = 0.f;

	float fOpaqueDepth0 = g_dephtTexture.Load(uint2(uGlobalIdx.x, uGlobalIdx.y), 0).x;
	float fOpaqueViewPosZ0 = ConvertProjDepthToView(fOpaqueDepth0);

	if (fOpaqueDepth0 != 0.f)
	{
		fMaxZForThisPixel = max(fMaxZForThisPixel, fOpaqueViewPosZ0);
		fMinZForThisPixel = min(fMinZForThisPixel, fOpaqueViewPosZ0);
	}

	for (uint uSampleIdx = 1; uSampleIdx < uDepthBufferNumSamples; uSampleIdx++)
	{
		float fOpaqueDepth = g_dephtTexture.Load(uint2(uGlobalIdx.x, uGlobalIdx.y), uSampleIdx).x;
		float fOpaqueViewPosZ = ConvertProjDepthToView(fOpaqueDepth);

		if (fOpaqueDepth != 0.f)
		{
			fMaxZForThisPixel = max(fMaxZForThisPixel, fOpaqueViewPosZ);
			fMinZForThisPixel = min(fMinZForThisPixel, fOpaqueViewPosZ);
		}
	}

	uint uZMaxForThisPixel = asuint(fMaxZForThisPixel);
	uint uZMinForThisPixel = asuint(fMinZForThisPixel);
	InterlockedMax(ldsZMax, uZMaxForThisPixel);
	InterlockedMin(ldsZMin, uZMinForThisPixel);

	return((fMaxZForThisPixel - fMinZForThisPixel) > 50.f);
}
#endif

void ApplyLightCulling(in uint3 uGlobalIdx, in uint uLocalIdxFlattend, in uint3 uGroupIdx, out float fHalfZ)
{
	if (uLocalIdxFlattend == 0)
	{
		ldsZMin = 0x7f7fffff; // FLT_MAX as uint
		ldsZMax = 0;
		ldsPointLightIdxCounterA = 0;
		ldsPointLightIdxCounterB = MAX_LIGHT_COUNT_PER_TILE;
		ldsSpotLightIdxCounterA = 0;
		ldsSpotLightIdxCounterB = MAX_LIGHT_COUNT_PER_TILE;
#if(VPLS)
		ldsVPLIdxCounterA = 0;
		ldsVPLIdxCounterB = MAX_VPL_COUNT_PER_TILE;
#endif
	}

	// construct frustum for current tile
	float4 f4FrustumEqn[4];
	{
		uint uPxm = TILE_RES * uGroupIdx.x;
		uint uPym = TILE_RES * uGroupIdx.y;
		uint uPxp = TILE_RES * (uGroupIdx.x + 1);
		uint uPyp = TILE_RES * (uGroupIdx.y + 1);

		uint uWindowWitdthDivisibleByTileRes = TILE_RES * g_uNumTilesX;
		uint uWindowHeightDivisibkeByTileRes = TILE_RES * g_uNumTilesY;

		// calculate the four corners of the frustum clockwise from top-left
		float4 f4Frustum[4];
		f4Frustum[0] = ConvertProjToView(float4(uPxm / (float)uWindowWitdthDivisibleByTileRes * 2.f - 1.f,
			(uWindowHeightDivisibkeByTileRes - uPym) / (float)uWindowHeightDivisibkeByTileRes * 2.f - 1.f,
			1.f, 1.f));
		f4Frustum[1] = ConvertProjToView(float4(uPxp / (float)uWindowWitdthDivisibleByTileRes * 2.f - 1.f,
			(uWindowHeightDivisibkeByTileRes - uPym) / (float)uWindowHeightDivisibkeByTileRes * 2.f - 1.f,
			1.f, 1.f));
		f4Frustum[2] = ConvertProjToView(float4(uPxp / (float)uWindowWitdthDivisibleByTileRes * 2.f - 1.f,
			(uWindowHeightDivisibkeByTileRes - uPyp) / (float)uWindowHeightDivisibkeByTileRes * 2.f - 1.f,
			1.f, 1.f));
		f4Frustum[3] = ConvertProjToView(float4(uPxm / (float)uWindowWitdthDivisibleByTileRes * 2.f - 1.f,
			(uWindowHeightDivisibkeByTileRes - uPyp) / (float)uWindowHeightDivisibkeByTileRes * 2.f - 1.f,
			1.f, 1.f));

		// create plane equations of the frustum
		for (uint i = 0; i < 4; i++)
		{
			f4FrustumEqn[i] = CreatePlaneEquation(f4Frustum[i], f4Frustum[(i + 1) & 3]);
		}
	}

	GroupMemoryBarrierWithGroupSync();

#if(NUM_MSAA_SAMPLES <= 1)
	CalculateMinMaxDepthInLds(uGlobalIdx);
#else
	uint uDepthBufferWidth, uDepthBufferHeight, uDepthBufferNumSamples;
	g_dephtTexture.GetDimensions(uDepthBufferWidth, uDepthBufferHeight, uDepthBufferNumSamples);
	CalculateMinMaxDepthInLdsMSAA(uGlobalIdx, uDepthBufferNumSamples);
#endif

	GroupMemoryBarrierWithGroupSync();

	float fMaxZ = asfloat(ldsZMax);
	float fMinZ = asfloat(ldsZMin);
	fHalfZ = (fMinZ + fMaxZ) / 2.f;

	// loop over point lights and intersect light bounding spheres with frustum
	for (uint i = uLocalIdxFlattend; i < g_uNumLights; i += NUM_THREADS_PER_TILE)
	{
		float4 f4Center = g_pointLightCenterAndRadiusBuffer[i];
		float fR = f4Center.w;
		f4Center.xyz = mul(float4(f4Center.xyz, 1.f), g_mView).xyz;

		// intersection test
		if ((GetSignedDistanceFromPlane(f4Center, f4FrustumEqn[0]) < fR) &&
			(GetSignedDistanceFromPlane(f4Center, f4FrustumEqn[1]) < fR) &&
			(GetSignedDistanceFromPlane(f4Center, f4FrustumEqn[2]) < fR) &&
			(GetSignedDistanceFromPlane(f4Center, f4FrustumEqn[3]) < fR))
		{
			if (-f4Center.z + fMinZ < fR && f4Center.z - fHalfZ < fR)
			{
				uint uDstIdx = 0;
				InterlockedAdd(ldsPointLightIdxCounterA, 1, uDstIdx);
				ldsPointLightIdx[uDstIdx] = i;
			}
			if (-f4Center.z + fHalfZ < fR && f4Center.z - fMaxZ < fR)
			{
				uint uDstIdx = 0;
				InterlockedAdd(ldsPointLightIdxCounterB, 1, uDstIdx);
				ldsPointLightIdx[uDstIdx] = i;
			}
		}
	}

	// loop over spot lights and intersect light bounding spheres with frustum
	for (uint j = uLocalIdxFlattend; j < g_uNumSpotLights; j += NUM_THREADS_PER_TILE)
	{
		float4 f4Center = g_spotLightCenterAndRadiusBuffer[j];
		float fR = f4Center.w;
		f4Center.xyz = mul(float4(f4Center.xyz, 1.f), g_mView).xyz;

		// intersection test
		if ((GetSignedDistanceFromPlane(f4Center, f4FrustumEqn[0]) < fR) &&
			(GetSignedDistanceFromPlane(f4Center, f4FrustumEqn[1]) < fR) &&
			(GetSignedDistanceFromPlane(f4Center, f4FrustumEqn[2]) < fR) &&
			(GetSignedDistanceFromPlane(f4Center, f4FrustumEqn[3]) < fR))
		{
			if (-f4Center.z + fMinZ < fR && f4Center.z - fHalfZ < fR)
			{
				uint uDstIdx = 0;
				InterlockedAdd(ldsSpotLightIdxCounterA, 1, uDstIdx);
				ldsSpotLightIdx[uDstIdx] = j;
			}
			if (-f4Center.z + fHalfZ < fR && f4Center.z - fMaxZ < fR)
			{
				uint uDstIdx = 0;
				InterlockedAdd(ldsSpotLightIdxCounterB, 1, uDstIdx);
				ldsSpotLightIdx[uDstIdx] = j;
			}
		}
	}
#if(VPLS == 1)
	uint uNumVPLs = min(g_uMaxVPLs, g_uNumVPLs);

	// loop over vpls and intersect light bounding spheres with frustum
	for (uint k = uLocalIdxFlattend; k < uNumVPLs; k += NUM_THREADS_PER_TILE)
	{
		float4 f4Center = g_VPLCenterAndRadiusBuffer[k];
		float fR = f4Center.w;
		f4Center.xyz = mul(float4(f4Center.xyz, 1.f), g_mView).xyz;

		// intersection test
		if ((GetSignedDistanceFromPlane(f4Center, f4FrustumEqn[0]) < fR) &&
			(GetSignedDistanceFromPlane(f4Center, f4FrustumEqn[1]) < fR) &&
			(GetSignedDistanceFromPlane(f4Center, f4FrustumEqn[2]) < fR) &&
			(GetSignedDistanceFromPlane(f4Center, f4FrustumEqn[3]) < fR))
		{
			if (-f4Center.z + fMinZ < fR && f4Center.z - fHalfZ < fR)
			{
				uint uDstIdx = 0;
				InterlockedAdd(ldsVPLIdxCounterA, 1, uDstIdx);
				ldsSpotLightIdx[uDstIdx] = k;
			}
			if (-f4Center.z + fHalfZ < fR && f4Center.z - fMaxZ < fR)
			{
				uint uDstIdx = 0;
				InterlockedAdd(ldsVPLIdxCounterB, 1, uDstIdx);
				ldsSpotLightIdx[uDstIdx] = k;
			}
		}
	}
#endif
}
//////////////////////////////////////////////////////////
