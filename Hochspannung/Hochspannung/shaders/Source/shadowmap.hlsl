cbuffer ObjectInfo : register( b0 )
{
	matrix World;
	matrix LightView;
	matrix dummy;
	matrix Projection;
}

struct VS_INPUT
{
    float4 f4Pos : POSITION;
//	float4 f4Color : COLOR;
    float3 f3Normal : NORMAL;
    float2 f2TexCoord : TEXCOORD; 
    float3 f3Tangent : TANGENT;
    float3 f3Bitangent : BITANGENT;
//	unsigned int iTexture : ITEXTURE;
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

	output.f4Pos = mul(input.f4Pos, World);
	output.f4Pos = mul(output.f4Pos, LightView);
	output.f4Pos = mul(output.f4Pos, Projection);

    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shaders
//--------------------------------------------------------------------------------------
void ShadowMapPS( PS_INPUT input)
{
}