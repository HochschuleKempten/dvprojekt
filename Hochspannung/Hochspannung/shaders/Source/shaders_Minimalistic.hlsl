
//--------------------------------------------------------------------------------------
// Copyright (c) Tobias Breiner & Florian Schnell
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Shadow Map Samplers
//--------------------------------------------------------------------------------------

SamplerComparisonState shadowSampler : register(s2);

SamplerState pointSampler : register(s1);

SamplerState linearSampler : register(s0);

//--------------------------------------------------------------------------------------
// Information that are provided by object
// ie: position in world space and lights affecting its surface
//--------------------------------------------------------------------------------------
cbuffer ObjectInfo : register(b0)
{
	matrix World;
	matrix View;
	matrix ViewInv;
	matrix Projection;
	vector<uint, 4> iLightsAffecting;
	uint iLightCount;
}

//--------------------------------------------------------------------------------------
// Material & Texture Information Variables
//--------------------------------------------------------------------------------------
cbuffer TexInfo : register(b1)
{
	float4 f4ColorAmbient			: packoffset(c0);
	float fA						: packoffset(c1); // specular sharpness
	float fH						: packoffset(c1.y);// diffuse sharpness
	float fBumpStrength				: packoffset(c1.z);
	float frTransparency			: packoffset(c1.w);
	float4 f4ColorSSS				: packoffset(c2);
	float4 f4SSSBRDFParams			: packoffset(c3);
	uint uImage						: packoffset(c4);
	uint uGlow						: packoffset(c4.y);
	uint uSpecular					: packoffset(c4.z);
	uint uBump						: packoffset(c4.w);
	uint uImageBlack				: packoffset(c5);
	uint uGlowAsImage				: packoffset(c5.y);
	uint uSpecularAsImage			: packoffset(c5.z);
	uint uHeightAsImage				: packoffset(c5.w);
	uint uImageWhite				: packoffset(c6);
	uint uGlowWhite					: packoffset(c6.y);
	uint uSpecularWhite				: packoffset(c6.z);
	uint uHeight					: packoffset(c6.w);
	uint uShadingOn					: packoffset(c7);
	uint uGlowAsAmbient				: packoffset(c7.y);
	uint uChromaKeying				: packoffset(c7.z);
	uint uEnvironment				: packoffset(c7.w);
	uint uPOM						: packoffset(c8);
	uint uTexBRDF					: packoffset(c8.y);
	uint uTexSSS					: packoffset(c8.z);
	uint uReflectionMap				: packoffset(c8.w);
	uint uixPos						: packoffset(c9);
	uint uiyPos						: packoffset(c9.y);
	uint uixPics					: packoffset(c9.z);
	uint uiyPics					: packoffset(c9.w);
}

cbuffer ViewportArt : register(b2)
{
	float4 f4ColorViewportOutline	: packoffset(c0);
	float4 f4FogParams				: packoffset(c1);
	matrix mColorModification		: packoffset(c2);

	uint uStyleColor				: packoffset(c6);
	uint uStyleHalfTransparent		: packoffset(c6.y);
	uint uStylePopart				: packoffset(c6.z);
	uint uStyleOutlining			: packoffset(c6.w);
	uint uStyleMonochrome			: packoffset(c7);
	uint uStyleOwn					: packoffset(c7.y);
	uint uStyleFog					: packoffset(c7.z);
	uint uPad0						: packoffset(c7.w);
}

//--------------------------------------------------------------------------------------
// Light information variables
//--------------------------------------------------------------------------------------
struct Light
{
	float3 f3Position;				// all lights
	uint iType;						// all lights
	float4 f4Color;					// all lights
	float3 f3Direction;				// directional light, spot light
	float fInnerCosAngle;			// spot light
	float fOuterCosAngle;			// spot light
	float fAttenuationConstant;		// point light, spot light
	float fAttenuationLinear;		// point light, spot light
	float fAttenuationQuadratic;	// point light, spot light
	bool bCauseShadow;
	bool bSoftShadow;
	bool bCascadedShadow;
	float4x4 mLightViewProj;
};

struct AffectingLight
{
	float fLuminosity;
	float3 f3Direction;
	float4 f4Color;
	float3 f3SpotDirection;
	float fSpotInnerCosAngle;
	float fSpotOuterCosAngle;
	bool bCauseShadow;
	bool bSoftShadow;
	bool bCascadedShadow;
	uint iId;
	uint iType;
	float4 f4LightPos : TEXCOORD0;
};

StructuredBuffer<Light> Lights : register (t10);

Texture2D shadowMap : register (t11);

//--------------------------------------------------------------------------------------
// Textur Buffer
// 0=Image, 1=Glow(emissive), 2=Specular, 3=DotBumpMap, 4 = Environmental 
//--------------------------------------------------------------------------------------

Texture2D tex2D[7] : register (t15); // texture

//--------------------------------------------------------------------------------------

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
	float4 f4Pos : SV_POSITION0;
	float3 f3Normal : NORMAL;
	float3 f3Tangent : TANGENT0;
	float3 f3Bitangent : BITANGENT0;
	float2 f2TexCoord : TEXCOORD0;
	float3 f3CamPos : TEXCOORD1;
	float4 f4VertexPos : TEXCOORD2;
	AffectingLight aAffectingLights[4] : LIGHTS;
	uint iLightCount : COUNT;
};

//--------------------------------------------------------------------------------------
// Phong Lighting Reflection Model
//--------------------------------------------------------------------------------------
struct DirectionalLight
{
	float4 f4Color;
	float3 f3Dir;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{

	PS_INPUT output = (PS_INPUT)0;
	float4 f4Z;
	f4Z.xyz = 0;
	f4Z.w = 1;

	output.f4Pos = mul(input.f4Pos, World);
	output.f4VertexPos = output.f4Pos;
	matrix viewproj = mul(View, Projection);
	output.f4Pos = mul(output.f4Pos, viewproj);

//	output.f3Normal = normalize(mul(input.f3Normal, (float3x3)World));
//	output.f3Tangent = normalize(mul(input.f3Tangent, (float3x3)World));
//	output.f3Bitangent = normalize(mul(input.f3Bitangent, (float3x3)World));
	output.f2TexCoord = input.f2TexCoord;

	// Augenpos mittels ViewInv-Matrix berechnen
	output.f3CamPos = mul(f4Z, ViewInv).xyz;    	// Augenvektor mittels View-Matrix berechnen
// 	output.iLightCount = 0;
	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	return tex2D[0].Sample(linearSampler, input.f2TexCoord);
	/*
	float4 f4ColorOut;
	float2 f2ParallaxTex = input.f2TexCoord;
	f4ColorOut = tex2D[0].Sample(linearSampler, f2ParallaxTex);


	return f4ColorOut;
	*/
}
