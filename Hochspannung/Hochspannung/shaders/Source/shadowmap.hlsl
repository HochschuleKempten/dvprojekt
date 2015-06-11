//--------------------------------------------------------------------------------------
// Copyright (c) Tobias Breiner, Vektoria UG (haftungsbeschränkt) 
//--------------------------------------------------------------------------------------

cbuffer ObjectInfo : register( b0 )
{
	matrix mWorld;
	matrix mLightView;
	matrix mDummy;
	matrix mProjection;
}

struct VS_INPUT
{
    float4 f4Pos : POSITION;
    float3 f3Normal : NORMAL;
    float2 f2TexCoord : TEXCOORD; 
    float3 f3Tangent : TANGENT;
    float3 f3Bitangent : BITANGENT;
};

struct PS_INPUT
{
	float4 f4Pos : SV_Position;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT ShadowMapVS( VS_INPUT input )
{
    PS_INPUT output;

	output.f4Pos = mul(input.f4Pos, mWorld);
	output.f4Pos = mul(output.f4Pos, mLightView);
	output.f4Pos = mul(output.f4Pos, mProjection);

    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shaders
//--------------------------------------------------------------------------------------
void ShadowMapPS( PS_INPUT input)
{
}