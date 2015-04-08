//------------------------------------------------------------------
// Constants: Lighting constants for forward+ shaders
//
// Author: Patrick Fleischmann
// Letzte Änderung: 2014-09-11
//-------------------------------------------------------------------

#include "texandtexflags.h"
#include "ggxlighting.h"

//////////////////////////////////////////////////////////////////////////
//Shadow atlas
Texture2D g_PointShadowAtlas : register(t13);
Texture2D g_SpotShadowAtlas  : register(t14);

//////////////////////////////////////////////////////////////////////////
//Helper functions for shadow casting
int Vector3ToFace(float3 f3Vec)
{
	int iFace = 0;
	float fx = f3Vec.x;
	float fy = f3Vec.y;
	float fz = f3Vec.z;
	if ((abs(fx) > abs(fy)) && (abs(fx) > abs(fz)))
	{
		if (fx >= 0)
		{
			iFace = 0;
		}
		else
		{
			iFace = 1;
		}
	}
	else if ((abs(fy) > abs(fx)) && (abs(fy) > abs(fz)))
	{
		if (fy >= 0)
		{
			iFace = 2;
		}
		else
		{
			iFace = 3;
		}
	}
	else
	{
		if (fz >= 0)
		{
			iFace = 4;
		}
		else
		{
			iFace = 5;
		}
	}
	return iFace;
}

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

float FilterShadow(Texture2D atlas, float3 f3uv)
{
	float fShadow = 0.f;
	
	static const int iKernelLevel = 3;
	static const int iKernelWidth = 2 * iKernelLevel + 1;
	[unroll(iKernelWidth)] for (int i = -iKernelLevel; i <= iKernelLevel; i++)
	{
		[unroll(iKernelWidth)] for (int j = -iKernelLevel; j <= iKernelLevel; j++)
		{
			fShadow += atlas.SampleCmpLevelZero(g_ShadowSampler, f3uv.xy, f3uv.z, int2(i, j)).r;
		}
	}

	fShadow /= (iKernelWidth*iKernelWidth);
	return fShadow;
}

static const uint uNumDiscSamples = 16;
static const float2 f2DiscKernel[uNumDiscSamples] = {
	float2(0.2069841f, 0.2245269f),
	float2(0.525808f, -0.2310817f),
	float2(0.1383943f, 0.9056122f),
	float2(0.6633009f, 0.5129843f),
	float2(-0.4002792f, 0.3727058f),
	float2(0.07912822f, -0.6512921f),
	float2(-0.7726067f, -0.5151217f),
	float2(-0.3843193f, -0.1494132f),
	float2(-0.9107782f, 0.2500633f),
	float2(0.6940153f, -0.7098927f),
	float2(-0.1964669f, -0.379389f),
	float2(-0.4769286f, 0.1840863f),
	float2(-0.247328f, -0.8798459f),
	float2(0.4206541f, -0.714772f),
	float2(0.5829348f, -0.09794202f),
	float2(0.3691838f, 0.4140642f)
};

float FilterShadowRand(Texture2D atlas, float3 f3uv)
{
	float fShadow = 0.f;
	static const float fDivisor = 0.0002441f; // 1/4096
	static const int iKernelLevel = 2;
	static const int iKernelWidth = 2 * iKernelLevel + 1;
	[unroll(iKernelWidth)] for (int i = -iKernelLevel; i <= iKernelLevel; i++)
	{
		[unroll(iKernelWidth)] for (int j = -iKernelLevel; j <= iKernelLevel; j++)
		{
			float fFlatNum = i + iKernelLevel + j + iKernelLevel;
			/*fShadow += atlas.SampleCmpLevelZero(g_ShadowSampler,
												f3uv.xy + TexOffset2(i, j, 8192, 8192, 3.f, f2Pos),
												f3uv.z, int2(i, j)).r;*/
			fShadow += atlas.SampleCmpLevelZero(g_ShadowSampler,
				f3uv.xy + f2DiscKernel[fFlatNum] * fDivisor,
				f3uv.z, int2(i, j)).r;
		}
	}

	fShadow /= (iKernelWidth*iKernelWidth);
	return fShadow;
}

float ApplyPointShadow(uint uShadowIndex, in float3 f3Position, float3 f3LightDir, in float fDistanceTerm, in float2 f2TexCoordDiff)
{
	float3 f3uv = -f3LightDir;
	f3uv.z = -f3uv.z;

	int iFace = Vector3ToFace(f3uv.xyz);
	//f2TexCoordDiff = float2(0, 0);
	float4 f4ShadowTexCoord = mul(float4(f3Position, 1.f), g_mPointShadowViewProj[uShadowIndex][iFace]);
	f4ShadowTexCoord.xyz = f4ShadowTexCoord.xyz / f4ShadowTexCoord.w;

	f4ShadowTexCoord.x = f4ShadowTexCoord.x / 2.f + 0.5f;
	f4ShadowTexCoord.y = f4ShadowTexCoord.y / -2.f + 0.5f;

	f4ShadowTexCoord.x += iFace;
	f4ShadowTexCoord.x *= rcp(6);

	f4ShadowTexCoord.y += uShadowIndex;
	f4ShadowTexCoord.y *= rcp(MAX_SHADOWCASTING_LIGHT_NUM);

	f4ShadowTexCoord.z -= lerp(10.f, .1f, saturate(5 * fDistanceTerm)) * g_f4ShadowBias.w;

	return FilterShadow(g_PointShadowAtlas, f4ShadowTexCoord.xyz);
}

float ApplySpotShadow(uint uShadowIndex, in float3 f3Position)
{
	float4 f4ShadowTexCoord = mul(float4(f3Position, 1.f), g_mSpotShadowViewProj[uShadowIndex]);
	f4ShadowTexCoord.xyz = f4ShadowTexCoord.xyz / f4ShadowTexCoord.w;

	f4ShadowTexCoord.x = f4ShadowTexCoord.x /  2.f + 0.5f;
	f4ShadowTexCoord.y = f4ShadowTexCoord.y / -2.f + 0.5f;

	f4ShadowTexCoord.x += uShadowIndex;
	f4ShadowTexCoord.x *= rcp(MAX_SHADOWCASTING_LIGHT_NUM);

	f4ShadowTexCoord.z -= g_f4ShadowBias.w*6;

	return FilterShadow(g_SpotShadowAtlas, f4ShadowTexCoord.xyz);
}

//////////////////////////////////////////////////////////////////////////
void ApplyPointLighting(uniform bool bShadow, in Buffer<float4> pointLightCenterAndRadiusBuffer,
	in Buffer<float4> pointLightColorBuffer,
	in uint uLightIndex, in float3 f3Position,
	in float3 f3Norm, in float3 f3ViewDir,
	in float2 f2TexCoordDiff, in float4 f4SpecMapCol,
	in float4 f4DiffMapColor,
	out float3 f3LightColorDiffuseResult,
	out float3 f3LightColorSpecularResult)
{
	float4 f4CenterAndRadius = pointLightCenterAndRadiusBuffer[uLightIndex];

	float3 f3ToLight = f4CenterAndRadius.xyz - f3Position;
	float3 f3LightDir = normalize(f3ToLight);
	float fLightDistance = length(f3ToLight);

	f3LightColorDiffuseResult = float3(0.f, 0.0f, 0.f);
	f3LightColorSpecularResult = float3(0.f, 0.f, 0.f);

	float fRad = f4CenterAndRadius.w;
	if (fLightDistance < fRad)
	{
		float fx = fLightDistance / fRad;
		//inverse squared falloff :
		// -(1/k)*(1-(k+1)/(1+k*x^2))
		// k=20: -(1/20)*(1 - 21/(1+20*x^2))
		//float fFallOff = -0.05 + 1.05 / (1 + 20 * fx * fx);
		
		float fFallOff = fRad * (saturate(pow((1.f - pow(fx, 4)), 2))) / ((fLightDistance * fLightDistance) + 1);

		f3LightColorDiffuseResult = pointLightColorBuffer[uLightIndex].rgb * saturate(dot(f3LightDir, f3Norm)) * fFallOff;
		f3LightColorDiffuseResult *= fH;
		float3 f3HalfAngle = normalize(f3ViewDir + f3LightDir);
		//f3LightColorSpecularResult = pointLightColorBuffer[uLightIndex].rgb * pow(saturate(dot(f3HalfAngle, f3Norm)), fA) * fFallOff;
		float fSpecMul = fLightingFuncGGX(f3Norm, f3ViewDir, f3ToLight, fSpecularRoughness, fSpecularIOR);
		f3LightColorSpecularResult = pointLightColorBuffer[uLightIndex].rgb * fSpecMul * fFallOff;
		//f3LightColorDiffuseResult = pointLightColorBuffer[uLightIndex].rgb *
		//	BRDF(f3ToLight, f3ViewDir, f3Norm, fSpecularRoughness, fSpecularIOR, f4DiffMapColor.xyz) * fFallOff;
		
		[branch]
		if (uSpecularWhite)
			f3LightColorSpecularResult = 2 * (f3LightColorSpecularResult * f3LightColorDiffuseResult);
		else if (uSpecularAsImage)
			f3LightColorSpecularResult = 2 * f4SpecMapCol.xyz * (f3LightColorSpecularResult * f3LightColorDiffuseResult);
		else
			f3LightColorSpecularResult = 2 * f4SpecMapCol.xyz * (f3LightColorSpecularResult * f3LightColorDiffuseResult);
	
		if (bShadow)
		{
			float fShadowRes = ApplyPointShadow(uLightIndex, f3Position, f3LightDir, fx, f2TexCoordDiff);
			f3LightColorDiffuseResult *= fShadowRes;
			f3LightColorSpecularResult *= fShadowRes;
		}

		f3LightColorDiffuseResult *= 16;
		f3LightColorSpecularResult *= 16;
	}
}



//************************************
// Method:    	ApplySpotLighting
// FullName:  	ApplySpotLighting
// Description: Handles spot lighting and specular mapping
// Access:    	public 
// Returns:   	void
// Qualifier: 	
// Parameter: 	uniform bool bShadow
// Parameter: 	in Buffer<float4> spotLightCenterAndRadiusBuffer
// Parameter: 	in Buffer<float4> spotLightColorBuffer
// Parameter: 	in Buffer<float4> spotLightSpotParamsBuffer
// Parameter: 	in uint uLightIndex
// Parameter: 	in float3 f3Position
// Parameter: 	in float3 f3Norm
// Parameter: 	in float3 f3ViewDir
// Parameter: 	in float2 f2TexCoord
// Parameter: 	in float4 f4SpecMapCol
// Parameter: 	out float3 f3LightColorDiffuseResult
// Parameter: 	out float3 f3LightColorSpecularResult
//************************************
void ApplySpotLighting(uniform bool bShadow, in Buffer<float4> spotLightCenterAndRadiusBuffer,
											 in Buffer<float4> spotLightColorBuffer,
											 in Buffer<float4> spotLightSpotParamsBuffer,
											 in uint uLightIndex, in float3 f3Position,
											 in float3 f3Norm, in float3 f3ViewDir,
											 in float2 f2TexCoord, in float4 f4SpecMapCol,
											 in float4 f4DiffMapColor,
											 out float3 f3LightColorDiffuseResult,
											 out float3 f3LightColorSpecularResult)
{
	float4 f4BoundingSphereCenterAndRadius = spotLightCenterAndRadiusBuffer[uLightIndex];
	float4 f4SpotParams = spotLightSpotParamsBuffer[uLightIndex];

	// reconstruct z from lightdir
	float3 f3SpotLightDir;
	f3SpotLightDir.xy = f4SpotParams.xy;
	f3SpotLightDir.z = sqrt(1.f - f3SpotLightDir.x * f3SpotLightDir.x - f3SpotLightDir.y * f3SpotLightDir.y);

	// use cone angle bit sign to get the right direction for z
	f3SpotLightDir.z = (f4SpotParams.z > 0) ? f3SpotLightDir.z : -f3SpotLightDir.z;
	
	float3 f3LightPosition = f4BoundingSphereCenterAndRadius.xyz - f4BoundingSphereCenterAndRadius.w * f3SpotLightDir;

	float3 f3ToLight = f3LightPosition - f3Position;
	float3 f3ToLightNormalized = normalize(f3ToLight);
	float fLightDistance = length(f3ToLight);
	float fCosineOfCurrentAngle = dot(-f3ToLightNormalized, f3SpotLightDir);

	f3LightColorDiffuseResult = float3(0.f, 0.f, 0.f);
	f3LightColorSpecularResult = float3(0.f, 0.f, 0.f);

	float fRad = f4SpotParams.w;
	float fCosineOfConeAngle = (f4SpotParams.z > 0.f) ? f4SpotParams.z : -f4SpotParams.z;

	if (fLightDistance < fRad && fCosineOfCurrentAngle > fCosineOfConeAngle)
	{
		float fRadialAttenuation = (fCosineOfCurrentAngle - fCosineOfConeAngle) / (1.f - fCosineOfCurrentAngle);
		fRadialAttenuation = saturate(fRadialAttenuation * fRadialAttenuation);

		float fx = fLightDistance / fRad;
		//inverse squared falloff :
		// -(1/k)*(1-(k+1)/(1+k*x^2))
		// k=20: -(1/20)*(1 - 21/(1+20*x^2))
// 		float fK = 1.f;
// 		float fFallOff = -(1.f / fK) * (1.f - (fK + 1.f) / (1 + fK*fx*fx));
		//float fFallOff = -0.05 + 1.05 / (1 + 20 * fx * fx);
		float fFallOff = fRad * (saturate(pow((1.f - pow(fx, 4)), 2))) / ((fLightDistance * fLightDistance) + 1);
		f3LightColorDiffuseResult = spotLightColorBuffer[uLightIndex].rgb * saturate(dot(f3ToLightNormalized, f3Norm)) 
			* fFallOff * fRadialAttenuation;
		f3LightColorDiffuseResult *= fH;
		float3 f3HalfAngle = normalize(f3ViewDir + f3ToLightNormalized);
		//f3LightColorSpecularResult = spotLightColorBuffer[uLightIndex].rgb * pow(saturate(dot(f3HalfAngle, f3Norm)), fA)
		//	* fFallOff * fRadialAttenuation;
		float fSpecMul = fLightingFuncGGX(f3Norm, -f3ViewDir, f3ToLight, fSpecularRoughness, fSpecularIOR);
		f3LightColorSpecularResult = spotLightColorBuffer[uLightIndex].rgb * fSpecMul * fFallOff * fRadialAttenuation;
		//f3LightColorDiffuseResult = spotLightColorBuffer[uLightIndex].rgb *
		//	BRDF(f3ToLight, f3ViewDir, f3Norm, fSpecularRoughness, fSpecularIOR, f4DiffMapColor.xyz) * fFallOff * fRadialAttenuation;
		
		// specular mapping
		[branch]
		if (uSpecularWhite)
			f3LightColorSpecularResult = 2 * (f3LightColorSpecularResult * f3LightColorDiffuseResult);
		else if (uSpecularAsImage)
			f3LightColorSpecularResult = 2 * f4SpecMapCol.xyz * (f3LightColorSpecularResult * f3LightColorDiffuseResult);
		else
			f3LightColorSpecularResult = 2 * f4SpecMapCol.xyz * (f3LightColorSpecularResult * f3LightColorDiffuseResult);
		
		if (bShadow)
		{
			float fShadowRes = ApplySpotShadow(uLightIndex, f3Position);
			f3LightColorDiffuseResult *= fShadowRes;
			f3LightColorSpecularResult *= fShadowRes;
		}
		
 		f3LightColorDiffuseResult *= 16.f;
 		f3LightColorSpecularResult *= 16.f;
	}
}

void ApplyVPLLighting(in StructuredBuffer<float4> vplCenterAndRadiusBuffer, in StructuredBuffer<SVPLData> vplDataBuffer,
					  in uint uLightIndex, in float3 f3Position, in float3 f3Norm,
					  out float3 f3LightColorDiffuseResult)
{
	float4 f4CenterAndRadius = vplCenterAndRadiusBuffer[uLightIndex];
	SVPLData data = vplDataBuffer[uLightIndex];

	float3 f3ToLight = f4CenterAndRadius.xyz - f3Position;
	float3 f3LightDir = normalize(f3ToLight);
	float fLightDistance = length(f3ToLight);

	f3LightColorDiffuseResult = float3(0.f, 0.f, 0.f);

	float fRad = f4CenterAndRadius.w;
	float fVPLNormalDotDir = max(0.f, dot(data.f4Direction.xyz, -f3LightDir));

	if (fLightDistance < fRad && fVPLNormalDotDir > 0.f)
	{
		float3 f3LightColor = data.f4Color.rgb;

		float fx = fLightDistance / fRad;
		float fFallOff = smoothstep(1.f, 0.f, fx);
		
		float fSourceLightDotL = dot(data.f4SourceLightDirection.xyz, f3Norm);
		if (fSourceLightDotL < 0.f)
		{
			fSourceLightDotL = 1.f + (fSourceLightDotL / g_fVPLRemoveBackFaceContrib);
		}
		else
		{
			fSourceLightDotL = 1.f;
		}

		f3LightColorDiffuseResult = f3LightColor * saturate(dot(f3LightDir, f3Norm)) * fFallOff * fVPLNormalDotDir * fSourceLightDotL;
	}
}