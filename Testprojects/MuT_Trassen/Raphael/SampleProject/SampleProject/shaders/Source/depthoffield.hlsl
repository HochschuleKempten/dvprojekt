#include "postconstants.h"

Texture2D tex2D[8] : register(t15);

#if(NUM_MSAA_SAMPLES <= 1)
Texture2D<float> transparentDepthTex : register(t22);
Texture2D<float> opaqueDepthTex : register(t23);
#else
Texture2DMS<float, NUM_MSAA_SAMPLES> transparentDepthTex : register(t22);
Texture2DMS<float, NUM_MSAA_SAMPLES> opaqueDepthTex : register(t23);
#endif

Texture2D depthblurTex : register(t24);

// Poisson disc kernel
static const uint uNumDiscSamples = 16;
static const float2 f2DiscKernel[uNumDiscSamples] = {
    float2(0.2069841f, 0.2245269f),
    float2(0.525808f, -0.2310817f),
    float2(0.1383943f, 0.9056122f),
    float2(0.6633009f, 0.5129843f),
    float2(-0.4002792f, 0.3727058f),
    float2(0.07912822f, -0.6512921f),
    float2(-0.7726067f, -0.5151217f),
    float2(-0.3843193f, -0.1494132f),
    float2(-0.9107782f, 0.2500633f),
    float2(0.6940153f, -0.7098927f),
    float2(-0.1964669f, -0.379389f),
    float2(-0.4769286f, 0.1840863f),
    float2(-0.247328f, -0.8798459f),
    float2(0.4206541f, -0.714772f),
    float2(0.5829348f, -0.09794202f),
    float2(0.3691838f, 0.4140642f)
};

struct VS_INPUT_DOF_POST
{
	float4 f4Pos : POSITION;
	float3 f3Normal : NORMAL;
	float2 f2TexCoord : TEXCOORD;
	float3 f3Tangent : TANGENT;
	float3 f3Bitangent : BITANGENT;
};

struct PS_INPUT_DOF_POST
{
	float4 f4Pos : SV_POSITION0;
	float2 f2TexCoord : TEXCOORD0;
	float4 f4VertexPos : TEXCOORD2;
};

PS_INPUT_DOF_POST VS_DOF(VS_INPUT_DOF_POST input)
{
	PS_INPUT_DOF_POST output = (PS_INPUT_DOF_POST)0;
	output.f2TexCoord = input.f2TexCoord;

	output.f4Pos = mul(input.f4Pos, World);

	return output;
}

float BlurFactor(in float fDepth)
{
	const float4 f4DOFDepths = float4(0.003f, 0.006f, 0.001f, 0.08f);//f4DoFParams;
	float f0 = 1.f - saturate((fDepth - f4DOFDepths.x) / max(f4DOFDepths.y - f4DOFDepths.x, 0.00001f));
	float f1 = saturate((fDepth - f4DOFDepths.z) / max(f4DOFDepths.w - f4DOFDepths.z, 0.000001f));
	float fBlur = saturate(f0 + f1);

	return fBlur;
}


float LinearDepth(in float fZBufferDepth)
{
	return fDoFFar / (fZBufferDepth - fDoFNear); 
}


float4 PS_DepthBlurGeneration(PS_INPUT_DOF_POST input) : SV_TARGET
{
#if(NUM_MSAA_SAMPLES <= 1)
	float fOpaqueDepth = LinearDepth(opaqueDepthTex.Load(int3(input.f4Pos.xy, 0)));
	float fTransparentDepth = LinearDepth(transparentDepthTex.Load(int3(input.f4Pos.xy, 0)));
#else
	float fOpaqueDepth = LinearDepth(opaqueDepthTex.Load(int3(input.f4Pos.xy, 0),0));
	float fTransparentDepth = LinearDepth(transparentDepthTex.Load(int3(input.f4Pos.xy, 0),0));
#endif
    
    float fDepth = fTransparentDepth > fOpaqueDepth ? fOpaqueDepth : fTransparentDepth;

	fDepth = 1.f - fDepth;
	
	float fBlur = BlurFactor(fDepth);

	return float4(fDepth, fBlur, 1.f, 1.f);
}

float4 PS_DepthofField(in PS_INPUT_DOF_POST input) : SV_TARGET
{
	float2 f2CenterCoord = input.f2TexCoord;

	float2 f2OffsetConversion = f2rcpFrame;

	float3 f3CenterColor = tex2D[7].Sample(linearSampler, f2CenterCoord).xyz;
	float3 f3ColorSum = f3CenterColor;
	float3 f3TotalContribution = 1.f;

	float2 f2CenterDepthBlur = depthblurTex.Sample(pointSampler, f2CenterCoord).xy;

	float fCenterDepth = f2CenterDepthBlur.x;
	float fCenterBlur = f2CenterDepthBlur.y;

	[branch]
	if(fCenterBlur > 0.f)
	{
		const float fGatherBlurSize = 0.0035f;
		float fCoCSize = fCenterBlur * fGatherBlurSize;
		[loop]
		for (int i = 0; i < uNumDiscSamples; ++i)
		{
			float2 f2KernelVal = f2DiscKernel[i];
			float fOffset = f2KernelVal * fCoCSize;
			float2 f2TapCoord = f2CenterCoord + fOffset + f2OffsetConversion;

			float3 f3TapColor = tex2D[7].SampleLevel(linearSampler, f2TapCoord, fCenterBlur).xyz;

			float2 f2TapDepthBlur = depthblurTex.SampleLevel(pointSampler, f2TapCoord, 0.f).xy;
		
			float fTapDepth = f2TapDepthBlur.x;
			float fTapBlur = f2TapDepthBlur.y;

			float fTabContribution = (f2TapDepthBlur.x > fCenterDepth) ? 1.f : f2TapDepthBlur.y;

			f3ColorSum += f3TapColor * fTabContribution;
			f3TotalContribution += fTabContribution;
		}
	}

	float3 f3FinalColor = f3ColorSum / f3TotalContribution;

	return float4(f3FinalColor, 1.f);
}