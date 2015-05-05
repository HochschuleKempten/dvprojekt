#include "constant.h"

//////////////////////////////////////////////////////////////////////
// Textures and buffers
RWStructuredBuffer<float4> g_vplPositionBuffer		: register(u0);
RWStructuredBuffer<SVPLData> g_VPLData				: register(u1);

Texture2D	g_RSMDepthAtlas							: register(t0);
Texture2D	g_RSMNormalAtlas						: register(t1);
Texture2D   g_RSMDiffuseAtlas						: register(t2);

StructuredBuffer<float4x4> g_invViewProjMatrices	: register(t3);

#if(SPOT_LIGHTS == 1)
Buffer<float4> g_spotLightCenterAndRadiusBuffer		: register(t4);
Buffer<float4> g_spotLightColorBuffer				: register(t5);
Buffer<float4> g_spotLightSpotParamsBuffer			: register(t6);
#else
Buffer<float4> g_pointLightCenterAndRadiusBuffer	: register(t4);
Buffer<float4> g_pointLightColorBuffer				: register(t5);
#endif

#if(SPOT_LIGHTS == 1)
#define RSM_SIZE 32
#else
#define RSM_SIZE 32
#endif

#define THREAD_DIM 16
#define SAMPLE_WIDTH (RSM_SIZE / THREAD_DIM)

[numthreads(THREAD_DIM, THREAD_DIM, 1)]
void GenerateVPLsCS(uint3 globalIdx : SV_DispatchThreadID)
{
	uint2 uv00 = SAMPLE_WIDTH*globalIdx.xy;

#if(SPOT_LIGHTS == 1)
	uint uiLightIndex = SAMPLE_WIDTH*globalIdx.x / RSM_SIZE;
#else
	uint uiLightIndex = SAMPLE_WIDTH*globalIdx.y / RSM_SIZE;
	uint uiFaceIndex = SAMPLE_WIDTH*globalIdx.x / RSM_SIZE;
#endif
	float3 f3Color = 0.f;
	float3 f3Normal = 0.f;
	float4 f4Position = 1.f;
	uint2 uv = uv00;

	f3Color = g_RSMDiffuseAtlas[uv].rgb;
	f3Normal = ((2 * g_RSMNormalAtlas[uv].rgb) - 1);

	float2 f2ViewportUV = uv.xy;
	f2ViewportUV.xy %= RSM_SIZE;

	float fDepth = g_RSMDepthAtlas[uv].r;

	float fx = (2.f * (((float)f2ViewportUV.x + 0.5f) / RSM_SIZE)) - 1.f;
	float fy = (2.f * -(((float)f2ViewportUV.y + 0.5f) / RSM_SIZE)) + 1.f;

	float4 f4ScreenSpacePos = float4(fx, fy, fDepth, 1.f);

#if(SPOT_LIGHTS == 1)
	uint uiMatrixIndex = uiLightIndex;
#else
	uint uiMatrixIndex = (6 * uiLightIndex) + uiFaceIndex;
#endif

	f4Position = mul(f4ScreenSpacePos, g_invViewProjMatrices[uiMatrixIndex]);
	f4Position.xyz /= f4Position.w;

#if(SPOT_LIGHTS == 1)
	float4 f4SpotParams = g_spotLightSpotParamsBuffer[uiLightIndex];
	float3 f3SpotLightDir;
	f3SpotLightDir.xy = f4SpotParams.xy;
	f3SpotLightDir.z = sqrt(1.f - f3SpotLightDir.x * f3SpotLightDir.x - f3SpotLightDir.y * f3SpotLightDir.y);
	f3SpotLightDir.z = (f4SpotParams.z > 0) ? f3SpotLightDir.z : -f3SpotLightDir.z;

	float4 f4SourceLightCenterAndRadius = g_spotLightCenterAndRadiusBuffer[uiLightIndex];
	float3 f3LightPos = f4SourceLightCenterAndRadius.xyz - f4SourceLightCenterAndRadius.w * f3SpotLightDir;
#else
	float4 f4SourceLightCenterAndRadius = g_pointLightCenterAndRadiusBuffer[uiLightIndex];
	float3 f3LightPos = f4SourceLightCenterAndRadius.xyz;
#endif

	float3 f3SourceLightDir = f4Position.xyz - f3LightPos;
	float fLightDistance = length(f3SourceLightDir);

	{
		float fFallOff = 1.f - fLightDistance / (f4SourceLightCenterAndRadius.w);
		f3Color *= fFallOff;
		
	
		float3 f3NormalizeColor = normalize(f3Color);
		float fDotR = dot(f3NormalizeColor, float3(1.f, 0.f, 0.f));
		float fDotG = dot(f3NormalizeColor, float3(0.f, 1.f, 0.f));
		float fDotB = dot(f3NormalizeColor, float3(0.f, 0.f, 1.f));

		float fThreashold = g_fVPLColorThreshold;
		bool bIsInterestingColor = fDotR > fThreashold || fDotG > fThreashold || fDotB > fThreashold;

		if (bIsInterestingColor)
		{
			float4 f4PosAndRadius;
			float fLightStrength = 1.f;
#if(SPOT_LIGHTS == 1)
			f4PosAndRadius.w = g_fVPLSpotRadius;
			fLightStrength *= g_fVPLSpotStrength;
#else
			f4PosAndRadius.w = g_fVPLPointRadius;
			fLightStrength *= g_fVPLPointStrength;
#endif
			f4PosAndRadius.xyz = f4Position.xyz;
		
#if(SPOT_LIGHTS == 1)
			f3Color = f3Color * g_spotLightColorBuffer[uiLightIndex].rgb * fLightStrength;
#else
			f3Color = f3Color * g_pointLightColorBuffer[uiLightIndex].rgb * fLightStrength;
#endif
			float fColorStrength = length(f3Color);
			if (fColorStrength > g_fVPLBrightnessThreshold)
			{
				SVPLData data;
				data.f4Color = float4(f3Color, 1.f);
				data.f4Direction = float4(f3Normal, 0);

#if(SPOT_LIGHTS == 1)
				data.f4SourceLightDirection = float4(-f3SpotLightDir, 0.f);
#else
				data.f4SourceLightDirection.xyz = normalize(f3SourceLightDir);
				data.f4SourceLightDirection.w = 0.f;
#endif
				uint uiIndex = g_vplPositionBuffer.IncrementCounter();

				g_vplPositionBuffer[uiIndex] = f4PosAndRadius;
				g_VPLData[uiIndex] = data;
			}
		}
	}
}