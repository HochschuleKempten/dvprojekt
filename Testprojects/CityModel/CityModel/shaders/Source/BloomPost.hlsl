#include "postconstants.h"

Texture2D tex2D[9] : register (t15); 

#if(NUM_MSAA_SAMPLES <= 1)
Texture2D<float> depthTex : register (t24);
#else
Texture2DMS<float, NUM_MSAA_SAMPLES> depthTex : register (t24);
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
	float fThreshold = 0.6f;

	return saturate((f4ColorOut - fThreshold) / (1.f - fThreshold));
}

float4 PS_BLOOMBLUR(PS_INPUT_BLOOM_POST input) : SV_TARGET
{
	float fBlurDistance = 0.0015f;
	float4 f4ColorOut  = tex2D[8].Sample(linearSampler, float2(input.f2TexCoord.x + fBlurDistance, 
															   input.f2TexCoord.y + fBlurDistance) );
	f4ColorOut += tex2D[8].Sample(linearSampler, float2(input.f2TexCoord.x - fBlurDistance,
															   input.f2TexCoord.y - fBlurDistance) );
	f4ColorOut += tex2D[8].Sample(linearSampler, float2(input.f2TexCoord.x + fBlurDistance,
															   input.f2TexCoord.y - fBlurDistance) );
	f4ColorOut += tex2D[8].Sample(linearSampler, float2(input.f2TexCoord.x - fBlurDistance,
															   input.f2TexCoord.y + fBlurDistance) );

	f4ColorOut *= 0.25;
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
	float fTau = 0.25f;
	float fLastLum = exp(lumTex1.Sample(pointSampler, input.f2TexCoord).x);
	float fCurrentLum = lumTex.Sample(pointSampler, input.f2TexCoord).x;

	float fAdaptedLum = fLastLum + (fCurrentLum - fLastLum) * (1.f - exp(-fTimeDelta * fTau));

	return float4(log(fAdaptedLum), 1.f, 1.f, 1.f);
}

float4 PS_BLOOMACCUM(PS_INPUT_BLOOM_POST input) : SV_TARGET
{
	float fOriginalIntesity = 1.f;
	float fBloomIntesity = 1.3f;
	float fOriginalSaturation = 1.f;
	float fBloomSaturation = 1.3f;
#if(NUM_MSAA_SAMPLES <= 1)
	float fDepth = depthTex.Load(int3((int2)input.f4Pos.xy, 0)).x;
#else
	float fDepth = depthTex.Load(int3((int2)input.f4Pos.xy, 0), 0).x;
#endif
	fBloomIntesity *= (3 * fDepth);
	float3 f3BloomColor = tex2D[8].Sample(linearSampler, input.f2TexCoord).xyz;
	float3 f3OriginalColor = tex2D[7].Sample(linearSampler, input.f2TexCoord).xyz;

	float fAvgLuminance = GetAvgLuminance(lumTex, input.f2TexCoord);
	float fExposure = 0.f;
	f3OriginalColor = ToneMap(f3OriginalColor, fAvgLuminance, 0, fOriginalSaturation, fExposure);
	
	f3BloomColor *= fBloomIntesity;

	float3 f3ColorOut = f3OriginalColor + f3BloomColor;
	
	return float4(f3ColorOut, 1.f);


	/*f4BloomColor = AdjustSaturationB(f4BloomColor, fBloomSaturation) * fBloomIntesity;
	f4OriginalColor = AdjustSaturationO(f4OriginalColor, fOriginalSaturation, input.f2TexCoord) * fOriginalIntesity;

	f4OriginalColor *= (1.f - saturate(f4BloomColor));
	
	return saturate(f4OriginalColor + f4BloomColor);*/
}