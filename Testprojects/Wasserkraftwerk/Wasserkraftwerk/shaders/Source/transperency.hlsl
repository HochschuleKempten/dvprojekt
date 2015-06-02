#include "constant.h"
#include "lightingconstants.h"

///////////////////////////////////////////////////////////////////
// Buffer 
//StructuredBuffer<matrix> g_instanceTransform		: register(t0);

Buffer<float4> g_pointLightCenterAndRadiusBuffer	: register(t2);
Buffer<float4> g_pointLightColorBuffer				: register(t3);
Buffer<uint>   g_perTilePointLightIndexBuffer		: register(t4);

Buffer<float4> g_spotLightCenterAndRadiusBuffer		: register(t5);
Buffer<float4> g_spotLightColorBuffer				: register(t6);
Buffer<float4> g_spotLightParamsBuffer				: register(t7);
Buffer<uint>   g_perTileSpotLightIndexBuffer		: register(t8);

///////////////////////////////////////////////////////////////////
// VS in/out structure
struct VS_INPUT_ALPHA_BLENDED
{
	float4 f4Pos : POSITION;
	float3 f3Normal : NORMAL;
	float2 f2TexCoord : TEXCOORD;
	float3 f3Tangent : TANGENT;
	float3 f3Bitangent : BITANGENT;
};

struct VS_OUTPUT_ALPHA_BLENDED
{
	float4 f4Pos : SV_POSITION;
	float3 f3Normal : NORMAL;
	float3 f3VertexPos : TEXCOORD0;
	float2 f2TexCoord : TEXCOORD1;
	float3 f3Tangent : TANGENT;
	float3 f3Bitangent : BITANGENT;
	float3 f3CamPos : TEXCOORD2;
};

struct VS_OUTPUT_ALPHA_BLENDED_DEPTH
{
	float4 f4Pos : SV_POSITION;
};

///////////////////////////////////////////////////////////////////
// Functions for alpha lighting
void ApplyPointLightingTwoSided(in uint uLightIndex, in float3 f3Position, in float3 f3Norm, in float3 f3ViewDir,
								in float4 f4SpecMapCol, in float2 f2TexCoord,
								out float3 f3LightColorDiffuseFrontRes, out float3 f3LightColorSpecularFrontRes,
								out float3 f3LightColorDiffuseBackRes, out float3 f3LightColorSpecularBackRes)
{
	float4 f4CenterAndRadius = g_pointLightCenterAndRadiusBuffer[uLightIndex];

	float3 f3ToLight = f4CenterAndRadius.xyz - f3Position.xyz;
	float3 f3LightDir = normalize(f3ToLight);
	float fLightDistance = length(f3ToLight);

	f3LightColorDiffuseFrontRes = float3(0.f, 0.f, 0.f);
	f3LightColorSpecularFrontRes = float3(0.f, 0.f, 0.f);
	f3LightColorDiffuseBackRes = float3(0.f, 0.f, 0.f);
	f3LightColorSpecularBackRes = float3(0.f, 0.f, 0.f);

	float fRad = f4CenterAndRadius.w;
	if (fLightDistance < fRad)
	{
		float fx = fLightDistance / fRad;

		// -(1/k)*(1-(k+1)/(1+k*x^2))
		// k=20: -(1/20)*(1 - 21/(1+20*x^2))
		//float fFallOff = -0.05 + 1.05 / (1 + 20 * fx*fx);
		float fFallOff = fRad * (saturate(pow((1.f - pow(fx, 4)), 2))) / ((fLightDistance * fLightDistance) + 1);

		float3 f3LightColor = g_pointLightColorBuffer[uLightIndex].rgb;

		f3LightColorDiffuseFrontRes = f3LightColor * saturate(dot(f3LightDir, f3Norm)) * fFallOff;
		f3LightColorDiffuseFrontRes *= fH;
		f3LightColorDiffuseFrontRes *= 10;
		float3 f3HalfAngle = normalize(f3ViewDir + f3LightDir);

		//f3LightColorSpecularFrontRes = f3LightColor * pow(saturate(dot(f3HalfAngle, f3Norm)), fA) * fFallOff;
		float fSpecMul = fLightingFuncGGX(f3Norm, f3ViewDir, f3ToLight, fSpecularRoughness, fSpecularIOR);
		f3LightColorSpecularFrontRes = g_pointLightColorBuffer[uLightIndex].rgb * fSpecMul * fFallOff;
		f3LightColorSpecularFrontRes *= 10;

		f3LightColorDiffuseBackRes = f3LightColor * saturate(dot(f3LightDir, -f3Norm)) * fFallOff;
		f3LightColorDiffuseBackRes *= fH;
		f3LightColorDiffuseBackRes *= 10;

		//f3LightColorSpecularBackRes = f3LightColor * pow(saturate(dot(f3HalfAngle, -f3Norm)), fA) * fFalloff;
		f3LightColorSpecularBackRes = g_pointLightColorBuffer[uLightIndex].rgb * fSpecMul * fFallOff;
		f3LightColorSpecularBackRes *= 10;


		// specular mapping
		[branch]
		if (uSpecularWhite)
			f3LightColorSpecularFrontRes = 2 * (f3LightColorSpecularFrontRes * f3LightColorDiffuseFrontRes);
		else if (uSpecularAsImage)
			f3LightColorSpecularFrontRes = 2 * f4SpecMapCol.xyz * (f3LightColorSpecularFrontRes * f3LightColorDiffuseFrontRes);
		else
			f3LightColorSpecularFrontRes = 2 * f4SpecMapCol.xyz * (f3LightColorSpecularFrontRes * f3LightColorDiffuseFrontRes);

#if(SHADOWS_ENABLED == 1)
		float fShadowRes = ApplyPointShadow(uLightIndex, f3Position, f3LightDir, fx, f2TexCoord);
		f3LightColorDiffuseFrontRes *= fShadowRes;
		f3LightColorSpecularFrontRes *= fShadowRes;
		f3LightColorDiffuseBackRes *= fShadowRes;
		f3LightColorSpecularBackRes *= fShadowRes;
#endif
	}
}

void ApplySpotLightingTwoSided(in uint uLightIndex, in float3 f3Position, in float3 f3Norm, in float3 f3ViewDir,
							   in float4 f4SpecMapCol,
							   out float3 f3LightColorDiffuseFrontRes, out float3 f3LightColorSpecularFrontRes,
							   out float3 f3LightColorDiffuseBackRes, out float3 f3LightColorSpecularBackRes)
{
	float4 f4BoundingSphereAndRadius = g_spotLightCenterAndRadiusBuffer[uLightIndex];
	float4 f4SpotParams = g_spotLightParamsBuffer[uLightIndex];

	float3 f3SpotLightDir;
	f3SpotLightDir.xy = f4SpotParams.xy;
	f3SpotLightDir.z = sqrt(1.f - f3SpotLightDir.x*f3SpotLightDir.x - f3SpotLightDir.y*f3SpotLightDir.y);

	f3SpotLightDir.z = (f4SpotParams.z > 0.f) ? f3SpotLightDir.z : -f3SpotLightDir.z;

	float3 f3LightPosition = f4BoundingSphereAndRadius.xyz - f4BoundingSphereAndRadius.w*f3SpotLightDir;

	float3 f3ToLight = f3LightPosition - f3Position;
	float3 f3ToLightNorm = normalize(f3ToLight);
	float fLightDistance = length(f3ToLight);

	float fCosineOfCurrentConeAngle = dot(-f3ToLightNorm, f3SpotLightDir);
	
	f3LightColorDiffuseFrontRes = float3(0.f, 0.f, 0.f);
	f3LightColorSpecularFrontRes = float3(0.f, 0.f, 0.f);
	f3LightColorDiffuseBackRes = float3(0.f, 0.f, 0.f);
	f3LightColorSpecularBackRes = float3(0.f, 0.f, 0.f);

	float fRad = f4SpotParams.w;
	float fCosineOfConeAngle = (f4SpotParams.z > 0) ? f4SpotParams.z : -f4SpotParams.z;
	if (fLightDistance < fRad && fCosineOfCurrentConeAngle > fCosineOfConeAngle)
	{
		float fRadialAttenuation = (fCosineOfCurrentConeAngle - fCosineOfConeAngle) / (1.f - fCosineOfConeAngle);
		fRadialAttenuation = fRadialAttenuation*fRadialAttenuation;
		
		float fx = fLightDistance / fRad;
		// -(1/k)*(1-(k+1)/(1+k*x^2))
		// k=20: -(1/20)*(1 - 21/(1+20*x^2))
		//float fFallOff = -0.05 + 1.05 / (1 + 20 * fx*fx);
		float fFallOff = fRad * (saturate(pow((1.f - pow(fx, 4)), 2))) / ((fLightDistance * fLightDistance) + 1);
		float3 f3LightColor = g_spotLightColorBuffer[uLightIndex].rgb;

		f3LightColorDiffuseFrontRes = f3LightColor * saturate(dot(f3ToLightNorm, f3Norm)) * fFallOff * fRadialAttenuation;
		f3LightColorDiffuseFrontRes *= fH;
		f3LightColorDiffuseFrontRes *= 10;
		float3 f3HalfAngle = normalize(f3ViewDir + f3ToLightNorm);
		//f3LightColorSpecularFrontRes = f3LightColor * pow(saturate(dot(f3HalfAngle, f3Norm)), fA) * fFallOff * fRadialAttenuation;
		float fSpecMul = fLightingFuncGGX(f3Norm, f3ViewDir, f3ToLight, fSpecularRoughness, fSpecularIOR);
		f3LightColorSpecularFrontRes = g_spotLightColorBuffer[uLightIndex].rgb * fSpecMul * fFallOff * fRadialAttenuation;
		f3LightColorSpecularFrontRes *= 10;
		
		f3LightColorDiffuseBackRes = f3LightColor * saturate(dot(f3ToLightNorm, -f3Norm)) * fFallOff * fRadialAttenuation;
		f3LightColorDiffuseBackRes *= fH;
		f3LightColorDiffuseBackRes * 10;
		//f3LightColorSpecularBackRes = f3LightColor * pow(saturate(dot(f3HalfAngle, f3Norm)), fA) * fFallOff * fRadialAttenuation;
		f3LightColorSpecularBackRes = g_spotLightColorBuffer[uLightIndex].rgb * fSpecMul * fFallOff * fRadialAttenuation;
		f3LightColorSpecularBackRes *= 10;

		// specular mapping
		[branch]
		if (uSpecularWhite)
			f3LightColorSpecularFrontRes = 2 * (f3LightColorSpecularFrontRes * f3LightColorDiffuseFrontRes);
		else if (uSpecularAsImage)
			f3LightColorSpecularFrontRes = 2 * f4SpecMapCol.xyz * (f3LightColorSpecularFrontRes * f3LightColorDiffuseFrontRes);
		else
			f3LightColorSpecularFrontRes = 2 * f4SpecMapCol.xyz * (f3LightColorSpecularFrontRes * f3LightColorDiffuseFrontRes);
#if(SHADOWS_ENABLED == 1)
		float fShadowRes = ApplySpotShadow(uLightIndex, f3Position);
		f3LightColorDiffuseFrontRes *= fShadowRes;
		f3LightColorSpecularFrontRes *= fShadowRes;
		f3LightColorDiffuseBackRes *= fShadowRes;
		f3LightColorSpecularBackRes *= fShadowRes;
#endif
	}
}

///////////////////////////////////////////////////////////////////
// Shader for depth buffer 
VS_OUTPUT_ALPHA_BLENDED_DEPTH RenderBlendedDepthVS(VS_INPUT_ALPHA_BLENDED input)
{
	VS_OUTPUT_ALPHA_BLENDED_DEPTH output;

	float4 f4WorldPos = mul(float4(input.f4Pos), g_mWorld);
	output.f4Pos = mul(f4WorldPos, g_mViewProj);

	return output;
}

//////////////////////////////////////////////////////////////////
// VS shader for color buffer 
VS_OUTPUT_ALPHA_BLENDED RenderBlendedVS(VS_INPUT_ALPHA_BLENDED input)
{
	VS_OUTPUT_ALPHA_BLENDED output;

	float4 f4WorldPos = mul(input.f4Pos, g_mWorld);
	output.f4Pos = mul(f4WorldPos, g_mViewProj);
	output.f3VertexPos = f4WorldPos.xyz;
	output.f3Normal = mul(input.f3Normal, (float3x3)g_mWorld);
	output.f2TexCoord = input.f2TexCoord;
	output.f3Tangent = input.f3Tangent;

	float4 f4z;
	f4z.xyz = 0.f;
	f4z.w = 1.f;

	output.f3CamPos = mul(f4z, g_mViewInv).xyz;

	return output;
}

//////////////////////////////////////////////////////////////////
// PS shader for color buffer
float4 RenderBlendedPS(VS_OUTPUT_ALPHA_BLENDED input) : SV_TARGET
{
	float3 f3VertexPos = input.f3VertexPos;

	float3 f3AccumDiffuseFront = float3(0.f, 0.f, 0.f);
	float3 f3AccumSpecularFront = float3(0.f, 0.f, 0.f);
	float3 f3AccumDiffuseBack = float3(0.f, 0.f, 0.f);
	float3 f3AccumSpecularBack = float3(0.f, 0.f, 0.f);

	if (uiyPos>1 || uiyPics>1) // Animierte 
	{
		float fxPic = uixPos;
		float fyPic = uiyPos;
		float fxPics = uixPics;
		float fyPics = uiyPics;
		input.f2TexCoord.x = fxPic / fxPics + input.f2TexCoord.x*(1.f / fxPics);
		input.f2TexCoord.y = fyPic / fyPics + input.f2TexCoord.y*(1.f / fyPics);
	}

	///////////////////////////////////////////////////////////////////////
	// Transform normal into world space with BTN matrix
	float3 f3Norm = tex2D[3].Sample(g_Sampler, input.f2TexCoord).xyz;
	f3Norm *= 2;
	f3Norm -= float3(1, 1, 1);
	float3 f3N = normalize(input.f3Normal);
	/*const float3 f3T = input.f3Tangent;
	const float3 f3B = -input.f3Bitangent;// normalize(-cross(f3N, f3T));*/

	

	float4 f4SpecMapCol = float4(0.f, 0.f, 0.f, 0.f);
	if (uSpecular)
		f4SpecMapCol = tex2D[0].Sample(g_Sampler, input.f2TexCoord);

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

	///////////////////////////////////////////////////////////////////////
	// Normal mapping
	if (uBump)
	{
		float3 f3BumpNormal = ((2 * (tex2D[3].Sample(g_Sampler, input.f2TexCoord))) - 1.f).xyz;
			f3BumpNormal *= fBumpStrength;
		input.f3Normal += f3BumpNormal.x* f3T + f3BumpNormal.y * f3B;
		input.f3Normal = normalize(input.f3Normal);
	}

	
	float3x3 BTNMat = float3x3(f3B, f3T, f3N);
	f3Norm = normalize(mul(f3Norm, BTNMat));

	float3 f3ViewDir = normalize(g_f3CameraPos - f3VertexPos);

	// loop over point lights
	{
		uint uStartIndex, uLightCount;
		GetLightListInfo(g_perTilePointLightIndexBuffer, g_uMaxNumLightsPerTile, g_uMaxNumElementsPerTile, input.f4Pos,
						 uStartIndex, uLightCount);

		[loop]
		for (uint i = uStartIndex; i < uStartIndex + uLightCount; i++)
		{
			uint uLightIndex = g_perTilePointLightIndexBuffer[i];

			float3 f3LightColorDiffuseFrontRes = float3(0.f, 0.f, 0.f);
			float3 f3LightColorSpecularFrontRes = float3(0.f, 0.f, 0.f);
			float3 f3LightColorDiffuseBackRes = float3(0.f, 0.f, 0.f);
			float3 f3LightColorSpecularBackRes = float3(0.f, 0.f, 0.f);

			ApplyPointLightingTwoSided(uLightIndex, f3VertexPos, f3Norm, f3ViewDir, f4SpecMapCol, input.f2TexCoord,
									   f3LightColorDiffuseFrontRes, f3LightColorSpecularFrontRes,
									   f3LightColorDiffuseBackRes, f3LightColorSpecularBackRes);

			f3LightColorDiffuseFrontRes += (8.f*(1.f - frTransparency) * f3LightColorDiffuseFrontRes);
			f3LightColorDiffuseBackRes += (8.f*(1.f - frTransparency) * f3LightColorDiffuseBackRes);
			f3LightColorSpecularFrontRes += (8.f*(1.f - frTransparency) * f3LightColorSpecularFrontRes);
			f3LightColorSpecularBackRes += (8.f*(1.f - frTransparency) * f3LightColorSpecularBackRes);

			if (uTexSSS)
			{
				float4 f4CenterAndRadius = g_pointLightCenterAndRadiusBuffer[uLightIndex];
				float3 f3ToLight = f4CenterAndRadius.xyz - f3VertexPos;
				
				float3 f3LightCol = g_pointLightColorBuffer[uLightIndex].rgb;

				const float4 f4TexColor = tex2D[0].Sample(g_Sampler, input.f2TexCoord);
				const float fThickValue = length(tex2D[6].Sample(g_Sampler, input.f2TexCoord).rgb);

				SubsurfaceScattering(f4CenterAndRadius, f3ToLight, f3LightCol, f4TexColor, fThickValue, f4SSSBRDFParams,
									f4ColorSSS, float4(input.f3VertexPos,1.f), input.f3CamPos, input.f3Normal, true,
									f3LightColorSpecularFrontRes, f3LightColorDiffuseFrontRes);

				SubsurfaceScattering(f4CenterAndRadius, f3ToLight, f3LightCol, f4TexColor, fThickValue, f4SSSBRDFParams,
									 f4ColorSSS, float4(input.f3VertexPos,1.f), input.f3CamPos, input.f3Normal, true,
									 f3LightColorSpecularBackRes, f3LightColorDiffuseBackRes);

			}

			const float3 f3EyeVector = normalize(input.f3CamPos.xyz - input.f3VertexPos);
			const float3 f3ViewDir = -f3EyeVector;

			f3AccumDiffuseFront += f3LightColorDiffuseFrontRes;
			f3AccumSpecularFront += f3LightColorSpecularFrontRes;
			f3AccumDiffuseBack += f3LightColorDiffuseBackRes;
			f3AccumSpecularBack += f3LightColorSpecularBackRes;
		}
	}

	// loop over spot lights
	{
		uint uStartIndex, uLightCount;
		GetLightListInfo(g_perTileSpotLightIndexBuffer, g_uMaxNumLightsPerTile, g_uMaxNumElementsPerTile, input.f4Pos,
						 uStartIndex, uLightCount);

		[loop]
		for (uint i = uStartIndex; i < uStartIndex + uLightCount; i++)
		{
			uint uLightIndex = g_perTileSpotLightIndexBuffer[i];

			float3 f3LightColorDiffuseFrontRes = float3(0.f, 0.f, 0.f);
			float3 f3LightColorSpecularFrontRes = float3(0.f, 0.f, 0.f);
			float3 f3LightColorDiffuseBackRes = float3(0.f, 0.f, 0.f);
			float3 f3LightColorSpecularBackRes = float3(0.f, 0.f, 0.f);

			ApplySpotLightingTwoSided(uLightIndex, f3VertexPos, f3Norm, f3ViewDir, f4SpecMapCol,
									  f3LightColorDiffuseFrontRes, f3LightColorSpecularFrontRes,
									  f3LightColorDiffuseBackRes, f3LightColorSpecularBackRes);

			f3LightColorDiffuseFrontRes += (8.f*(1.f - frTransparency) * f3LightColorDiffuseFrontRes);
			f3LightColorDiffuseBackRes += (8.f*(1.f - frTransparency) * f3LightColorDiffuseBackRes);
			f3LightColorSpecularFrontRes += (8.f*(1.f - frTransparency) * f3LightColorSpecularFrontRes);
			f3LightColorSpecularBackRes += (8.f*(1.f - frTransparency) * f3LightColorSpecularBackRes);

			if (uTexSSS)
			{
				float4 f4CenterAndRadius = g_spotLightCenterAndRadiusBuffer[uLightIndex];
				float3 f3ToLight = f4CenterAndRadius.xyz - f3VertexPos;
				
				float3 f3LightCol = g_spotLightColorBuffer[uLightIndex].rgb;

				const float4 f4TexColor = tex2D[0].Sample(g_Sampler, input.f2TexCoord);
				const float fThickValue = length(tex2D[6].Sample(g_Sampler, input.f2TexCoord).rgb);

				SubsurfaceScattering(f4CenterAndRadius, f3ToLight, f3LightCol, f4TexColor, fThickValue, f4SSSBRDFParams,
									f4ColorSSS, float4(input.f3VertexPos,1.f), input.f3CamPos, input.f3Normal, true,
									f3LightColorSpecularFrontRes, f3LightColorDiffuseFrontRes);

				SubsurfaceScattering(f4CenterAndRadius, f3ToLight, f3LightCol, f4TexColor, fThickValue, f4SSSBRDFParams,
									f4ColorSSS, float4(input.f3VertexPos,1.f), input.f3CamPos, input.f3Normal, true,
									f3LightColorSpecularBackRes, f3LightColorDiffuseBackRes);

			}


			f3AccumDiffuseFront += f3LightColorDiffuseFrontRes;
			f3AccumSpecularFront += f3LightColorSpecularFrontRes;
			f3AccumDiffuseBack += f3LightColorDiffuseBackRes;
			f3AccumSpecularBack += f3LightColorSpecularBackRes;
		}
	}

	f3AccumDiffuseFront *= 2.f;
	f3AccumSpecularFront *= 8.f;
	f3AccumDiffuseBack *= 2.f;
	f3AccumSpecularBack *= 8.f;

	// Ambient cube map for front and back face
	float fAmbientBlendFront = 0.5f * f3Norm * 0.5f;
	float3 f3AmbientFront = g_f4AmbientColorUp.rgb * fAmbientBlendFront + g_f4AmbientColorDown.rgb * (1-fAmbientBlendFront);

	float fAmbientBlendBack = 0.5f * -f3Norm * 0.5f;
	float3 f3AmbientBack = g_f4AmbientColorUp.rgb * fAmbientBlendBack + g_f4AmbientColorDown.rgb * (1 - fAmbientBlendBack);

	// Accumulate
	float3 f3Color = tex2D[0].Sample(g_Sampler, input.f2TexCoord).xyz * 0.25f;
	float3 f3DiffuseAndAmbientFront = (f3AccumDiffuseFront * f3AmbientFront) + f3Color;
	float3 f3DiffuseAndAmbientBack = (f3AccumDiffuseBack * f3AmbientBack) + f3Color;
	float fBackFaceWeight = 0.5f;
	float3 f3AccumLight = f3DiffuseAndAmbientFront + f3AccumSpecularFront + (fBackFaceWeight * (f3DiffuseAndAmbientBack + f3AccumSpecularBack));

	float4 f4DiffTex = tex2D[0].Sample(g_Sampler, input.f2TexCoord);

	if (uChromaKeying) 
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

	float4 f4ColorOut = 2 * float4(f3AccumLight, 1.f);

	if (uEnvironment)
	{
		float3 f3EyeVector = normalize(input.f3CamPos - input.f3VertexPos);
		float3 f3Reflection = reflect(f3EyeVector, input.f3Normal);
		float3 f3Refraction = refract(f3EyeVector, input.f3Normal, .99f);

		float3 f3RefrColor = tex2D[4].Sample(g_Sampler, f3Refraction.xy).rgb;
		float3 f3ReflColor = tex2D[4].Sample(g_Sampler, f3Reflection.xy).rgb;
		if (uReflectionMap)
		{
			float fReflectionFactor = tex2D[4].Sample(g_Sampler, input.f2TexCoord).a;
			f4ColorOut.rgb *= fReflectionFactor * (lerp(f3RefrColor, f3ReflColor, .5f) / f4ColorSSS.a)*(length(f4ColorOut.rgb)*length(f4ColorOut.rgb));
		}
		else
		{
			f4ColorOut.rgb += (lerp(f3RefrColor, f3ReflColor, .5f) / f4ColorSSS.a)*(length(f4ColorOut.rgb)*length(f4ColorOut.rgb));
			//f4ColorOut.rgb += (lerp(f3RefrColor, f3ReflColor, .5f) / f4ColorSSS.a)*(length(f4ColorOut.rgb)*length(f4ColorOut.rgb));
		}
	}
	float fTrans = min(frTransparency, f4DiffTex.a);
	
	f4ColorOut.a = fTrans;

	return f4ColorOut;
}