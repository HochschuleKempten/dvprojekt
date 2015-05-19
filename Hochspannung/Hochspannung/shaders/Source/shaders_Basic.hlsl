
//--------------------------------------------------------------------------------------
// Copyright (c) Vektoria UG (haftungsbeschränkt)
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

//--------------------------------------------------------------------------------------
// Viewport information variables
//--------------------------------------------------------------------------------------

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
// 0=Diffuse, 1=Glow(emissive), 2=Specular, 3=DotBumpMap, 4 = Environmental 5= iPOM 6 = Thickness
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
	output.f4Pos = mul(input.f4Pos, World);
	output.f4VertexPos = output.f4Pos;
	output.f2TexCoord = input.f2TexCoord;
	matrix mViewProj = mul(View, Projection);
	output.f4Pos = mul(output.f4Pos,mViewProj);

	float4 f4Z; // Ursprung
	f4Z.xyz = 0;
	f4Z.w = 1;
	output.f3CamPos = mul(f4Z, ViewInv).xyz;  // f3CamPos ( wo liegt die Kamera?)
	output.f3Normal = normalize(mul(input.f3Normal, (float3x3)World));
	output.f3Tangent = normalize(mul(input.f3Tangent, (float3x3)World));
	output.f3Bitangent = normalize(mul(input.f3Bitangent, (float3x3)World));

	Light lightCurrent;
	int lightCurrentId = iLightsAffecting[0]; // Wir gehen (nur im BasicRenderer) vereinfachend davon aus: Es gibt nur 1 Licht
	lightCurrent = Lights[lightCurrentId];
	output.aAffectingLights[0].f4Color = lightCurrent.f4Color;
	output.aAffectingLights[0].bCauseShadow = lightCurrent.bCauseShadow;
	output.iLightCount = 1;
	float d;

	// TODO: create three buffers: one for parallel lights, one for spot lights and one for point lights, this will  increase performance!
	if (lightCurrent.iType == 3)		// spot light
	{
		output.aAffectingLights[0].f3Direction = normalize(lightCurrent.f3Position - output.f4Pos.xyz);
		output.aAffectingLights[0].f3SpotDirection = lightCurrent.f3Direction;
		output.aAffectingLights[0].fSpotInnerCosAngle = lightCurrent.fInnerCosAngle;
		output.aAffectingLights[0].fSpotOuterCosAngle = lightCurrent.fOuterCosAngle;
		d = abs(distance(lightCurrent.f3Position, output.f4Pos.xyz));
		output.aAffectingLights[0].fLuminosity = 1 / (1 + lightCurrent.fAttenuationConstant + lightCurrent.fAttenuationLinear * d + lightCurrent.fAttenuationQuadratic * pow(max(d, 1), 2));
		output.aAffectingLights[0].f4LightPos = mul(input.f4Pos, mul(World, lightCurrent.mLightViewProj));
		output.aAffectingLights[0].bSoftShadow = lightCurrent.bSoftShadow;
		output.aAffectingLights[0].bCascadedShadow = lightCurrent.bCascadedShadow;
	}
	else if (lightCurrent.iType == 2)	// point light
	{
		output.aAffectingLights[0].f3Direction = normalize(lightCurrent.f3Position - output.f4Pos.xyz);
		d = abs(distance(lightCurrent.f3Position, output.f4Pos.xyz));
		output.aAffectingLights[0].fLuminosity = 1 / (1 + lightCurrent.fAttenuationConstant + lightCurrent.fAttenuationLinear * d + lightCurrent.fAttenuationQuadratic * pow(max(d, 1), 2));
	}
	else								// directional light
	{
		output.aAffectingLights[0].f3Direction = normalize(lightCurrent.f3Direction);
		output.aAffectingLights[0].fLuminosity = 1;
	}

	output.aAffectingLights[0].iType = lightCurrent.iType;
	
	return output;
}

static const float pi = 3.14159265f;
float2 SphericalMapping(float3 f3)
{
	float  phi = 0;


	phi = atan(f3.x / f3.z);
	if (f3.x >= 0)
	{
		if ((f3.z < 0))
		{
			phi += pi;
		}
	}
	else
	{
		if (f3.z<0)
		{
			phi += pi;
		}
		else
			phi += 2 * pi;

	}

	phi /= 2.f * pi;

	float  theta = acos(f3.y);
	theta /= pi;

	return float2(phi, theta);
}
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	float3 f3EyeVector = normalize(input.f3CamPos - input.f4VertexPos.xyz);
	
	if (uiyPos>1 || uiyPics>1) // Animierte 
	{
		//20 = ixPos       21 = iyPos           22 = ixPics         23 = iyPics

		float fxPic = uixPos;
		float fyPic = uiyPos;
		float fxPics = uixPics;
		float fyPics = uiyPics;
		input.f2TexCoord.x = fxPic / fxPics + input.f2TexCoord.x*(1 / fxPics);
		input.f2TexCoord.y = fyPic / fyPics + input.f2TexCoord.y*(1 / fyPics);
	}


	if (uBump)
	{
		float3 f3BumpNormal = ((2 * (tex2D[3].Sample(linearSampler, input.f2TexCoord))) - 1.0).xyz;
		f3BumpNormal *= fBumpStrength;
		input.f3Normal = f3BumpNormal.r*input.f3Tangent + f3BumpNormal.g*input.f3Bitangent + f3BumpNormal.b*input.f3Normal;
		input.f3Normal = normalize(input.f3Normal);

	}
	float fShading = saturate(dot(input.aAffectingLights[0].f3Direction, input.f3Normal));


//	fFallOff = 1;
	float frShadowFactor = 1.f;
//	shadowFactor = shadowMap.SampleCmpLevelZero(shadowSampler, alLight.f4LightPos.xy, alLight.f4LightPos.z) / 4.f;
	float4 f4Diffuse;
	f4Diffuse = fShading* input.aAffectingLights[0].fLuminosity * input.aAffectingLights[0].f4Color * frShadowFactor; // *FallOff

	float4 f4ColGlow;
	if (uGlow) // TEXFLAG_GLOW
	{
		float fShadingInv = 1 - fShading;
		if (uGlowAsAmbient) // TEXFLAG_GLOWASAMBIENT
			f4ColGlow = f4ColorAmbient* fShadingInv;
		else
		{
			if (uGlowAsImage) // TEXFLAG_GLOWASIMAGE
				f4ColGlow = tex2D[0].Sample(linearSampler, input.f2TexCoord)* fShadingInv;
			else
				f4ColGlow = tex2D[1].Sample(linearSampler, input.f2TexCoord)* fShadingInv;
		}
	}
	else
		f4ColGlow = 0;

	// Berechnung des Specular Mappings:
	float fSpecular = 0;
	float4 f4SpecCol;
	float4 f4ReflectionTexture;
	if (uSpecular) // TEXTFLAG_SPECULAR
	{
		float3 f3Half = normalize(input.aAffectingLights[0].f3Direction + f3EyeVector);
		fSpecular += pow(saturate(dot(normalize(input.f3Normal), f3Half)), fA);
		if (uSpecularWhite) // TEXFLAG_SPECULARWHITE
			f4ReflectionTexture = 1;
		else if (uSpecularAsImage)// TEXFLAG_SPECULARASIMAGE 
			f4ReflectionTexture = tex2D[0].Sample(linearSampler, input.f2TexCoord);
		else
			f4ReflectionTexture = tex2D[2].Sample(linearSampler, input.f2TexCoord);
		f4SpecCol.rgb = 2 * input.aAffectingLights[0].f4Color.rgb * f4ReflectionTexture.b  * (fSpecular * f4Diffuse); 
		f4SpecCol.a = 1;
	}
	else
	{
		f4ReflectionTexture = 0;
		f4SpecCol = 0;
	}



	float4 f4ColorOut  = tex2D[0].Sample(linearSampler, input.f2TexCoord);
	if (uShadingOn) // bShading
		f4ColorOut.rgb = f4Diffuse.rgb*f4ColorOut.rgb + f4ColGlow.rgb;

	//Berechnung des Environmentmappings
	if (uEnvironment)
	{
//		float3 f3EyeVector = -normalize(input.f3CamPos - input.f4VertexPos.xyz);
		float3 f3Reflection = reflect(-f3EyeVector, input.f3Normal);
		// Refraction Ratio: Luft zu Wasser = 0,752; Luft zu Eis: 0,76; Luft zu Fensterglas: 0.657; Luft zu Diamant: 0.413
		float3 f3Refraction = refract(-f3EyeVector, input.f3Normal, .752f); 
	//	float3 RefractColor = texCUBE(ReflectionCubeMapSampler, Refract);

		float4 f4RefrColor = tex2D[4].Sample(linearSampler, SphericalMapping(f3Refraction));
		float4 f4ReflColor = tex2D[4].Sample(linearSampler, SphericalMapping(f3Reflection));
		float fColorStrength = 1.0f - f4ReflectionTexture.r - f4ReflectionTexture.g - f4ReflectionTexture.b;
		saturate(fColorStrength);
		f4ColorOut = f4RefrColor*f4ReflectionTexture.r + f4ReflColor*f4ReflectionTexture.g + f4SpecCol*f4ReflectionTexture.b + f4ColorOut*fColorStrength;

	}
	else
		f4ColorOut = f4ColorOut + f4SpecCol;

	return f4ColorOut;
}
