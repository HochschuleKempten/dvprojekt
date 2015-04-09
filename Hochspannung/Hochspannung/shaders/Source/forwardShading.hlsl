#include "constant.h"
#include "lightingconstants.h"

//////////////////////////////////////////////////////////////////////
// light buffers
Buffer<float4>	g_pointLightCenterAndRadiusBuffer	: register(t2);
Buffer<float4>	g_pointLightColorBuffer				: register(t3);
Buffer<uint>	g_perTilePointLightIndexBuffer		: register(t4);

Buffer<float4>	g_spotLightCenterAndRadiusBuffer	: register(t5);
Buffer<float4>	g_spotLightColorBuffer				: register(t6);
Buffer<float4>	g_spotLightSpotParamsBuffer			: register(t7);
Buffer<uint>	g_perTileSpotLightIndexBuffer		: register(t8);

#if(VPLS == 1)
StructuredBuffer<float4> g_VPLCenterAndRadiusBuffer : register(t9);
StructuredBuffer<SVPLData> g_VPLDataBuffer			: register(t10);
Buffer<uint> g_perTileVPLIndexBuffer				: register(t11);
#endif

///////////////////////////////////////////////////////////////////////
// VS in/out for scene rendering
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
	float4 f4Pos : SV_POSITION;
	float3 f3Normal : NORMAL;
	float3 f3Tangent : TANGENT;
	float3 f3Bitangent : BITANGENT;
	float2 f2TexCoord : TEXCOORD0;
	float3 f3CamPos : TEXCOORD1;
	float4 f4VertexPos : TEXCOORD2;
};

///////////////////////////////////////////////////////////////////////
// VS out for depth prepass
struct VS_OUTPUT_POSITION_ONLY
{
	float4 f4Pos : SV_POSITION;
};

///////////////////////////////////////////////////////////////////////
// VS out for depth prepass with alpha test
struct VS_OUTPUT_POSITION_AND_TEX
{
	float4 f4Pos : SV_POSITION;
	float2 f2TexCoord : TEXCOORD0;
};

///////////////////////////////////////////////////////////////////////
// VS for depth prepass
VS_OUTPUT_POSITION_ONLY RenderPositionOnlyVS(VS_INPUT input)
{
	VS_OUTPUT_POSITION_ONLY output;
	float4 f4WorldPos = mul(float4(input.f4Pos), g_mWorld);
	output.f4Pos = mul(f4WorldPos, g_mViewProj);

	return output;
}

///////////////////////////////////////////////////////////////////////
// VS for depth prepass with alpha test
VS_OUTPUT_POSITION_AND_TEX RenderPositionAndTexVS(VS_INPUT input)
{
	VS_OUTPUT_POSITION_AND_TEX output;
	float4 f4WorldPos = mul(float4(input.f4Pos), g_mWorld);
	output.f4Pos = mul(f4WorldPos, g_mViewProj);
	output.f2TexCoord = input.f2TexCoord;
	
	return output;
}

///////////////////////////////////////////////////////////////////////
// VS for scene rendering
VS_OUTPUT RenderSceneVS(VS_INPUT input)
{
	VS_OUTPUT output;
	float4 f4WorldPos = mul(input.f4Pos, g_mWorld);
	output.f4Pos = mul(f4WorldPos, g_mViewProj);
	output.f4VertexPos = f4WorldPos;
	output.f3Normal = mul(input.f3Normal, (float3x3)g_mWorld);
	output.f3Tangent = mul(input.f3Tangent, (float3x3)g_mWorld);
	output.f3Bitangent = mul(input.f3Bitangent, (float3x3)g_mWorld);
	output.f2TexCoord = input.f2TexCoord;

	float4 f4z;
	f4z.xyz = 0.f;
	f4z.w = 1.f;

	output.f3CamPos = mul(f4z, g_mViewInv).xyz;

	return output;
}

///////////////////////////////////////////////////////////////////////
// PS for alpha testing
float4 RenderAlphaTestOnlyPS(VS_OUTPUT_POSITION_AND_TEX input) : SV_TARGET
{
	if (uiyPos>1 || uiyPics>1) // Animierte 
	{
		float fxPic = uixPos;
		float fyPic = uiyPos;
		float fxPics = uixPics;
		float fyPics = uiyPics;
		input.f2TexCoord.x = fxPic / fxPics + input.f2TexCoord.x*(1.f / fxPics);
		input.f2TexCoord.y = fyPic / fyPics + input.f2TexCoord.y*(1.f / fyPics);
	}

	float4 f4DiffTex = tex2D[0].Sample(g_Sampler, input.f2TexCoord);

	if (uChromaKeying) // bChromaKeying
	{
			uint iWidth;
			uint iHeight;
			uint iLevels;
			tex2D[0].GetDimensions(0, iWidth, iHeight, iLevels);

			// Rechne Texturkoordinaten aus:
			float2 f2TexCoord2 = float2(input.f2TexCoord.x * iWidth, input.f2TexCoord.y * iHeight);
			int2 i2TexCoord = int2(input.f2TexCoord.x, input.f2TexCoord.y);

			// Hole Farbe des linken oberen Pixels
			int3 i3Pos = int3(0, 0, 0);
			float4 f4ChromaKey = tex2D[0].Load(i3Pos);
			i3Pos = int3(i2TexCoord.x, i2TexCoord.y, 0);
			float4 f4Texel = tex2D[0].Load(i3Pos);

			// ChromaKey Maskierung:
			if ((f4Texel.r == f4ChromaKey.r) && (f4Texel.g == f4ChromaKey.g) && (f4Texel.b == f4ChromaKey.b))
				f4DiffTex.a = 0;	// discard;

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
				f4DiffTex.a = fAlpha - 0.40; // etwas weiche Raender

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
			f4DiffTex = float4(
				(f4Col3.r - f4Col1.r) * f2TexPos1.y + f4Col1.r,
				(f4Col3.g - f4Col1.g) * f2TexPos1.y + f4Col1.g,
				(f4Col3.b - f4Col1.b) * f2TexPos1.y + f4Col1.b,
				fAlpha);

	}
	
	float fAlpha = f4DiffTex.a;
	if (fAlpha < g_fAlphaTest) discard;
	return f4DiffTex;
}

//////////////////////////////////////////////////////////////////////////
// Texture based BRDF
float3 texBRDF(VS_OUTPUT input,
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
	const float3 f3ht = tex2D[5].Sample(g_Sampler, f2huv).rgb;
	const float3 f3nt = tex2D[3].Sample(g_Sampler, f2nuv).rgb;
	const float3 f3nspec = f3ht + f3nt * f3LampColor * f3AmbiColor;
	return (f3DiffColor + f3nspec);
}

///////////////////////////////////////////////////////////////////////////
// PS for scene rendering
float4 RenderScenePS(VS_OUTPUT input) : SV_TARGET
{
	if (uiyPos>1 || uiyPics>1) // Animierte 
	{
		float fxPic = uixPos;
		float fyPic = uiyPos;
		float fxPics = uixPics;
		float fyPics = uiyPics;
		input.f2TexCoord.x = fxPic / fxPics + input.f2TexCoord.x*(1.f / fxPics);
		input.f2TexCoord.y = fyPic / fyPics + input.f2TexCoord.y*(1.f / fyPics);
	}

	float3 f3VertexPos = input.f4VertexPos.xyz / input.f4VertexPos.w;

	float3 f3AccumDiffuse = float3(0.f, 0.f, 0.f);
	float3 f3AccumSpecular = float3(0.f, 0.f, 0.f);

	float2 f2ParallaxTex = input.f2TexCoord;

	float3 f3N = normalize(input.f3Normal);
	
	float3 f3C1 = cross(f3N, float3(0.f, 0.f, 1.f));
	float3 f3C2 = cross(f3N, float3(0.f, 1.f, 0.f));
	float3 f3T;
	[branch]
	if (length(f3C1) > length(f3C2))
	{
		f3T = normalize(f3C1);
	}
	else
	{
		f3T = normalize(f3C2);
	}
	float3 f3B = normalize(-cross(f3N, f3T));

	///////////////////////////////////////////////////////////////////////
	// POM (Highttracing)
	if (uPOM == 1)
	{
		const float3 f3EyeVector = normalize(input.f3CamPos.xyz - input.f4VertexPos.xyz);
		const float3 f3ViewDir = -f3EyeVector;

		const float3x3 f3x3ToTangent = transpose(float3x3(f3T, f3B, f3N));
		const float3 f3ViewDirTS = mul(f3ViewDir, f3x3ToTangent);

		const float2 f2MaxParallaxOffset = -f3ViewDirTS.xy * 0.02f / f3ViewDirTS.z;

		const int iSampleCount = ((int)lerp(20, 5, dot(-f3EyeVector, f3N)));

		const float fZStep = 1.f / (float)iSampleCount;
		const float2 f2TexStep = f2MaxParallaxOffset * fZStep;

		const float2 f2Dx = ddx(f2ParallaxTex);
		const float2 f2Dy = ddy(f2ParallaxTex);

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
			fCurHeight = tex2D[5].SampleGrad(g_Sampler, f2ParallaxTex + f2CurTexOffset, f2Dx, f2Dy).r;
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

		f2ParallaxTex = f2ParallaxTex + f2FinalTexOffset;

		const float fHeightX = (tex2D[5].Sample(g_Sampler, f2ParallaxTex).g);
		const float fHeightY = (tex2D[5].Sample(g_Sampler, f2ParallaxTex).g);

		input.f3Normal += ((fHeightX * f3T) + (fHeightY * f3B));
		input.f3Normal = normalize(input.f3Normal);
	}

	///////////////////////////////////////////////////////////////////////
	// POM (Conetracing)
	if (uPOM == 2) 
	{
		const int iConeSteps = 15;
		const int iBinarySteps = 6;

		const float3 f3EyeVector = normalize(input.f3CamPos.xyz - input.f4VertexPos.xyz);
		const float3 f3ViewDir = f3EyeVector;

		const float3x3 f3x3ToTangent = transpose(float3x3(f3T, input.f3Bitangent, f3N));
		const float3 f3ViewDirTS = mul(f3ViewDir, f3x3ToTangent);

		float3 f3RayDir = normalize(f3ViewDirTS);
		f3RayDir /= f3RayDir.z;
		//float fRayRatio = length(f3RayDir.xy);
		float fRayRatio = 1.f;
		float3 f3Pos = float3(f2ParallaxTex, 0.f);
		//float fRayRatio = (lerp(10.f, 0.f, dot(-f3EyeVector, input.f3Normal)));
		[unroll]
		for (int i = 0; i < iConeSteps; i++)
		{
			float4 f4Tex = tex2D[5].Sample(g_Sampler, f3Pos.xy);
			float fConeRatio = f4Tex.z;
			float fHeight = saturate(f4Tex.w - f3Pos.z);
			float fD = (fConeRatio*fHeight / (fRayRatio + fConeRatio))*0.01f;
			f3Pos += f3RayDir * fD;
		}

		float3 f3BinSearchRange = 0.5f * f3RayDir * f3Pos.z;
		float3 f3BinSearchPosition = float3(f2ParallaxTex, 0.f) + f3BinSearchRange;
		[unroll]
		for (int i = 0; i < iBinarySteps; i++)
		{
			float4 f4Tex = tex2D[5].Sample(g_Sampler, f3BinSearchPosition.xy);
			f3BinSearchRange *= 0.5f;
			[branch]
			if (f3BinSearchPosition.z < f4Tex.w)
				f3BinSearchPosition += f3BinSearchRange;
			else
				f3BinSearchPosition -= f3BinSearchRange;
		}

		f2ParallaxTex = f3BinSearchPosition.xy;

		const float fHeightX = (tex2D[5].Sample(g_Sampler, f3BinSearchPosition.xy).w);
		const float fHeightY = (tex2D[5].Sample(g_Sampler, f3BinSearchPosition.xy).w);

		input.f3Normal += ((fHeightX)* f3T + (fHeightY)* f3B);
		input.f3Normal = normalize(input.f3Normal);
	}

	float2 f2TexCoordDiff = f2ParallaxTex - input.f2TexCoord;

	float4 f4DiffTex = tex2D[0].Sample(g_Sampler, f2ParallaxTex);
#if(USE_APLHA_TEST == 1)
	float fSpecMasc = 0.f;
	float fAlpha = f4DiffTex.a;
	if (fAlpha < g_fAlphaTest) discard;
#else
	float fSpecMasc = f4DiffTex.a;
#endif
	
	///////////////////////////////////////////////////////////////////////
	// Normal mapping
	if (uBump)
	{
		float3 f3BumpNormal = ((2 * (tex2D[3].Sample(g_Sampler, f2ParallaxTex))) - 1.f).xyz;
		f3BumpNormal *= fBumpStrength;
		input.f3Normal += f3BumpNormal.x * input.f3Tangent + -f3BumpNormal.y * input.f3Bitangent;
		input.f3Normal = normalize(input.f3Normal);
	}
	float3 f3Norm = input.f3Normal;
	float3 f3ViewDir = normalize(g_f3CameraPos - f3VertexPos);
	
	///////////////////////////////////////////////////////////////////////
	// Get color for specular mapping
	float4 f4SpecMapCol = float4(0.f, 0.f, 0.f, 0.f);
	if (uSpecular)
		f4SpecMapCol = tex2D[0].Sample(g_Sampler, f2ParallaxTex);


	///////////////////////////////////////////////////////////////////////
	// Ambient cubemap blending
	float fAmbientBlend = 0.5f * f3Norm.y + 0.5f;
	float3 f3Ambient = g_f4AmbientColorUp.rgb * fAmbientBlend + g_f4AmbientColorDown.rgb * (1.f - fAmbientBlend);

	///////////////////////////////////////////////////////////////////////
	// Handle point lights
	{
		uint uStartIndex, uLightCount;
		GetLightListInfo(g_perTilePointLightIndexBuffer, g_uMaxNumLightsPerTile, g_uMaxNumElementsPerTile, input.f4Pos,
			uStartIndex, uLightCount);

		[loop]
		for (uint i = uStartIndex; i < uStartIndex + uLightCount; i++)
		{
			uint uLightIndex = g_perTilePointLightIndexBuffer[i];

			float3 f3LightColorDiffuseResult = float3(0.f, 0.f, 0.f);
			float3 f3LightColorSpecularResult = float3(0.f, 0.f, 0.f);
#if(SHADOWS_ENABLED == 1)
			ApplyPointLighting(true, g_pointLightCenterAndRadiusBuffer, g_pointLightColorBuffer, uLightIndex, f3VertexPos,
			f3Norm, f3ViewDir, f2TexCoordDiff, f4DiffTex, f4SpecMapCol, f3LightColorDiffuseResult, f3LightColorSpecularResult);
#else
			ApplyPointLighting(false, g_pointLightCenterAndRadiusBuffer, g_pointLightColorBuffer, uLightIndex, f3VertexPos,
			f3Norm, f3ViewDir, f2TexCoordDiff, f4DiffTex, f4SpecMapCol, f3LightColorDiffuseResult, f3LightColorSpecularResult);
#endif
			
			// Subsurface scattering 
			if (uTexSSS)
			{
				float4 f4CenterAndRadius = g_pointLightCenterAndRadiusBuffer[uLightIndex];
				float3 f3ToLight = f4CenterAndRadius.xyz - f3VertexPos;
				float3 f3LightCol = g_pointLightColorBuffer[uLightIndex].rgb;

				const float4 f4TexColor = tex2D[0].Sample(g_Sampler, f2ParallaxTex);
				const float fThickValue = length(tex2D[6].Sample(g_Sampler, f2ParallaxTex).rgb);

				SubsurfaceScattering(f4CenterAndRadius, f3ToLight, f3LightCol, f4TexColor, fThickValue, f4SSSBRDFParams,
									f4ColorSSS, input.f4VertexPos, input.f3CamPos, f3Norm, true,
									f3LightColorSpecularResult, f3LightColorDiffuseResult);

			}

			f3AccumDiffuse += f3LightColorDiffuseResult;
			f3AccumSpecular += f3LightColorSpecularResult;
		}
	}
	
	///////////////////////////////////////////////////////////////////////
	// Handle spot lights
	{
		uint uStartIndex, uLightCount;
		GetLightListInfo(g_perTileSpotLightIndexBuffer, g_uMaxNumLightsPerTile, g_uMaxNumElementsPerTile, input.f4Pos,
			uStartIndex, uLightCount);
		[loop]
		for (uint i = uStartIndex; i < uStartIndex + uLightCount; i++)
		{
			uint uLightIndex = g_perTileSpotLightIndexBuffer[i];

			float3 f3LightColorDiffuseResult = float3(0.f, 0.f, 0.f);
			float3 f3LightColorSpecularResult = float3(0.f, 0.f, 0.f);
#if(SHADOWS_ENABLED == 1)
			ApplySpotLighting(true, g_spotLightCenterAndRadiusBuffer, g_spotLightColorBuffer, g_spotLightSpotParamsBuffer,
			uLightIndex, f3VertexPos, f3Norm, f3ViewDir, f2TexCoordDiff, f4SpecMapCol, f4DiffTex,
			f3LightColorDiffuseResult, f3LightColorSpecularResult);
#else
			ApplySpotLighting(false, g_spotLightCenterAndRadiusBuffer, g_spotLightColorBuffer, g_spotLightSpotParamsBuffer,
			uLightIndex, f3VertexPos, f3Norm, f3ViewDir, f2TexCoordDiff, f4SpecMapCol, f4DiffTex,
			f3LightColorDiffuseResult, f3LightColorSpecularResult);
#endif
			
			// Subsurface scattering 
			if (uTexSSS)
			{
				float4 f4CenterAndRadius = g_spotLightCenterAndRadiusBuffer[uLightIndex];
				float3 f3ToLight = f4CenterAndRadius.xyz - f3VertexPos;
				float3 f3LightCol = g_spotLightColorBuffer[uLightIndex].rgb;

				const float4 f4TexColor = tex2D[0].Sample(g_Sampler, f2ParallaxTex);
				const float fThickValue = length(tex2D[6].Sample(g_Sampler, f2ParallaxTex).rgb);

				SubsurfaceScattering(f4CenterAndRadius, f3ToLight, f3LightCol, f4TexColor, fThickValue, f4SSSBRDFParams,
									 f4ColorSSS, input.f4VertexPos, input.f3CamPos, f3Norm, false,
									 f3LightColorSpecularResult, f3LightColorDiffuseResult);
			}

			f3AccumDiffuse += f3LightColorDiffuseResult;
			f3AccumSpecular += f3LightColorSpecularResult;
		}
	}

#if(VPLS == 1)
    ///////////////////////////////////////////////////////////////////////
	// Handle vpls
	{
		uint uStartIndex, uLightCount;
		GetLightListInfo(g_perTileVPLIndexBuffer, g_uMaxNumVPLsPerTile, g_uMaxNumVPLElementsPerTile, input.f4Pos,
			uStartIndex, uLightCount);

		[loop]
		for (uint i = uStartIndex; i < uStartIndex + uLightCount; i++)
		{
			uint uLightIndex = g_perTileVPLIndexBuffer[i];

			float3 f3LightColorDiffuseResult = float3(0.f, 0.f, 0.f);

			ApplyVPLLighting(g_VPLCenterAndRadiusBuffer, g_VPLDataBuffer, uLightIndex, f3VertexPos, f3Norm,
			f3LightColorDiffuseResult);

			float3 f3LightColorSpecularResult = float3(0.f, 0.f, 0.f);
			// Subsurface scattering 
			if (uTexSSS)
			{
				float4 f4CenterAndRadius = g_VPLCenterAndRadiusBuffer[uLightIndex];
				float3 f3ToLight = f4CenterAndRadius.xyz - f3VertexPos;
				float3 f3LightCol = g_VPLDataBuffer[uLightIndex].f4Color.rgb;

				const float4 f4TexColor = tex2D[0].Sample(g_Sampler, f2ParallaxTex);
				const float fThickValue = length(tex2D[6].Sample(g_Sampler, f2ParallaxTex).rgb);

				SubsurfaceScattering(f4CenterAndRadius, f3ToLight, f3LightCol, f4TexColor, fThickValue, f4SSSBRDFParams,
									 f4ColorSSS, input.f4VertexPos, input.f3CamPos, f3Norm, true,
									 f3LightColorSpecularResult, f3LightColorDiffuseResult);

			}

			f3AccumDiffuse += f3LightColorDiffuseResult;
		}
	}
#endif

	f3AccumDiffuse *= .5f;
	f3AccumSpecular *= 2.f;

	///////////////////////////////////////////////////////////////////////
	// Glow mapping
	float4 f4Glow = 0.f;
	if (uGlow) // TEXFLAG_GLOW
	{
		float4 f4Amb = float4(1.f, 1.f, 1.f, 1.f);
		if (uGlowAsAmbient) // TEXFLAG_GLOWASAMBIENT
			f4Glow = float4(f3Ambient, 1.f);
		else
		{
			if (uGlowAsImage) // TEXFLAG_GLOWASIMAGE
				f4Glow = tex2D[0].Sample(g_Sampler, f2ParallaxTex)* saturate(1 - float4(f3Ambient, 1.f));
			else
				f4Glow = tex2D[1].Sample(g_Sampler, f2ParallaxTex)* saturate(1 - float4(f3Ambient, 1.f));
		}
	}
	else
		f4Glow = 0.f;
	
	///////////////////////////////////////////////////////////////////////
	// Ambient/Specular/Diffuse integration
	f3AccumDiffuse += f4Glow*0.75;
	float3 f3DiffuseAndAmbient = f3AccumDiffuse + f3Ambient;
	float4 f4ColorOut = float4(0.f, 0.f, 0.f, 1.f);
	if(uShadingOn) // bShading
	{	
		f4ColorOut = float4((f4DiffTex.xyz*(f3DiffuseAndAmbient + f3AccumSpecular * fSpecMasc)), 1.f);
	}
	else
	{
		f4ColorOut = float4(f4DiffTex.xyz, 1);
	}	
	/*float3 ambient = f3Ambient * f4DiffTex.xyz;
	float3 spec = f3AccumSpecular *  f4DiffTex.xyz;
	f4ColorOut = float4(f3AccumDiffuse + ambient + (spec * fSpecMasc), 1.f);*/
	
	///////////////////////////////////////////////////////////////////////
	// Environmentmapping
	if (uEnvironment)
	{
		float3 f3EyeVector = normalize(input.f3CamPos - input.f4VertexPos.xyz);
		float3 f3Reflection = reflect(f3EyeVector, f3Norm);
		float3 f3Refraction = refract(f3EyeVector, f3Norm, .99f);

		float4 f4RefrColor = tex2D[4].Sample(g_Sampler, f3Refraction.xy);
		float4 f4ReflColor = tex2D[4].Sample(g_Sampler, f3Reflection.xy);
		if (uReflectionMap)
		{
			float fReflectionFactor = tex2D[4].Sample(g_Sampler, f2ParallaxTex).a;
			f4ColorOut += fReflectionFactor * (lerp(f4RefrColor, f4ReflColor, .5f) / f4ColorSSS.a)*(length(f4ColorOut.rgb)*length(f4ColorOut.rgb));
		}
		else
		{
			f4ColorOut += (lerp(f4RefrColor, f4ReflColor, .5f) / f4ColorSSS.a)*(length(f4ColorOut.rgb)*length(f4ColorOut.rgb));
		}
	}

	///////////////////////////////////////////////////////////////////////
	// Halftransparent
	if (uStyleHalfTransparent) 
	{
		f4ColorOut *= 0.5;
	}

	if (uStyleOutlining) // Outline-Shading
	{
		float fEdge = max(dot(normalize(input.f3CamPos - (float3)input.f4VertexPos), f3Norm), 0);
		if (fEdge<f4ColorViewportOutline.a)
			f4ColorOut.rgb = f4ColorViewportOutline.rgb;

	}

	///////////////////////////////////////////////////////////////////////
	// Nebel
	if (uStyleFog) 
	{
		f4ColorOut.rgb += length(input.f3CamPos - (float3)input.f4VertexPos) / f4FogParams.a; // Nebel
	}

	///////////////////////////////////////////////////////////////////////
	// Style Colorize
	if (uStyleColor) 
	{
		f4ColorOut = mul(f4ColorOut, mColorModification);
	}

	///////////////////////////////////////////////////////////////////////
	// Own-Shading
	if (uStyleOwn) 
	{
		// Hier ist Platz für Deinen eigenen Shader:
	}

	return f4ColorOut;
}