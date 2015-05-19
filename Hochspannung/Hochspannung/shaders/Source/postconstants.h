
SamplerState linearSampler : register(s1);
SamplerState pointSampler : register(s2);

cbuffer ObjectInfo : register(b0)
{
	matrix World;
}

cbuffer TexInfo : register(b7)
{
	float fBloomOriginalIntensity	: packoffset(c0.x);
	float fBloomIntensity			: packoffset(c0.y);
	float fBloomOriginalSaturation	: packoffset(c0.z);
	float fBloomSaturation			: packoffset(c0.w);
	float fRayExposure				: packoffset(c1.x);
	float fRayDecay					: packoffset(c1.y);
	float fRayDensity				: packoffset(c1.z);
	float fRayWeight				: packoffset(c1.w);
	float fTimeDelta				: packoffset(c2.x);
	float fBloomBlurDistance		: packoffset(c2.y);
	float fDoFFar					: packoffset(c2.z);
	float fDoFNear					: packoffset(c2.w);
	float fRcpFrameX				: packoffset(c3.x);
	float fRcpFrameY				: packoffset(c3.y);
	uint uPad5						: packoffset(c3.z);
	uint uPad6						: packoffset(c3.w);
	float4 f4GodRayPos				: packoffset(c4);
	float4 f4rcpFrameOpt			: packoffset(c5);
	float4 f4DoFParams				: packoffset(c6);
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