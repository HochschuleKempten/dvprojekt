float G1V(float fDotNV, float fK)
{
	return 1.f / (fDotNV * (1.f - fK) + fK);
}

float fLightingFuncGGX(float3 f3N, float3 f3V, float3 f3L, float fRoughness, float fF0)
{
	f3N = normalize(f3N);
	
	float fAlpha = fRoughness * fRoughness;
	float3 f3H = normalize(f3V + f3L);

	float fDotNL = saturate(dot(f3N, f3L));
	float fDotNV = saturate(dot(f3N, f3V));
	float fDotNH = saturate(dot(f3N, f3H));
	float fDotLH = saturate(dot(f3L, f3H));

	float fF, fD, fVis;

	// Distribution term 
	float fAlphaSqr = fAlpha * fAlpha;
	const float fPi = 3.14159f;
	float fDenom = fDotNH * fDotNH * (fAlphaSqr - 1.f) + 1.f;
	fD = fAlphaSqr / (fPi * fDenom * fDenom);

	// Fresnel term
	float fDotLH5 = pow(1.f - fDotLH, 5);
	fF = fF0 + (1.f - fF0) * (fDotLH5);

	// Visibility term
	float fK = fAlpha / 2.f;
	fVis = G1V(fDotNL, fK) * G1V(fDotNV, fK);

	float fSpecular = fDotNL * fD * fF * fVis;
	return fSpecular;
}

// float2 LightingFuncGGX_FV(float fDotLH, float fRoughness)
// {
// 	float fAlpha = fRoughness * fRoughness;
// 
// 	// F
// 	float fFA, fFB;
// 	float fDotLH5 = pow(1.f - fDotLH, 5);
// 	fFA = 1.f;
// 	fFB = fDotLH5;
// 
// 	// V
// 	float fVis;
// 	float fK = fAlpha / 2.f;
// 	float fK2 = fK * fK;
// 	float fInvK2 = 1.f - fK2;
// 	fVis = rcp(fDotLH * fDotLH * fInvK2 + fK2);
// 
// 	return float2(fFA * fVis, fFB * fVis);
// }
// 
// float LightingFunctionGGX_D(float fDotNH, float fRoughness)
// {
// 	float fAlpha = fRoughness * fRoughness;
// 	float fAplhaSqr = fAlpha * fAlpha;
// 	const float fPI = 3.14159f;
// 	float fDenom = fDotNH * fDotNH * (fAplhaSqr - 1.f) + 1.f;
// 
// 	float fD = fAplhaSqr / (fPI * fDenom * fDenom);
// 	return fD;
// }

// float fLightingFuncGGX(float3 f3N, float3 f3V, float3 f3L, float fRoughness, float fF0)
// {
// 	float3 f3H = normalize(f3V + f3L);
// 
// 	float fDotNL = saturate(dot(f3N, f3L));
// 	float fDotLH = saturate(dot(f3L, f3H));
// 	float fDotNH = saturate(dot(f3N, f3H));
// 
// 	float fD = LightingFunctionGGX_D(fDotNH, fRoughness);
// 	float2 fFVHelper = LightingFuncGGX_FV(fDotLH, fRoughness);
// 	float fFV = fF0 * fFVHelper.x + (1.f - fF0) * fFVHelper.y;
// 	float fSpecular = fDotNL * fD * fFV;
// 
// 	return fSpecular;
// }



//////////////////////////////////////////////////////////////////////////

float SchlickFresnel(float fu)
{
	float fm = clamp(1.f - fu, 0, 1);
	float fm2 = fm * fm;
	return fm2 * fm2 * fm;
}

float fDiffuseLighting(float3 f3N, float3 f3V, float3 f3L, float fRoughness)
{
	float3 f3H = normalize(f3V + f3L);
	float fDotNL = saturate(dot(f3N, f3L));
	float fDotLH = saturate(dot(f3L, f3H));
	float fDotNV = saturate(dot(f3N, f3V));
	float fFL = SchlickFresnel(fDotNL), fFV = SchlickFresnel(fDotNV);
	float fFd90 = 0.5f + 2.f * fDotLH * fDotLH * fRoughness;
	float fPi = 3.14159f;
	return (1/fPi * ((lerp(1, fFd90, fFL) * lerp(1, fFd90, fFV))));
}

//////////////////////////////////////////////////////////////////////////

//static const float fPI = 3.14159265358979323846f;
//static const float3 f3BaseColor = float3(0.82f, 0.67f, 0.16f);
static const float3 f3BaseColor = float3(0.01f, 0.01f, 0.01f);
static const float fSpecular = 0.8f;
static const float fSpecularTint = 0.f;
static const float fMetallic = 0.f;
static const float fSubSurface = 0.f;
static const float fAnistropic = 0.f;
static const float fSheen = 0.f;
static const float fSheenTint = 0.f;
static const float fClearCoat = 0.f;
static const float fClearCoatGloss = 1.f;

float Sqr(float fx)
{
	return fx*fx;
}

float GTR1(float fDotNH, float fa)
{
	const float fPI = 3.14159265358979323846f;
	if (fa >= 1.f) return 1 / fPI;
	float fa2 = fa * fa;
	float fT = 1.f + (fa2 - 1.f) * fDotNH * fDotNH;
	return (fa2 - 1.f) / (fPI * log(fa2) * fT);
}

float GTR2(float fDotNH, float fa)
{
	const float fPI = 3.14159265358979323846f;
	float fa2 = fa + fa;
	float fT = 1.f + (fa2 - 1.f) * fDotNH * fDotNH;
	return fa2 / (fPI * fT * fT);
}

float GTR2Aniso(float fDotNH, float fDotHX, float fDotHY, float fax, float fay)
{
	const float fPI = 3.14159265358979323846f;
	return 1.f / (fPI * fax * fay * Sqr(Sqr(fDotHX / fax) + Sqr(fDotHY / fay) + fDotNH * fDotNH));
}

float SmithGGX(float fDotNV, float fAlphaG)
{
	float fa = fAlphaG * fAlphaG;
	float fb = fDotNV * fDotNV;
	return 1 / (fDotNV + Sqr(fa + fb - fa * fb));
}

float3 Mon2Lin(float3 f3Color)
{
	return float3(saturate(pow(f3Color.x, 2.2f)), saturate(pow(f3Color.y, 2.2f)), saturate(pow(f3Color.z, 2.2f)));
}

float3 BRDF(float3 f3L, float3 f3V, float3 f3N,  float fRoughness, float fF0, float3 f3Color)
{
	f3L = f3L;
	f3N = f3N;
	float3 f3C1 = cross(f3N, float3(0.f, 0.f, 1.f));
	float3 f3C2 = cross(f3N, float3(0.f, 1.f, 0.f));
	float3 f3X;
	[branch]
	if (length(f3C1) > length(f3C2))
	{
		f3X = normalize(f3C1);
	}
	else
	{
		f3X = normalize(f3C2);
	}
	float3 f3Y = normalize(-cross(f3N, f3X));

	const float fPI = 3.141592;
	float fDotNL = (dot(f3N, f3L));
	float fDotNV = (dot(f3N, f3V));

	if (fDotNL < 0) return float3(0.f, 0.f, 0.f);
	if (fDotNV < 0) return float3(0.f, 0.f, 0.f);
	float3 f3H = normalize(f3L + f3V);
	float fDotNH = (dot(f3N, f3H));
	float fDotLH = saturate(dot(f3L, f3H));

	float3 f3CdLin = Mon2Lin(f3Color);
	float fCdLum = 0.3f * f3CdLin.x + 0.6f * f3CdLin.y + 0.1f * f3CdLin.z;

	float3 f3CTint = fCdLum > 0 ? f3CdLin / fCdLum : float3(1.f, 1.f, 1.f);
	//					  spec												spectint		metallic		
	float3 f3CSpec0 = lerp(0.5f * 0.08f * lerp(float3(1.f, 1.f, 1.f), f3CTint, 0.5f), f3CdLin, 0.f);
														// sheentint
	float3 f3CSheen = lerp(float3(1.f, 1.f, 1.f), f3CTint, 0.f);

	float fFL = SchlickFresnel(fDotNL), fFV = SchlickFresnel(fDotNV);
	float fFd90 = 0.5f + 2 * fDotLH * fDotLH *fRoughness; 
	float fFd = (lerp(1, fFd90, fFL) * lerp(1, fFd90, fFV));

	float fFss90 = fDotLH * fDotLH * fRoughness;
	float fFss = lerp(1, fFss90, fFL) * lerp(1, fFss90, fFV);
	float fss = 1.5f * (fFss * (1 / (fDotNL + fDotNV) - 0.5f) + 0.5f);

							// anisotropic
	float fAspect = sqrt(1.f - 0.f * 0.9f);
	float fax = max(0.001f, Sqr(fRoughness) / fAspect);
	float fay = max(0.001f, Sqr(fRoughness) * fAspect);
	float fDs = GTR2Aniso(fDotNH, dot(f3H, f3X), dot(f3H, f3Y), fax, fay);
	float fFH = SchlickFresnel(fDotLH);
	float3 f3Fs = lerp(f3CSpec0, float3(1.f, 1.f, 1.f), fFH);
	float fRoughG = Sqr(fRoughness * 0.5f + 0.5f);
	float fGs = SmithGGX(fDotNL, fRoughG) * SmithGGX(fDotNV, fRoughG);
						 // fsheen
	float3 f3FSheen = fFH * 0.f * f3CSheen;
												//clearcoat gloss
	float fDr = GTR1(fDotNH, lerp(0.1f, 0.001, 1.f));
	float fFr = lerp(fF0, 1.f, fFH);
	float fGr = SmithGGX(fDotNL, 0.25f) * SmithGGX(fDotNV, 0.25f);
	//								subsurface			sheen		metaillic
	return (((1 / fPI) * lerp(fFd, fss, 0.f) * f3CdLin + 0.f) * (1.f - 0.f) + fGs * f3Fs * fDs + 0.25f *
		0.f * fGr * fFr * fDr);
	// clearcout
}