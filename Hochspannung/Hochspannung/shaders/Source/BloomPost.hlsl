#include "postconstants.h"

Texture2D tex2D[9] : register (t15); 

#if(NUM_MSAA_SAMPLES <= 1)
Texture2D<float> transparentDepthTex : register(t26);
Texture2D<float> opaqueDepthTex : register(t24);
#else
Texture2DMS<float, NUM_MSAA_SAMPLES> transparentDepthTex : register(t26);
Texture2DMS<float, NUM_MSAA_SAMPLES> opaqueDepthTex : register(t24);
#endif

Texture2D lumTex  : register(t25);
Texture2D lumTex1 : register(t26);

struct VS_INPUT_BLOOM_POST
{
	float4 f4Pos : POSITION;
	float3 f3Normal : NORMAL;
	float2 f2TexCoord : TEXCOORD;
	float3 f3Tangent : TANGENT;
	float3 f3Bitangent : BITANGENT;
};

struct PS_INPUT_BLOOM_POST
{
	float4 f4Pos : SV_POSITION0;
	float2 f2TexCoord : TEXCOORD0;
	float4 f4VertexPos : TEXCOORD2;
};

PS_INPUT_BLOOM_POST VS_BLOOMTEXTURE(VS_INPUT_BLOOM_POST input)
{
	PS_INPUT_BLOOM_POST output = (PS_INPUT_BLOOM_POST)0;
	output.f2TexCoord = input.f2TexCoord;

	output.f4Pos = mul(input.f4Pos, World);

	return output;
}

PS_INPUT_BLOOM_POST VS_BLOOMBLUR(VS_INPUT_BLOOM_POST input)
{
	PS_INPUT_BLOOM_POST output = (PS_INPUT_BLOOM_POST)0;
	output.f2TexCoord = input.f2TexCoord;

	output.f4Pos = mul(input.f4Pos, World);

	return output;
}

PS_INPUT_BLOOM_POST VS_BLOOMACCUM(VS_INPUT_BLOOM_POST input)
{
	PS_INPUT_BLOOM_POST output = (PS_INPUT_BLOOM_POST)0;
	output.f2TexCoord = input.f2TexCoord;

	output.f4Pos = mul(input.f4Pos, World);

	return output;
}

float4 PS_BLOOMTEXTURE(PS_INPUT_BLOOM_POST input) : SV_TARGET
{
	float4 f4ColorOut = tex2D[7].Sample(linearSampler, input.f2TexCoord);
	float fThreshold = .9;

	return saturate((f4ColorOut - fThreshold) / (1.f - fThreshold));
}

float CalcGaussianWeight(int iSampleDist, float fSigma)
{
	float fG = 1.f / sqrt(2.f * 3.14159 * fSigma * fSigma);
	return(fG * exp(-(iSampleDist * iSampleDist) / (2 * fSigma * fSigma)));
}

float4 Blur(in PS_INPUT_BLOOM_POST input, float2 f2TexScale, float fSigma)
{
	float4 f4Color = 0;
	float2 f2FrameWidth = float2(1.f / fRcpFrameX, 1.f / fRcpFrameY);
	for (int i = -6; i < 6; ++i)
	{
		float fWeight = CalcGaussianWeight(i, fSigma);
		float2 f2TexCoord = input.f2TexCoord;
		f2TexCoord -= (i / f2FrameWidth) * f2TexScale;
		
		float4 f4Sample = tex2D[8].Sample(linearSampler, f2TexCoord);
		f4Color += f4Sample * fWeight;
	}

	return f4Color;
}

float4 BloomBlurH(in PS_INPUT_BLOOM_POST input)
{
	return(Blur(input, float2(1, 0), 1.8f));
}

float4 BloomBlurV(in PS_INPUT_BLOOM_POST input)
{
	return(Blur(input, float2(0, 1), 1.8f));
}

float4 PS_BLOOMBLUR(PS_INPUT_BLOOM_POST input) : SV_TARGET
{
	float4 f4ColorOut = BloomBlurH(input);
	f4ColorOut += BloomBlurV(input);
	f4ColorOut *= 0.5f;
	
	f4ColorOut.w = 1.f;
	return f4ColorOut;
}

float4 AdjustSaturationO(float4 f4Color, float fSaturation, float2 f2TexCoord)
{
	float fGrey = max(dot(f4Color.xyz, float3(0.299f, 0.587f, 0.114f)), 0.0001f);

	return lerp(fGrey, f4Color, fSaturation);
}

float4 AdjustSaturationB(float4 f4Color, float fSaturation)
{
	float fGrey = max(dot(f4Color.xyz, float3(0.299f, 0.587f, 0.114f)), 0.0001f);

	return lerp(fGrey, f4Color, fSaturation);
}

float4 PS_LUMINANCE(PS_INPUT_BLOOM_POST input) : SV_TARGET
{
	float3 f3Color = tex2D[7].Sample(linearSampler, input.f2TexCoord);

	float fLuminance = CalcLuminance(f3Color);

	return float4(fLuminance, 1.f, 1.f, 1.f);
}

float4 PS_ADAPT_LUMINANCE(PS_INPUT_BLOOM_POST input) : SV_TARGET
{
	const float fTau = 1.f;
	float fLastLum = exp(lumTex1.Sample(pointSampler, input.f2TexCoord).x);
	float fCurrentLum = lumTex.Sample(pointSampler, input.f2TexCoord).x;

	float fAdaptedLum = fLastLum + (fCurrentLum - fLastLum) * (1.f - exp(-fTimeDelta * fTau));

	return float4(log(fAdaptedLum), 1.f, 1.f, 1.f);
}

float LinearDepth(in float fZBufferDepth)
{
	return fDoFFar / (fZBufferDepth - fDoFNear);
}

float4 PS_BLOOMACCUM(PS_INPUT_BLOOM_POST input) : SV_TARGET
{
	float fOriginalIntesity = 1.f;
	float fBloomIntesity = 1.3f;
	float fOriginalSaturation = 1.f;
	float fBloomSaturation = 1.3f;

#if(NUM_MSAA_SAMPLES <= 1)
	float fOpaqueDepth = LinearDepth(opaqueDepthTex.Load(int3(input.f4Pos.xy, 0)));
	float fTransparentDepth = LinearDepth(transparentDepthTex.Load(int3(input.f4Pos.xy, 0)));
#else
	float fOpaqueDepth = LinearDepth(opaqueDepthTex.Load(int3(input.f4Pos.xy, 0), 0));
	float fTransparentDepth = LinearDepth(transparentDepthTex.Load(int3(input.f4Pos.xy, 0), 0));
#endif
	
	float fDepth = fTransparentDepth > fOpaqueDepth ? fOpaqueDepth : fTransparentDepth;
	fDepth = 1.f - 1.3*fDepth;

	fBloomIntesity *= (fDepth);
	float4 f4BloomColor = tex2D[8].Sample(linearSampler, input.f2TexCoord) * fBloomIntesity;
	float4 f4OriginalColor = tex2D[7].Sample(linearSampler, input.f2TexCoord) * fOriginalIntesity;

	//float fAvgLuminance = GetAvgLuminance(lumTex, input.f2TexCoord);
	//float fExposure = 0.f;
	//f4OriginalColor.xyz = ToneMap(f4OriginalColor.xyz * fOriginalIntesity, fAvgLuminance, 0, 1.f, fExposure);
	//f4BloomColor.xyz = ToneMap(f4BloomColor.xyz * fBloomIntesity, fAvgLuminance, 0, 1.f, fExposure);
	f4BloomColor = AdjustSaturationB(f4BloomColor, fBloomSaturation) * fBloomIntesity;
	f4OriginalColor = AdjustSaturationO(f4OriginalColor, fOriginalSaturation, input.f2TexCoord) * fOriginalIntesity;
	
	return f4OriginalColor + f4BloomColor;
}