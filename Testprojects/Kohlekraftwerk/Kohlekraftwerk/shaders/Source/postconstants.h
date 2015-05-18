
SamplerState linearSampler : register(s1);
SamplerState pointSampler : register(s2);

cbuffer ObjectInfo : register(b0)
{
	matrix World;
}

cbuffer TexInfo : register(b7)
{
	float4 f4ColorEffect : packoffset(c0);
	float fBlurStrength : packoffset(c1.x);
	uint uBlur : packoffset(c1.y);
	uint uEnhancedEdges : packoffset(c1.z);
	uint uMeanFilter : packoffset(c1.w);
	float fBloomOriginalIntensity : packoffset(c2.x);
	float fBloomIntensity : packoffset(c2.y);
	float fBloomOriginalSaturation : packoffset(c2.z);
	float fBloomSaturation : packoffset(c2.w);
	float fRayExposure : packoffset(c3.x);
	float fRayDecay : packoffset(c3.y);
	float fRayDensity : packoffset(c3.z);
	float fRayWeight : packoffset(c3.w);
	float fTimeDelta : packoffset(c4.x);
	float fBloomBlurDistance : packoffset(c4.y);
	float fDoFFar : packoffset(c4.z);
	float fDoFNear : packoffset(c4.w);
	float2 f2RayLightPos : packoffset(c5.x);
	float2 f2rcpFrame : packoffset(c5.z);
	float4 f4rcpFrameOpt : packoffset(c6);
	float4 f4DoFParams : packoffset(c7);
}

//////////////////////////////////////////////////////////////////////////
// Functions for tone mapping
float CalcLuminance(float3 f3Color)
{
	return max(dot(f3Color, float3(0.299f, 0.587f, 0.114f)), 0.0001f);
}

float GetAvgLuminance(Texture2D lumTex, float2 f2TexCoord)
{
	return exp(lumTex.SampleLevel(linearSampler, f2TexCoord, 10).x);
}

// Filmic curve from John Hable (ALU version from Haarm-Pieter Duiker’s curve)
float3 ToneMapFilmicALU(float3 f3Color)
{
	f3Color = max(0.f, f3Color - 0.004f);
	f3Color = (f3Color * (6.2f * f3Color + .5f)) / (f3Color * (6.2f * f3Color + 1.7f) + 0.06f);

	// Gamma = 2.2
	return pow(f3Color, 2.2f);
}

// Reinhard tone mapping
float3 ToneMapReinhard(float3 f3Color, float fSaturation)
{
	float fPixelLuminance = CalcLuminance(f3Color);
	float fToneMappedLuminance = fPixelLuminance / (fPixelLuminance + 1.f);
	return fToneMappedLuminance * pow(f3Color / fPixelLuminance, fSaturation);
}

float3 CalcExposedColor(float3 f3Color, float fAvgLuminance, float fThreshold, out float fExposure)
{
	fAvgLuminance = max(fAvgLuminance, 0.0001f);
	float fKeyVal = 1.f;
	float fLinearExposure = (fKeyVal / fAvgLuminance);
	fExposure = log2(max(fLinearExposure, 0.0001f));
	fExposure -= fThreshold;

	return exp2(fExposure) * f3Color;
}

float3 ToneMap(float3 f3Color, float fAvgLuminance, float fThreshold, float fSaturation, out float fExposure)
{
	float fPixelLuminance = CalcLuminance(f3Color);
	fExposure = 0.f;
	f3Color = CalcExposedColor(f3Color, fAvgLuminance, fThreshold, fExposure);
	f3Color = ToneMapFilmicALU(f3Color);
	//f3Color = ToneMapReinhard(f3Color, fSaturation);
	return f3Color;
}