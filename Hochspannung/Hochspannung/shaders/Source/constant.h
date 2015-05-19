//------------------------------------------------------------------
// Constants: Constants for forward+ shaders
//
// Author: Patrick Fleischmann
// Letzte Änderung: 2014-09-11
//-------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
//Constants for light culling
#define TILE_RES 32
#define MAX_LIGHT_COUNT_PER_TILE 272
#define MAX_VPL_COUNT_PER_TILE 1024

//////////////////////////////////////////////////////////////////////////
//Constant for shadows (same as in lightutil.h)
#define MAX_SHADOWCASTING_LIGHT_NUM 24

//////////////////////////////////////////////////////////////////////////
//Constant buffers
cbuffer cbPerObject : register (b0)
{
	matrix g_mWorld : packoffset(c0);
};

cbuffer cbPerCamera : register(b1)
{
	matrix g_mViewProj : packoffset(c0);
};

cbuffer cbPerFrame : register(b2)
{
	matrix g_mView						: packoffset(c0   );
	matrix g_mViewInv					: packoffset(c4	  );
	matrix g_mProjection				: packoffset(c8   );
	matrix g_mProjectionInv				: packoffset(c12   );
	matrix g_mProjectionInvViewport		: packoffset(c16  );
	float4 g_f4AmbientColorUp			: packoffset(c20  );
	float4 g_f4AmbientColorDown			: packoffset(c21  );
	float3 g_f3CameraPos				: packoffset(c22  );
	float  g_fAlphaTest					: packoffset(c22.w);
	uint   g_uNumLights					: packoffset(c23  );
	uint   g_uNumSpotLights				: packoffset(c23.y);
	uint   g_uWindowWidth				: packoffset(c23.z);
	uint   g_uWindowHeight				: packoffset(c23.w);
	uint   g_uMaxNumLightsPerTile		: packoffset(c24  );
	uint   g_uMaxNumElementsPerTile		: packoffset(c24.y);
	uint   g_uNumTilesX					: packoffset(c24.z);
	uint   g_uNumTilesY					: packoffset(c24.w);
	uint   g_uMaxVPLs					: packoffset(c25  );
	uint   g_uMaxNumVPLsPerTile			: packoffset(c25.y);
	uint   g_uMaxNumVPLElementsPerTile	: packoffset(c25.z);
	float  g_fVPLSpotStrength			: packoffset(c25.w);
	float  g_fVPLSpotRadius				: packoffset(c26  );
	float  g_fVPLPointStrength			: packoffset(c26.y);
	float  g_fVPLPointRadius			: packoffset(c26.z);
	float  g_fVPLRemoveBackFaceContrib	: packoffset(c26.w);
	float  g_fVPLColorThreshold			: packoffset(c27  );
	float  g_fVPLBrightnessThreshold	: packoffset(c27.y);
	float  g_fPerFramePad1				: packoffset(c27.z);
	float  g_fPerFramePad2				: packoffset(c27.w);
};

cbuffer cbShadowConstants : register(b3)
{
	matrix g_mPointShadowViewProj[MAX_SHADOWCASTING_LIGHT_NUM][6];
	matrix g_mSpotShadowViewProj[MAX_SHADOWCASTING_LIGHT_NUM];
	float4 g_f4ShadowBias;
	// X: Texel offset from edge, Y: Underscan scale, Z: Z bias for points, W: Z bias for spots
}

cbuffer cbVPLConstants : register(b4)
{
	uint g_uNumVPLs;
	uint g_uVPLPad[3];
}

struct SVPLData
{
	float4 f4Direction;
	float4 f4Color;
	float4 f4SourceLightDirection;
};

//////////////////////////////////////////////////////////////////////////
//Samplers
SamplerState g_Sampler				   : register(s0);
SamplerComparisonState g_ShadowSampler : register(s1);
SamplerState g_pointSampler			   : register(s2);


//////////////////////////////////////////////////////////////////////////
//Helper functions

// convert a point from post-projection space into view space
float4 ConvertProjToView(float4 p)
{
	p = mul(p, g_mProjectionInv);
	p /= p.w;
	return p;
}

// convert a depth value from post-projection space into view space
float ConvertProjDepthToView(float z)
{
	z = 1.f / (z*g_mProjectionInv._34 + g_mProjectionInv._44);
	return z;
}

uint GetTileIndex(float2 ScreenPos)
{
	float fTileRes = (float)TILE_RES;
	uint nTileIdx = floor(ScreenPos.x / fTileRes) + floor(ScreenPos.y / fTileRes)*g_uNumTilesX;
	return nTileIdx;
}

// PerTileLightIndexBuffer layout:
// | HalfZ High Bits | HalfZ Low Bits | Light Count List A | Light Count List B 
// | space for max num lights per tile light indices (List A) | space for max num lights per tile light indices (List B) |
void GetLightListInfo(in Buffer<uint> PerTileLightIndexBuffer, in uint uMaxNumLightsPerTile, in uint uMaxNumElementsPerTile, 
					 in float4 SVPosition, out uint uFirstLightIndex, out uint uNumLights)
{
	uint nTileIndex = GetTileIndex(SVPosition.xy);
	uint nStartIndex = uMaxNumElementsPerTile*nTileIndex;

	// reconstruct fHalfZ
	uint uHalfZBitsHigh = PerTileLightIndexBuffer[nStartIndex];
	uint uHalfZBitsLow = PerTileLightIndexBuffer[nStartIndex + 1];
	uint uHalfZBits = (uHalfZBitsHigh << 16) | uHalfZBitsLow;
	float fHalfZ = asfloat(uHalfZBits);

	float fViewPosZ = ConvertProjDepthToView(SVPosition.z);

	uFirstLightIndex = (fViewPosZ < fHalfZ) ? (nStartIndex + 4) : (nStartIndex + 4 + uMaxNumLightsPerTile);
	uNumLights = (fViewPosZ < fHalfZ) ? PerTileLightIndexBuffer[nStartIndex + 2] : PerTileLightIndexBuffer[nStartIndex + 3];
}

//////////////////////////////////////////////////////////////////////////
// Subsurface scattering
float HalfLambert(float3 f3Vec1, float3 f3Vec2)
{
	float fProduct = dot(f3Vec1, f3Vec2);
	fProduct *= 0.5f;
	fProduct += 0.5f;
	return fProduct;
}

float BlinnPhongSpec(float3 f3Normal, float3 f3LightDir, float fSpecpower)
{
	float3 f3HalfAngle = normalize(f3Normal + f3LightDir);
	return pow(saturate(dot(f3Normal, f3HalfAngle)), fSpecpower);
}

void SubsurfaceScattering(in float4 f4CenterAndRadius, in float3 f3ToLight, in float3 f3LightColor, in float4 float4TexColor,
						  in float fThickValue, in float4 f4SSSBRDFParams, in float4 f4ColorSSS, in float4 f4VertexPos,
						  in float3 f3CamPos, in float3 f3Normal,
						  inout float3 f3LightColorSpecularResult, inout float3 f3LightDiffuseResult)
{
	const float fMaterialThickness = f4SSSBRDFParams.r;
	const float fRimScalar = f4SSSBRDFParams.b;
	const float fExtinctionCoefficientRed = f4ColorSSS.r;
	const float fExtinctionCoefficientGreen = f4ColorSSS.g;
	const float fExtinctionCoefficientBlue = f4ColorSSS.b;
	const float fSpecPower = 1.f;
	const float3 f3SpecColor = f3LightColorSpecularResult;
	const float4 f4TexColor = float4TexColor;
	float3 f3LightDir = normalize(f3ToLight);
	float4 f4LightPos;
	float3 f3LightDirSSS;
	float4 f4FinColor;

	float3 f3EyeVector = normalize(f3CamPos - f4VertexPos.xyz);
	f3LightDirSSS = -f3EyeVector;
	f4LightPos = f4CenterAndRadius;
	f4LightPos.w = 1.f;

	float fAttenuation = 30.f * (1.f / distance(f4LightPos, f4VertexPos));

	const float3 f3Eye = normalize(f3CamPos.xyz - f4VertexPos.xyz);
	float4 f4DotLN = HalfLambert(f3LightDirSSS, f3Normal) * fAttenuation;

	float3 f3IndirectLightComponent = (float3)(fMaterialThickness * max(0, dot(-f3Normal, f3LightDirSSS)));
	f3IndirectLightComponent += HalfLambert(-f3Eye, f3LightDirSSS)*fMaterialThickness;
	f3IndirectLightComponent *= fAttenuation;
	f3IndirectLightComponent.r *= fExtinctionCoefficientRed;
	f3IndirectLightComponent.g *= fExtinctionCoefficientGreen;
	f3IndirectLightComponent.b *= fExtinctionCoefficientBlue;
	f3IndirectLightComponent.rgb *= fThickValue;

	float3 f3Rim = (float3)(1.f - max(0.f, dot(f3Normal, f3Eye)));
	f3Rim *= f3Rim;
	f3Rim *= max(0.f, dot(f3Normal, f3LightDirSSS)) * f3SpecColor;

	f4DotLN *= f4TexColor;

	f4FinColor = f4DotLN + float4(f3IndirectLightComponent, 1.f);
	f4FinColor.a = 1.f;
	f4FinColor.rgb += (f3Rim * fRimScalar * fAttenuation * f4FinColor.a);
	f4FinColor.rgb += (BlinnPhongSpec(f3Normal, f3LightDirSSS, fSpecPower) * fAttenuation * f3SpecColor * f4FinColor.a * .05f);
	f4FinColor.rgb *= f3LightColor;

	float fEdge = max(dot(normalize(f3CamPos - f4VertexPos.xyz), f3Normal), 0);
	[branch]
	if ((fEdge < 0.7f) && (fMaterialThickness > 2.f))
	{
		f3LightDiffuseResult.rgb *= saturate(f3IndirectLightComponent * 0.06666f);
		f3LightColorSpecularResult.rgb *= saturate(f3IndirectLightComponent * 0.06666f);
	}
	else
	{	
 		f3LightDiffuseResult *= f4FinColor.xyz;
 		f3LightColorSpecularResult *= f4FinColor.xyz;
	}
}


