#include "constant.h"
#include "texandtexflags.h"
//////////////////////////////////////////////////////////////////////
// textures
//Texture2D tex2D[7] : register (t15);

//////////////////////////////////////////////////////////////////////
// shader in-output
struct VS_INPUT
{
	float4 f4Pos : POSITION;
	float3 f3Normal : NORMAL;
	float2 f2TexCoord : TEXCOORD;
	float3 f3Tangent : TANGENT;
	float3 f3Bitangent : BITANGENT;
};

struct VS_OUTPUT
{
	float3 f3Normal : NORMAL;
	float2 f2TexCoord :TEXCOORD0;
	float3 f3PosWS : TEXCOORD1;
	float4 f4Pos : SV_POSITION;
};

struct PS_INPUT
{
	float3 f3Normal : NORMAL;
	float2 f2TexCoord : TEXCOORD0;
	float3 f3PosWS : TEXCOORD1;
};

struct PS_OUTPUT
{
	float4 f4Normal : SV_TARGET0;
	float4 f4Diffuse : SV_TARGET1;
};

//////////////////////////////////////////////////////////////////////
// RSM vertex shader
VS_OUTPUT RSMVS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	float4 f4WorldPos = mul(input.f4Pos, g_mWorld);
	output.f3PosWS = f4WorldPos.xyz;
	output.f4Pos = mul(f4WorldPos, g_mViewProj);

	output.f3Normal = mul(input.f3Normal, (float3x3)g_mWorld);

	output.f2TexCoord = input.f2TexCoord;

	return output;
}
//////////////////////////////////////////////////////////////////////
// RSM pixel shader
PS_OUTPUT RSMPS(PS_INPUT input)
{
	PS_OUTPUT output = (PS_OUTPUT)0;
	
	float3 f3N = normalize(input.f3Normal);
	
	float3 f3C1 = cross(f3N, float3(0.f, 0.f, 1.f));
	float3 f3C2 = cross(f3N, float3(0.f, 1.f, 0.f));
	float3 f3T;
	[branch]
	if (length(f3C1) > length(f3C2))
	{
		f3T = f3C1;
	}
	else
	{
		f3T = f3C2;
	}
	float3 f3B = normalize(-cross(f3N, f3T));

	[branch]
	if (uBump)
	{
		float3 f3BumpNormal = ((2 * (tex2D[3].Sample(g_Sampler, input.f2TexCoord))) - 1.f).xyz;
		f3BumpNormal *= fBumpStrength;
		input.f3Normal += f3BumpNormal.x* f3T + f3BumpNormal.y * f3B;
		output.f4Normal.xyz = normalize(input.f3Normal);
	}
	else
	{
		output.f4Normal.xyz = normalize(0.5f * (1.f + normalize(input.f3Normal)));
	}

	output.f4Diffuse.rgb = tex2D[0].Sample(g_Sampler, input.f2TexCoord).rgb;
	output.f4Diffuse.a = 1.f;

	return output;
}