
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

	DirectionalLight light;
	light.f4Color.rgba = 1.f;
	light.f3Dir = 0;

	output.f4Pos = mul(input.f4Pos, World);
	output.f4VertexPos = output.f4Pos;
	// calculate the directions of the lights
	Light lightCurrent;
	float d;

	[unroll]
	for (uint i = 0; i < iLightCount; i++)
	{
		// get the lights that we need to render for current vertex
		int lightCurrentId = iLightsAffecting[i];
		lightCurrent = Lights[lightCurrentId];
		output.aAffectingLights[i].iId = lightCurrentId;

		// copy color
		output.aAffectingLights[i].f4Color = lightCurrent.f4Color;

		// copy shadow setting
		output.aAffectingLights[i].bCauseShadow = lightCurrent.bCauseShadow;

		// TODO: create three buffers: one for parallel lights, one for spot lights and one for point lights, this will  increase performance!
		if (lightCurrent.iType == 3)		// spot light
		{
			output.aAffectingLights[i].f3Direction = normalize(lightCurrent.f3Position - output.f4Pos.xyz);
			output.aAffectingLights[i].f3SpotDirection = lightCurrent.f3Direction;
			output.aAffectingLights[i].fSpotInnerCosAngle = lightCurrent.fInnerCosAngle;
			output.aAffectingLights[i].fSpotOuterCosAngle = lightCurrent.fOuterCosAngle;
			d = abs(distance(lightCurrent.f3Position, output.f4Pos.xyz));
			output.aAffectingLights[i].fLuminosity = 1 / (1 + lightCurrent.fAttenuationConstant + lightCurrent.fAttenuationLinear * d + lightCurrent.fAttenuationQuadratic * pow(max(d, 1), 2));
			output.aAffectingLights[i].f4LightPos = mul(input.f4Pos, mul(World, lightCurrent.mLightViewProj));
			output.aAffectingLights[i].bSoftShadow = lightCurrent.bSoftShadow;
			output.aAffectingLights[i].bCascadedShadow = lightCurrent.bCascadedShadow;
		}
		else if (lightCurrent.iType == 2)	// point light
		{
			output.aAffectingLights[i].f3Direction = normalize(lightCurrent.f3Position - output.f4Pos.xyz);
			d = abs(distance(lightCurrent.f3Position, output.f4Pos.xyz));
			output.aAffectingLights[i].fLuminosity = 1 / (1 + lightCurrent.fAttenuationConstant + lightCurrent.fAttenuationLinear * d + lightCurrent.fAttenuationQuadratic * pow(max(d, 1), 2));
		}
		else								// directional light
		{
			output.aAffectingLights[i].f3Direction = lightCurrent.f3Direction;
			output.aAffectingLights[i].fLuminosity = 1;
		}

		output.aAffectingLights[i].iType = lightCurrent.iType;
	}

	matrix viewproj = mul(View, Projection);
	output.f4Pos = mul(output.f4Pos, viewproj);
	//output.f4Pos = mul(output.f4Pos, Projection);

	output.f3Normal = normalize(mul(input.f3Normal, (float3x3)World));
	output.f3Tangent = normalize(mul(input.f3Tangent, (float3x3)World));
	output.f3Bitangent = normalize(mul(input.f3Bitangent, (float3x3)World));
	output.f2TexCoord = input.f2TexCoord;
	//    output.f3CamPos = mul(f3Z, transpose(View));  
	// Augenpos mittels ViewInv-Matrix berechnen
	output.f3CamPos = mul(f4Z, ViewInv).xyz;    	// Augenvektor mittels View-Matrix berechnen
	output.iLightCount = iLightCount;
	return output;
}

//Get random numbers with Gelfond-Schneider
float RandomGelfond(float2 f2p)
{
	const float2 r = float2(23.1406926327792690,  // e^pi (Gelfond's constant)
							2.6651441426902251);  // 2^sqrt(2) (Gelfond–Schneider constant)
	return (frac(cos(fmod(123456789., 1e-7 + 256. * dot(f2p, r)))));
}

//Get random texture offset
float2 TexOffset2(int iu, int iv, float fWidth, float fHeight, float fSampleOffset, float2 f2Pos)
{
	const float frand = RandomGelfond(f2Pos);
	return float2((iu * 1.f / (fWidth * (fSampleOffset + frand))), (iv * 1.f / (fHeight * (fSampleOffset + frand))));
}


float HalfLambert(float3 f3Vec1, float3 f3Vec2)
{
	float fProduct = dot(f3Vec1, f3Vec2);
	fProduct *= 0.5f;
	fProduct += 0.5f;
	return fProduct;
}

float BlinnPhongSpec(float3 f3Normal, float3 f3LightDir, float fSpecpower)
{
	float3 f3HalfAngle = normalize(f3Normal + f3LightDir);
		return pow(saturate(dot(f3Normal, f3HalfAngle)), fSpecpower);
}

float3 texBRDF(PS_INPUT input,
	float3 f3SurfaceColor,
	float3 f3LampColor,
	float3 f3AmbiColor,
	float3 f3LightDir,
	float3 f3DiffColor)
{
	const float3 f3Nn = input.f3Normal;
	const float3 f3Vn = normalize(input.f3CamPos.xyz - input.f4VertexPos.xyz);
	const float3 f3Ln = normalize(f3LightDir);
	const float3 f3Hn = normalize(f3Vn + f3Ln);
	const float2 f2huv = float2(0.5f + dot(f3Hn, f3Ln) / 2.f, 1.f - (0.5f + dot(f3Nn, f3Hn) / 2.f));
	const float2 f2nuv = float2(0.5f + dot(f3Ln, f3Nn) / 2.f, 1.f - (0.5f + dot(f3Nn, f3Vn) / 2.f));
	const float3 f3ht = tex2D[5].Sample(linearSampler, f2huv).rgb;
	const float3 f3nt = tex2D[3].Sample(linearSampler, f2nuv).rgb;
	const float3 f3nspec = f3ht + f3nt * f3LampColor * f3AmbiColor;
	return (f3DiffColor + f3nspec);
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
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

	float2 f2ParallaxTex = input.f2TexCoord;
	const float3 f3aNormal = input.f3Normal;
	if (uPOM == 1) //POM
	{
		const float3 f3EyeVector = normalize(input.f3CamPos.xyz - input.f4VertexPos.xyz);
		const float3 f3ViewDir = -f3EyeVector;

		const float3 f3N = normalize(input.f3Normal);
		const float3 f3T = input.f3Tangent;
		const float3 f3B = -cross(f3N, f3T);

		const float3x3 f3x3ToTangent = transpose(float3x3(f3T, f3B, f3N));
		const float3 f3ViewDirTS = mul(f3ViewDir, f3x3ToTangent);

		const float2 f2MaxParallaxOffset = -f3ViewDirTS.xy * 0.02f / f3ViewDirTS.z;

		const int iSampleCount = ((int)lerp(20, 5, dot(-f3EyeVector, input.f3Normal)));

		const float fZStep = 1.f / (float)iSampleCount;
		const float2 f2TexStep = f2MaxParallaxOffset * fZStep;

		const float2 f2Dx = ddx(input.f2TexCoord);
		const float2 f2Dy = ddy(input.f2TexCoord);

		int iSampleIdx = 0;
		float2 f2CurTexOffset = 0.f;
		float2 f2PrevTexOffset = 0.f;
		float2 f2FinalTexOffset = 0.f;
		float fCurRayZ = 1.f - fZStep;
		float fPrevRayZ = 1.f;
		float fCurHeight = 0.f;
		float fPrevHeight = 0.f;
		float2 f2P1 = 0.f;
		float2 f2P2 = 0.f;

		[loop]
		while (iSampleIdx < iSampleCount + 1)
		{
			fCurHeight = tex2D[5].SampleGrad(linearSampler, input.f2TexCoord + f2CurTexOffset, f2Dx, f2Dy).r;
			fCurHeight = (fPrevHeight + fCurHeight) * .5f;
			if (fCurHeight > fCurRayZ)
			{
				float fT = (fPrevHeight - fPrevRayZ) / (fPrevHeight - fCurHeight + fCurRayZ - fPrevRayZ);
				f2FinalTexOffset = f2PrevTexOffset + fT * f2TexStep;

				iSampleIdx = iSampleCount + 1;
			}
			else
			{
				++iSampleIdx;
				f2PrevTexOffset = f2CurTexOffset;
				fPrevRayZ = fCurRayZ;
				fPrevHeight = fCurHeight;
				f2CurTexOffset += f2TexStep;
				fCurRayZ -= fZStep;
			}
		}

		f2ParallaxTex = input.f2TexCoord + f2FinalTexOffset;

		const float fHeightX = (tex2D[5].Sample(linearSampler, f2ParallaxTex).g);
		const float fHeightY = (tex2D[5].Sample(linearSampler, f2ParallaxTex).g);

		input.f3Normal += (fHeightX * f3T + fHeightY * f3B);
		input.f3Normal = normalize(input.f3Normal);
	}
	
	if (uPOM == 2) //POM
	{
		const int iConeSteps = 15;
		const int iBinarySteps = 6;

		const float3 f3EyeVector = normalize(input.f3CamPos.xyz - input.f4VertexPos.xyz);
		const float3 f3ViewDir = -f3EyeVector;

		const float3 f3N = normalize(input.f3Normal);
		const float3 f3T = input.f3Tangent;
		const float3 f3B = -cross(f3N, f3T);

		const float3x3 f3x3ToTangent = transpose(float3x3(f3T, f3B, f3N));
		const float3 f3ViewDirTS = mul(f3ViewDir, f3x3ToTangent);

		float3 f3RayDir = normalize(f3ViewDirTS);
		f3RayDir /= f3RayDir.z;
		float fRayRatio = length(f3RayDir.xy);
		//fRayRatio /= fRayRatio.z;
		fRayRatio = 1.f;
		float3 f3Pos = float3(input.f2TexCoord, 0.f);
		//float fRayRatio = (lerp(2.f, 0, dot(-f3EyeVector, input.f3Normal)));
		[unroll]
		for (int i = 0; i < iConeSteps; i++)
		{
			float4 f4Tex = tex2D[5].Sample(linearSampler, f3Pos.xy);
			float fConeRatio = f4Tex.z;
			float fHeight = saturate(f4Tex.w - f3Pos.z);
			float fD = (fConeRatio*fHeight / (fRayRatio + fConeRatio))*0.01f;
			f3Pos += f3RayDir * fD;
		}

		float3 f3BinSearchRange = 0.5f * f3RayDir * f3Pos.z;
		float3 f3BinSearchPosition = float3(input.f2TexCoord, 0.f) + f3BinSearchRange;
		[unroll]
		for (int i = 0; i < iBinarySteps; i++)
		{
			float4 f4Tex = tex2D[5].Sample(linearSampler, f3BinSearchPosition.xy);
			f3BinSearchRange *= 0.5f;
			[branch]
			if (f3BinSearchPosition.z < f4Tex.w)
				f3BinSearchPosition += f3BinSearchRange;
			else
				f3BinSearchPosition -= f3BinSearchRange;
		}

		f2ParallaxTex = f3BinSearchPosition.xy;

		const float fHeightX = (tex2D[5].Sample(linearSampler, f3BinSearchPosition.xy).w);
		const float fHeightY = (tex2D[5].Sample(linearSampler, f3BinSearchPosition.xy).w);

		input.f3Normal += ((fHeightX)* f3T + (fHeightY)* f3B);
		input.f3Normal = normalize(input.f3Normal);
	}
	// Berechnung des Bump Mappings:
	if (uBump)
	{
		float3 f3BumpNormal = ((2 * (tex2D[3].Sample(linearSampler, f2ParallaxTex))) - 1.0).xyz;
		f3BumpNormal *= fBumpStrength;
		input.f3Normal += f3BumpNormal.x*input.f3Tangent + f3BumpNormal.y*input.f3Bitangent;
		//		input.f3Normal = f3BumpNormal.x*input.f3Tangent*fBumpStrength+f3BumpNormal.y*input.f3Bitangent*fBumpStrength +f3BumpNormal.z*input.f3Normal;
		input.f3Normal = normalize(input.f3Normal);

	}
	// Berechnung der diffusen Beleuchtung:
	float fFallOff;
	float4 f4Diffuse = 0;
	float shadowFactor = 0;

	float fWidth, fHeight;
	shadowMap.GetDimensions(fWidth, fHeight);

	[unroll]
	for (uint i = 0; i < input.iLightCount; i++)
	{
		AffectingLight alLight = input.aAffectingLights[i];

		// SPOT LIGHT
		fFallOff = 1;
		shadowFactor = 1.f;

		if (alLight.iType == 3)
		{
			float fCosCurAngle = dot(normalize(alLight.f3Direction), normalize(alLight.f3SpotDirection));
			if (fCosCurAngle < alLight.fSpotInnerCosAngle)
			{
			if (fCosCurAngle > alLight.fSpotOuterCosAngle)
			{
				fFallOff = (fCosCurAngle - alLight.fSpotOuterCosAngle) / (alLight.fSpotInnerCosAngle - alLight.fSpotOuterCosAngle);
			}
			else
			{
				continue;
			}
			}
			// SHADOW MAPPING
			if (alLight.bCauseShadow)
			{
				//re-homogenize position after interpolation
				alLight.f4LightPos.xyz /= alLight.f4LightPos.w;

				//if position is not visible to the light - dont illuminate it
				//results in hard light frustum
				[branch]
				if (alLight.f4LightPos.x < -1.0f || alLight.f4LightPos.x > 1.0f ||
					alLight.f4LightPos.y < -1.0f || alLight.f4LightPos.y > 1.0f ||
					alLight.f4LightPos.z < 0.0f || alLight.f4LightPos.z > 3.0f) continue;

				//alLight.f4LightPos.z -= 0.00001f;
				const float2 Offset = f2ParallaxTex - input.f2TexCoord;
				alLight.f4LightPos.x -= Offset.x * .2f;
				alLight.f4LightPos.y -= Offset.y * .2f;

				//transform clip space coords to texture space coords (-1:1 to 0:1)	
				alLight.f4LightPos.x = alLight.f4LightPos.x * 0.5f + 0.5f;
				alLight.f4LightPos.y = alLight.f4LightPos.y * -0.5f + 0.5f;
				[branch]
				if (alLight.bSoftShadow)
				{
					//PCF filtering
					float fsum = 0.f;
					float fx, fy;
					[unroll]
					for (fy = -1.5f; fy <= 1.5f; fy += 1.f)
					{
						[unroll]
						for (fx = -1.5f; fx <= 1.5f; fx += 1.f)
						{
							fsum += ((shadowMap.SampleCmpLevelZero(shadowSampler, alLight.f4LightPos.xy +
								TexOffset2(fx, fy, fWidth, fHeight, 0.5f, f2ParallaxTex), alLight.f4LightPos.z))).r * 0.8f;
						}
					}
					[branch]
					if (alLight.bCascadedShadow)
					{
						//Offset for 2nd shadow map
						alLight.f4LightPos.x += (abs(alLight.f4LightPos.z) * 0.1f);
						alLight.f4LightPos.y += (abs(alLight.f4LightPos.z) * 0.1f);

						[unroll]
						for (fy = -1.5f; fy <= 1.5f; fy += 1.f)
						{
							[unroll]
							for (fx = -1.5f; fx <= 1.5f; fx += 1.f)
							{
								fsum += ((shadowMap.SampleCmpLevelZero(shadowSampler, alLight.f4LightPos.xy +
									TexOffset2(fx, fy, fWidth, fHeight, 0.5f, f2ParallaxTex), alLight.f4LightPos.z)).r * 0.2f);
							}
						}
					}
					//float4 f4BilVals = shadowMap.Gather(shadowSampler, alLight.f4LightPos.xy);
					//float fMid = (f4BilVals.x + f4BilVals.y + f4BilVals.z + f4BilVals.w);
					//fsum /= fMid;*/
					shadowFactor = fsum / 16.f;
				}
				else
				{
					shadowFactor = shadowMap.SampleCmpLevelZero(shadowSampler, alLight.f4LightPos.xy, alLight.f4LightPos.z) / 4.f;
				}
			}
			else
			{
				shadowFactor = shadowMap.SampleCmpLevelZero(shadowSampler, alLight.f4LightPos.xy, alLight.f4LightPos.z) / 4.f;
			}
		}
		// EVERY LIGHT
		f4Diffuse += saturate(dot(alLight.f3Direction, normalize(input.f3Normal))) * alLight.fLuminosity * alLight.f4Color * fFallOff * shadowFactor;
	}
	f4Diffuse = saturate(fH * f4Diffuse);  // saturate clamps the specified value within the range of 0 to 1.


	// Berechnung des Specular Mappings:
	float3 f3Half;
	float fSpecular = 0;
	float4 f4SpecCol;
	if (uSpecular) // TEXTFLAG_SPECULAR
	{
		[unroll]
		for (uint i = 0; i < input.iLightCount; i++)
		{
			f3Half = normalize(normalize(input.aAffectingLights[i].f3Direction) + normalize(input.f3CamPos - (float3)input.f4VertexPos));
			fSpecular += pow(saturate(dot(normalize(input.f3Normal), f3Half)), fA);
		}
		if (uSpecularWhite) // TEXFLAG_SPECULARWHITE
			f4SpecCol = 2 * (fSpecular * f4Diffuse);
		else if (uSpecularAsImage)// TEXFLAG_SPECULARASIMAGE 
			f4SpecCol = 2 * tex2D[0].Sample(linearSampler, f2ParallaxTex) * (fSpecular * f4Diffuse);
		else
			f4SpecCol = 2 * tex2D[2].Sample(linearSampler, f2ParallaxTex) * (fSpecular * f4Diffuse);
	}
	else
	{
		f4SpecCol = 0;
	}


	// Berechnung der Image Textur:
	float4 f4TexCol;
	if (uImage) // TEXFLAG_IMAGE
		f4TexCol = tex2D[0].Sample(linearSampler, f2ParallaxTex);
	else if (uImageBlack) // TEXFLAG_IMAGEBLACK
		f4TexCol = 0;
	else
		f4TexCol = 1; // TEXFLAG_NOIMAGE or TEXFLAG_IMAGEWHITE
	uint iWidth;
	uint iHeight;
	if (uChromaKeying) // bChromaKeying
	{

		uint iLevels;
		tex2D[0].GetDimensions(0, iWidth, iHeight, iLevels);

		// Rechne Texturkoordinaten aus:
		float2 f2TexCoord2 = float2(f2ParallaxTex.x * iWidth, f2ParallaxTex.y * iHeight);
		int2 i2TexCoord = int2(f2ParallaxTex.x, f2ParallaxTex.y);

		// Hole Farbe des linken oberen Pixels
		int3 i3Pos = int3(0, 0, 0);
		float4 f4ChromaKey = tex2D[0].Load(i3Pos);
		i3Pos = int3(i2TexCoord.x, i2TexCoord.y, 0);
		float4 f4Texel = tex2D[0].Load(i3Pos);

		// ChromaKey Maskierung:
		if ((f4Texel.r == f4ChromaKey.r) && (f4Texel.g == f4ChromaKey.g) && (f4Texel.b == f4ChromaKey.b))
			f4TexCol.a = 0;	// discard;

		// Sampling:
		float2 f2TexPos1 = float2(f2TexCoord2.x - 0.5, f2TexCoord2.y - 0.5);
		float2 f2TexPos2 = float2(f2TexCoord2.x + 0.5, f2TexCoord2.y - 0.5);
		float2 f2TexPos3 = float2(f2TexCoord2.x - 0.5, f2TexCoord2.y + 0.5);
		float2 f2TexPos4 = float2(f2TexCoord2.x + 0.5, f2TexCoord2.y + 0.5);
		float4 f4Col1 = tex2D[0].Load(int3(f2TexPos1.x, f2TexPos1.y, 0));
		float4 f4Col2 = tex2D[0].Load(int3(f2TexPos2.x, f2TexPos2.y, 0));
		float4 f4Col3 = tex2D[0].Load(int3(f2TexPos3.x, f2TexPos3.y, 0));
		float4 f4Col4 = tex2D[0].Load(int3(f2TexPos4.x, f2TexPos4.y, 0));
		if ((f4Col1.r == f4ChromaKey.r) && (f4Col1.g == f4ChromaKey.g) && (f4Col1.b == f4ChromaKey.b)) f4Col1 = 0;
		if ((f4Col2.r == f4ChromaKey.r) && (f4Col2.g == f4ChromaKey.g) && (f4Col2.b == f4ChromaKey.b)) f4Col2 = 0;
		if ((f4Col3.r == f4ChromaKey.r) && (f4Col3.g == f4ChromaKey.g) && (f4Col3.b == f4ChromaKey.b)) f4Col3 = 0;
		if ((f4Col4.r == f4ChromaKey.r) && (f4Col4.g == f4ChromaKey.g) && (f4Col4.b == f4ChromaKey.b)) f4Col4 = 0;
		f2TexPos1 = float2(frac(f2TexPos1.x), frac(f2TexPos1.y));

		// Bilineare Interpolation:
		float fAlpha = (f4Col2.a - f4Col1.a) * f2TexPos1.x + f4Col1.a;
		fAlpha = (((f4Col4.a - f4Col3.a) * f2TexPos1.x + f4Col3.a) - fAlpha) * f2TexPos1.y + fAlpha;
		//	if (fAlpha < 0.75) 
		//		f4TexCol.a = 0;			// discard;
		if (fAlpha <0.73)
			f4TexCol.a = fAlpha - 0.40; // etwas weiche Raender

		f4Col1 = float4(
			(f4Col2.r - f4Col1.r) * f2TexPos1.x + f4Col1.r,
			(f4Col2.g - f4Col1.g) * f2TexPos1.x + f4Col1.g,
			(f4Col2.b - f4Col1.b) * f2TexPos1.x + f4Col1.b,
			0);
		f4Col3 = float4(
			(f4Col4.r - f4Col3.r) * f2TexPos1.x + f4Col3.r,
			(f4Col4.g - f4Col3.g) * f2TexPos1.x + f4Col3.g,
			(f4Col4.b - f4Col3.b) * f2TexPos1.x + f4Col3.b,
			0);
		f4TexCol = float4(
			(f4Col3.r - f4Col1.r) * f2TexPos1.y + f4Col1.r,
			(f4Col3.g - f4Col1.g) * f2TexPos1.y + f4Col1.g,
			(f4Col3.b - f4Col1.b) * f2TexPos1.y + f4Col1.b,
			fAlpha);

	}

	// Berechnung des Glowmappings:
	float4 f4Glow;
	if (uGlow) // TEXFLAG_GLOW
	{
		if (uGlowAsAmbient) // TEXFLAG_GLOWASAMBIENT
			f4Glow = f4ColorAmbient;
		else
		{
			if (uGlowAsImage) // TEXFLAG_GLOWASIMAGE
				f4Glow = tex2D[0].Sample(linearSampler, f2ParallaxTex)* saturate(1 - f4Diffuse);
			else
				f4Glow = tex2D[1].Sample(linearSampler, f2ParallaxTex)* saturate(1 - f4Diffuse);
		}
	}
	else
		f4Glow = 0;

	if (uShadingOn) // bShading
		f4TexCol.rgb *= f4Diffuse.rgb;

	// Alpha Mapping und Integration:
	float4 f4ColorOut = f4ColorAmbient + f4TexCol + f4Glow + f4SpecCol;

		//Berechnung des Environmentmappings
		if (uEnvironment)
		{
			float3 f3EyeVector = normalize(input.f3CamPos - input.f4VertexPos.xyz);
			float3 f3Reflection = reflect(f3EyeVector, input.f3Normal);
			float3 f3Refraction = refract(f3EyeVector, input.f3Normal, .99f);

			float4 f4RefrColor = tex2D[4].Sample(linearSampler, f3Refraction.xy);
			float4 f4ReflColor = tex2D[4].Sample(linearSampler, f3Reflection.xy);
			if (uReflectionMap)
			{
				float fReflectionFactor = tex2D[4].Sample(linearSampler, f2ParallaxTex).a;
				f4ColorOut += fReflectionFactor * (lerp(f4RefrColor, f4ReflColor, .5f) / f4ColorSSS.a)*(length(f4ColorOut.rgb)*length(f4ColorOut.rgb));
			}
			else
			{
				f4ColorOut += (lerp(f4RefrColor, f4ReflColor, .5f) / f4ColorSSS.a)*(length(f4ColorOut.rgb)*length(f4ColorOut.rgb));
			}
		}


	// Florian Schnell: dieser Fix erlaubt transparente Ambiente Texturen
	if (uImage)
		f4ColorOut.a = saturate(f4TexCol.a)*(1 - frTransparency) + f4ColorAmbient.a;
	else
		f4ColorOut.a = f4ColorAmbient.a;

	//TexBRDF nur mit normal- und heigtmap
	if (uTexBRDF && uBump && uPOM)
	{
		float3 f3LightDir;
		float3 f3LightColor;

		[unroll]
		for (uint i = 0; i < 1; i++)
		{
			AffectingLight alLight = input.aAffectingLights[i];
			f3LightDir = alLight.f3Direction;
			f3LightColor = alLight.f4Color.rgb;

			//if (f3LightColor.r > 0.01f)
				f4ColorOut.rgb += ((texBRDF(input, f4TexCol.rgb, f3LightColor, f4ColorAmbient.rgb, f3LightDir,f4Diffuse.rgb)) 
									/ (input.iLightCount * (20.f / f4SSSBRDFParams.g))
									* (length(f4ColorOut.rgb)*length(f4ColorOut.rgb)));
		}
	}

	//Subsurfacescattering
	if (uTexSSS)
	{
		const float fMaterialThickness = f4SSSBRDFParams.r;
		const float fRimScalar = f4SSSBRDFParams.b;
		const float fExtinctionCoefficientRed = f4ColorSSS.r;
		const float fExtinctionCoefficientGreen = f4ColorSSS.g;
		const float fExtinctionCoefficientBlue = f4ColorSSS.b;
		const float fSpecPower = 1.f;
		const float3 f3SpecColor = f4SpecCol.rgb;
		const float4 f4TexColor = tex2D[0].Sample(linearSampler, f2ParallaxTex);
		const float fThickValue = length(tex2D[6].Sample(linearSampler, f2ParallaxTex).rgb);
		float4 f4LightPos;
		float3 f3LightDir;
		float4 f4LightCol;
		float4 f4FinColor;

		[unroll]
		for (uint i = 0; i < input.iLightCount; i++)
		{
			AffectingLight alLight = input.aAffectingLights[i];
			float3 f3EyeVector = normalize(input.f3CamPos - input.f4VertexPos.xyz);
			f3LightDir = -f3EyeVector;
			f3LightDir = normalize(alLight.f3Direction);
			f4LightPos = alLight.f4LightPos;
			f4LightCol = alLight.f4Color;

			float fAttenuation = 10.f * (1.f / distance(f4LightPos, input.f4VertexPos));
			[branch]
			if (fAttenuation < 1.f)
				fAttenuation = 1.f;

			const float3 f3Eye = normalize(input.f3CamPos.xyz - input.f4VertexPos.xyz);
			float3 f3Normal = input.f3Normal;
			f3LightDir = f3LightDir;
			float4 f4DotLN = HalfLambert(f3LightDir, f3Normal) * fAttenuation;

			float3 f3IndirectLightComponent = (float3)(fMaterialThickness * max(0, dot(-f3Normal, f3LightDir)));
			f3IndirectLightComponent += HalfLambert(-f3Eye, f3LightDir)*fMaterialThickness;
			f3IndirectLightComponent *= fAttenuation;
			f3IndirectLightComponent.r *= fExtinctionCoefficientRed;
			f3IndirectLightComponent.g *= fExtinctionCoefficientGreen;
			f3IndirectLightComponent.b *= fExtinctionCoefficientBlue;
			f3IndirectLightComponent.rgb *= fThickValue;

			float3 f3Rim = (float3)(1.f - max(0.f, dot(f3Normal, f3Eye)));
			f3Rim *= f3Rim;
			f3Rim *= max(0.f, dot(f3Normal, f3LightDir)) * f3SpecColor;

			f4DotLN *= f4TexColor;

			f4FinColor = f4DotLN + float4(f3IndirectLightComponent, 1.f);
			f4FinColor.a = 1.f;
			f4FinColor.rgb += (f3Rim * fRimScalar * fAttenuation * f4FinColor.a);
			f4FinColor.rgb += (BlinnPhongSpec(f3Normal, f3LightDir, fSpecPower) * fAttenuation * f3SpecColor * f4FinColor.a * .05f);
			f4FinColor.rgb *= f4LightCol.rgb;

			if (alLight.iType == 3)
			{
				f4ColorOut *= f4FinColor;
				float fEdge = max(dot(normalize(input.f3CamPos - (float3)input.f4VertexPos), input.f3Normal), 0);
				[branch]
				if ((fEdge < 0.8f) && (fMaterialThickness > 2.f))
					f4ColorOut.rgb = f3IndirectLightComponent;
			}
		}
	}

	if (uStyleHalfTransparent) // Halftransparent
	{
		f4ColorOut *= 0.5;
	}
	if (uStyleOutlining) // Outline-Shading
	{
		float fEdge = max(dot(normalize(input.f3CamPos - (float3)input.f4VertexPos), input.f3Normal), 0);
		if (fEdge<f4ColorViewportOutline.a)
			f4ColorOut.rgb = f4ColorViewportOutline.rgb;

	}
	if (uStyleFog) // Nebel
	{
		f4ColorOut.rgb += length(input.f3CamPos - (float3)input.f4VertexPos) / f4FogParams.a; // Nebel
	}

	if (uStyleColor) // Style Colorize
	{
		f4ColorOut = mul(f4ColorOut, mColorModification);
	}

	if (uStyleOwn) // Own-Shading
	{
		// Hier ist Platz für Deinen eigenen Shader:
	}
	
	return f4ColorOut;
}
