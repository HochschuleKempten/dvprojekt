#include "postconstants.h"

cbuffer cbPerCamera : register(b1)
{
	matrix g_mViewProj : packoffset(c0);
};

Texture2D tex2D[8] : register (t15); 

#if(NUM_MSAA_SAMPLES <= 1)
Texture2D<float> transparentDepthTex : register(t22);
Texture2D<float> opaqueDepthTex : register(t23);
#else
Texture2DMS<float, NUM_MSAA_SAMPLES> transparentDepthTex : register(t22);
Texture2DMS<float, NUM_MSAA_SAMPLES> opaqueDepthTex : register(t23);
#endif

Texture2D godRayTex : register(t24);

struct VS_INPUT_GODRAYS
{
	float4 f4Pos : POSITION;
	float3 f3Normal : NORMAL;
	float2 f2TexCoord : TEXCOORD;
	float3 f3Tangent : TANGENT;
	float3 f3Bitangent : BITANGENT;
};

struct VS_OUTPUT_POSITION_ONLY
{
	float4 f4Pos : SV_POSITION0;
};

struct VS_OUTPUT_GODRAYS
{
	float4 f4Pos : SV_POSITION0;
	float2 f2TexCoord : TEXCOORD0;
	float4 f4LightPos : TEXCOORD1;
};

VS_OUTPUT_GODRAYS VS_GODRAYS(VS_INPUT_GODRAYS input)
{
	VS_OUTPUT_GODRAYS output = (VS_OUTPUT_GODRAYS)0;

	output.f2TexCoord = input.f2TexCoord;
	output.f4Pos = mul(input.f4Pos, World);
	float4 f4LightPosIn = float4(f4GodRayPos.x, -f4GodRayPos.y, f4GodRayPos.z, 1.f);
	f4LightPosIn = mul(f4LightPosIn, World);
	output.f4LightPos = mul(f4LightPosIn, g_mViewProj);
	
	return output;
}


VS_OUTPUT_POSITION_ONLY RenderPositionOnlyVS(VS_INPUT_GODRAYS input)
{
	VS_OUTPUT_POSITION_ONLY output;
	float4 f4WorldPos = mul(float4(input.f4Pos), World);
	output.f4Pos = mul(f4WorldPos, g_mViewProj);
	
	return output;
}

float4 PS_GODRAYS_PRE(VS_OUTPUT_GODRAYS input) : SV_TARGET
{
	float4 f4Color = float4(0.f, 0.f, 0.f, 1.f);
#if(NUM_MSAA_SAMPLES <= 1)
	f4Color.x = opaqueDepthTex.Load(int3((int2)input.f4Pos.xy, 0)).x;
	f4Color.y = transparentDepthTex.Load(int3((int2)input.f4Pos.xy, 0)).x;
#else
	f4Color.x = opaqueDepthTex.Load(int3((int2)input.f4Pos.xy, 0), 0).x;
	f4Color.y = transparentDepthTex.Load(int3((int2)input.f4Pos.xy, 0), 0).x;
#endif

	f4Color.x = f4Color.y < f4Color.x ? f4Color.x : f4Color.y;

	f4Color = float4(1-1000*f4Color.x, 1-1000*f4Color.x, 1-1000*f4Color.x, 1.f);
	f4Color = saturate(f4Color);
	
	return f4Color;
}

float4 PS_GODRAYS_ACCUM(VS_OUTPUT_GODRAYS input) : SV_TARGET
{
	float2 f2LightPos = float2((input.f4LightPos.x*fRcpFrameX) + 0.5f, (input.f4LightPos.y*fRcpFrameY) + 0.5f);
	
	const int iNumSamples = 150;

	float2 f2DeltaTexCoord = float2(input.f2TexCoord - f2LightPos);
	float2 f2texCoord = input.f2TexCoord;
	f2DeltaTexCoord *= 1.f / float(iNumSamples) * fRayDensity;
	float fIllumDecay = 1.f;

	float4 f4SceneColor = tex2D[7].Sample(linearSampler, input.f2TexCoord);
	float4 f4Depth = godRayTex.Sample(pointSampler, input.f2TexCoord);
	
	float4 f4SceneColorCurr = f4SceneColor;
	[unroll(iNumSamples)]
	for (int i = 0; i < iNumSamples; i++)
	{
		f2texCoord -= f2DeltaTexCoord;
		float4 f4Sample = godRayTex.Sample(pointSampler, f2texCoord);
		f4Sample *= fIllumDecay * fRayWeight;
		f4SceneColor += f4Sample;
		fIllumDecay *= fRayDecay;
	}
	
	f4SceneColor *= fRayExposure;
	f4SceneColorCurr += f4Depth * f4SceneColor;
	f4SceneColor.a = 1.f;
	return f4SceneColorCurr;
}