#include "postconstants.h"

#define FXAA_PC 1
#define FXAA_HLSL_5 1
#define FXAA_QUALITY__PRESET 12
#define FXAA_GREEN_AS_LUMA 1

#include "fxaa.h"
//--------------------------------------------------------------------------------------
// Copyright (c) Tobias Breiner
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// Textur Buffer
//--------------------------------------------------------------------------------------

Texture2D tex2D[8] : register ( t15 ); // texture

//--------------------------------------------------------------------------------------

struct VS_INPUT_POST
{
    float4 f4Pos : POSITION;
    float3 f3Normal : NORMAL;
    float2 f2TexCoord : TEXCOORD; 
    float3 f3Tangent : TANGENT;
    float3 f3Bitangent : BITANGENT;
};


struct PS_INPUT_POST
{
   float4 f4Pos : SV_POSITION0;
   float2 f2TexCoord : TEXCOORD0;
   float4 f4VertexPos : TEXCOORD2;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT_POST VS_POST( VS_INPUT_POST input )
{
    PS_INPUT_POST output = (PS_INPUT_POST)0;
	output.f2TexCoord = input.f2TexCoord;
	//output.f2TexCoord.x = 1.f - output.f2TexCoord.x;
	output.f4Pos = mul(input.f4Pos, World);

    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS_POST( PS_INPUT_POST input) : SV_Target
{
	float4 f4ColorOut;
	f4ColorOut.rgb = (tex2D[7].Sample(linearSampler, input.f2TexCoord)).rgb;
	FxaaTex tex;
	float2 f2rcpFrame = float2(fRcpFrameX, fRcpFrameY);
	tex.smpl = linearSampler;
	tex.tex = tex2D[7];
	if (fRcpFrameX) // FXAA enabled
	{
		
		
	}


	f4ColorOut.a = 1.f;
	return f4ColorOut;
}