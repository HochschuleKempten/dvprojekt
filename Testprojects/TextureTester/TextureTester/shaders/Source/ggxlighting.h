static const float fPI = 3.14159265358979323846f;

float G1V(in float fDotNV, in float fK)
{
	return 1.f / (fDotNV * (1.f - fK) + fK);
}

float fLightingFuncGGX(in float3 f3N, in float3 f3V, in float3 f3L, in float fRoughness, in float fF0)
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

float SchlickFresnel(in float fu)
{
	float fm = clamp(1.f - fu, 0, 1);
	float fm2 = fm * fm;
	return fm2 * fm2 * fm;
}

float OrenNayar(in float3 f3L, in float3 f3V, in float3 f3N, in float3 f3X, in float3 f3Y, in float fRoughness, in float F0)
{
	float fSigma = fRoughness;
	float fRho = 2.5f;

	float fVDotN = dot(f3V, f3N);
	float fLDotN = dot(f3L, f3N);

	float f3Llength = length(f3L);
	float f3Vlength = length(f3V);

	fVDotN /= f3Vlength;
	fLDotN /= f3Llength;

	float fThetaR = acos(fVDotN);
	float fSigma2 = pow(fSigma * fPI / 180.f, 2);
	
	float fCosPhiDiff = dot(normalize(f3V - f3N * fVDotN), normalize(f3L - f3N * fLDotN));
	float fThetaI = acos(fLDotN);
	float fAlpha = max(fThetaI, fThetaR);
	float fBeta = min(fThetaI, fThetaR);
	[branch]
	if (fAlpha > fPI / 2.f) return float3(0.f, 0.f, 0.f);

	float fC1 = 1.f - 0.5f * fSigma2 / (fSigma2 + 0.33f);
	float fC2 = 0.45f * fSigma2 / (fSigma2 + 0.09f);
	[branch]
	if (fCosPhiDiff >= 0.f) fC2 *= sin(fAlpha);
	else fC2 *= (sin(fAlpha) - pow(2 * fBeta / fPI, 3));
	float fC3 = 0.125 * fSigma2 / (fSigma2 + 0.09f) * pow((4 * fAlpha * fBeta) / (fPI * fPI), 2);
	float fL1 = fRho / fPI * (fC1 + fCosPhiDiff * fC2 * tan(fBeta) + (1.f - abs(fCosPhiDiff)) * fC3 
				* tan((fAlpha + fBeta) / 2.f));
	float fL2 = 0.17f * fRho * fRho / fPI * fSigma2 / (fSigma2 + 0.13f) * (1.f - fCosPhiDiff * (4 * fBeta * fBeta) 
				/ (fPI * fPI));
	return (fL1 + fL2);
}
//////////////////////////////////////////////////////////////////////////

float Sqr(in float fx)
{
	return fx*fx;
}

float GTR1(in float fDotNH, in float fa)
{
	if (fa >= 1.f) return 1 / fPI;
	float fa2 = fa * fa;
	float fT = 1.f + (fa2 - 1.f) * fDotNH * fDotNH;
	return (fa2 - 1.f) / (fPI * log(fa2) * fT);
}

float GTR2(in float fDotNH, in float fa)
{
	float fa2 = fa * fa;
	float fT = 1.f + (fa2 - 1.f) * fDotNH * fDotNH;
	return fa2 / (fPI * fT * fT);
}

float GTR2Aniso(in float fDotNH, in float fDotHX, in float fDotHY, in float fax, in float fay)
{
	return (1.f / (fPI * fax * fay * Sqr(Sqr(fDotHX / fax) + Sqr(fDotHY / fay) + fDotNH * fDotNH)));
}

float SmithG_GGX(in float fDotNV, in float fAlphaG)
{
	float fa = fAlphaG * fAlphaG;
	float fb = fDotNV * fDotNV;
	return 1.f / (fDotNV + Sqr(fa + fb - fa * fb));
}

float3 Mon2Lin(in float3 f3Color)
{
	return float3(pow(abs(f3Color.x), 2.2f), pow(abs(f3Color.y), 2.2f), pow(abs(f3Color.z), 2.2f));
}

float RoughnessToSpecPower(in float fM)
{
	return 2.f / (fM * fM) - 2.f;
}

float Beckmann_G1(float fm, float fDotNX)
{
	float fDotNX2 = fDotNX * fDotNX;
	float fTanTheta = sqrt((1.f - fDotNX2) / fDotNX2);
	float fa = 1.f / (fm * fTanTheta);
	float fa2 = fa * fa;
	float fg = 1.f;
	[branch]
	if (fa < 1.6f)
		fg *= (3.535f * fa + 2.181f * fa2) / (1.0f + 2.276f * fa + 2.577f * fa2);
	return fg;
}

float LeanMapping(float2 f2LeanB, float3 f3LeanM, float3 f3Ht)
{
	float2 f2B = f2LeanB * 0.01f;
	float3 f3M = f3LeanM.xyz * 0.0001f * 0.5f;
	float fInvS = 1.f / RoughnessToSpecPower(fRoughness / 5.f);
	f3M.xy += (fInvS);
	float3 f3Sigma = f3M - float3(f2B * f2B, f2B.x * f2B.y);
	float fDet = f3Sigma.x * f3Sigma.y - f3Sigma.z * f3Sigma.z;
	float fD = 0.f;
	float2 f2H = f3Ht.xy / f3Ht.z - f2B;
	float fE = (f2H.x * f2H.x * f3Sigma.y + f2H.y * f2H.y * f3Sigma.x - 2 * f2H.x * f2H.y * f3Sigma.z);
	
	[branch]
	if (f3Ht.z > 0.f && fDet > 0.f)
		fD = ((exp(-0.5f * fE / fDet) / (sqrt(fDet) * fPI * 2.f)));

	return fD;
}

float3 BRDF(in float3 f3L, in float3 f3V, in float3 f3N,  in float fRoughness, in float fF0, in float3 f3Color,
			in float3 f3X, in float3 f3Y, float2 f2LeanB, float3 f3LeanM)
{	
	f3N = normalize(f3N);
	
	float3 f3C1 = cross(f3N, float3(0.f, 0.f, 1.f));
	float3 f3C2 = cross(f3N, float3(0.f, 1.f, 0.f));
	float3 f3C3 = cross(f3N, float3(1.f, 0.f, 0.f));
	[branch]
	if (length(f3C1) > length(f3C2) || length(f3C1) > length(f3C3))
	{
		f3X = normalize(f3C1);
		
	}
	else if (length(f3C2) > length(f3C1) || length(f3C2) > length(f3C3))
	{
		f3X = normalize(f3C2);
	}
	else
	{
		f3X = normalize(f3C3);
	}
	f3Y = normalize(cross(f3N, f3X));

	float3 f3H = normalize(f3L + f3V);
	float3x3 tangentToWorld = transpose(float3x3(f3X, f3Y, f3N));
	float3 f3Ht = normalize(mul((f3V + f3L), tangentToWorld));
	f3Ht = float3(f3Ht.x, f3Ht.y, f3Ht.z);

	float f3Llength = length(f3L);
	float f3Vlength = length(f3V);
 	
	float fDotNL = (dot(f3N, f3L));
	float fDotNV = (dot(f3N, f3V));
	
	fDotNL /= f3Llength;
	fDotNV /= f3Vlength;

	
	float fDotNH = (dot(f3N, f3H));
	float fDotLH = (dot(f3L / f3Llength, f3H));

	float3 f3CdLin = Mon2Lin(f3Color);
	float fCdLum = 0.3f * f3CdLin.r + 0.6f * f3CdLin.g + 0.1f * f3CdLin.b;

	[branch]
	float3 f3CTint = fCdLum > 0 ? f3CdLin / fCdLum : float3(1.f, 1.f, 1.f);
	float3 f3CSpec0 = lerp(fSpecular * 0.08f * lerp(float3(1.f, 1.f, 1.f), f3CTint, fSpecularTint), f3CdLin, fMetallic);												
	float3 f3CSheen = lerp(float3(1.f, 1.f, 1.f), f3CTint, fSheenTint);

	// Diffuse fresnel - go from 1 at normal incidence to .5 at grazing
	// and mix in diffuse retro-reflection based on roughness
	float fFL = SchlickFresnel(fDotNL);
	float fFV = SchlickFresnel(fDotNV);
	float fFd90 = (0.5f + 2 * fDotLH * fDotLH * (fRoughness));
	//float fFd = lerp(1.f, fFd90, fFL) * lerp(1.f, fFd90, fFV);
	float fFd = OrenNayar(f3L, f3V, f3N, f3X, f3Y, fRoughness, fF0);

	// Based on Hanrahan - Krueger brdf approximation of isotropic bssrdf
	// 1.25 scale is used to (roughly) preserve albedo
	// Fss90 used to "flatten" retroreflection based on roughness
	float fFss90 = (fDotLH * fDotLH * fRoughness);
	float fFss = lerp(1, fFss90, fFL) * lerp(1, fFss90, fFV);
	float fss = 1.25f * (fFss * (1 / (fDotNL + fDotNV) - 0.5f) + 0.5f);
	
	// specular
	float fAspect = sqrt(1.f - fAnistropic * 0.9f);
	float fax = max(0.001f, Sqr(fRoughness) / fAspect);
	float fay = max(0.001f, Sqr(fRoughness) * fAspect);

	// LEAN mapping
	float fD = LeanMapping(f2LeanB, f3LeanM, f3Ht);
	
	float fDs = GTR2Aniso(fDotNH, dot(f3H, f3X), dot(f3H, f3Y), fax, fay);
	float fFH = SchlickFresnel(fDotLH);
	float3 f3Fs = lerp(f3CSpec0, float3(1.f, 1.f, 1.f), fFH);
	float fRoughG = Sqr(fRoughness * 0.5f + 0.5f);
	float fGs = SmithG_GGX(fDotNL, fRoughG) * SmithG_GGX(fDotNV, fRoughG);

/*	float fm = fRoughness/5;
	float fG1i = Beckmann_G1(fm, fDotNL);
	float fG1o = Beckmann_G1(fm, fDotNV);
	float fGB = fG1i * fG1o;
// 	float fGs = fGB;

	float fSpec = (fD * fGB * (1.0f / (4.0f * fDotNL * fDotNV)));*/
	
	// sheen
	float3 f3FSheen = fFH * fSheen * f3CSheen;
		
	// clearcoat
	float fDr = GTR1(fDotNH, lerp(0.1f, 0.001, fClearCoatGloss));
	float fFr = lerp(fF0, 1.f, fFH);
	float fGr = SmithG_GGX(fDotNL, 0.25f) * SmithG_GGX(fDotNV, 0.25f);

	[branch]
	if (fDotNL < 0.f) 
	{
		fFr = 0.f;
		fGs = 0.f;
		float retMul = saturate((smoothstep(1, 0, 1 * saturate(dot(f3N, -f3L)))));
		return (retMul*retMul*retMul) * (((1 / fPI) * lerp(fFd, fss, fSubSurface) * f3CdLin + fSheen) * (1.f - fMetallic) + fGs * f3Fs * fDs + 0.25f *
			fClearCoat * fGr * fFr * fDr);
	}
	[branch]
	if (fDotNV < 0.f)
	{
		fFr = 0.f;
		fGs = 0.f;
		float retMul = saturate(smoothstep(1, 0, (dot(f3N, -f3V))));
		return (retMul*retMul*retMul) * (((1 / fPI) * lerp(fFd, fss, fSubSurface) * f3CdLin + fSheen) * (1.f - fMetallic) + fGs * f3Fs * fDs + 0.25f *
			fClearCoat * fGr * fFr * fDr);
	}

	//[branch]
	//if (fDotNL < 0.f || fDotNV < 0.f) return float3(0.f, 0.f, 0.f);


	return (((1 / fPI) * lerp(fFd, fss, fSubSurface) * f3CdLin + fSheen) * (1.f - fMetallic) + fGs * f3Fs * fD + 0.25f *
			fClearCoat * fGr * fFr * fDr);
}