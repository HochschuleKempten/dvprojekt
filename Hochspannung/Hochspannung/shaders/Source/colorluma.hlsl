#include "postconstants.h"

Texture2D tex2D[8] : register(t15);

struct VS_INPUT_LUMA_POST
{
	float4 f4Pos : POSITION;
	float3 f3Normal : NORMAL;
	float2 f2TexCoord : TEXCOORD;
	float3 f3Tangent : TANGENT;
	float3 f3Bitangent : BITANGENT;
};

struct PS_INPUT_LUMA_POST
{
	float4 f4Pos : SV_POSITION0;
	float2 f2TexCoord : TEXCOORD0;
	float4 f4VertexPos : TEXCOORD2;
};

PS_INPUT_LUMA_POST VS_LUMA(VS_INPUT_LUMA_POST input)
{
	PS_INPUT_LUMA_POST output = (PS_INPUT_LUMA_POST)0;
	output.f2TexCoord = input.f2TexCoord;

	output.f4Pos = mul(input.f4Pos, World);

	return output;
}

float3 Mon2Lin(in float3 f3Color)
{
	return float3(pow(abs(f3Color.x), 2.2f), pow(abs(f3Color.y), 2.2f), pow(abs(f3Color.z), 2.2f));
}

float4 PS_LumaPost(in PS_INPUT_LUMA_POST input) : SV_TARGET
{
	float4 f4ColorOut;
	f4ColorOut.rgb = (tex2D[7].Sample(linearSampler, input.f2TexCoord)).rgb;
	f4ColorOut.a = 1.f;
	//f4ColorOut.rgb = ToneMapReinhard(f4ColorOut.rgb, 1.f);
	f4ColorOut.a = CalcLuminance(f4ColorOut.rgb);
	return f4ColorOut;
}
