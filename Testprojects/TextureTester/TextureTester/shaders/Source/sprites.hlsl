SamplerState linearSampler : register(s0);

Texture2D tex2D[8] : register ( t15 );

cbuffer cbPerObject : register (b0)
{
	matrix g_mWorld : packoffset(c0);
};

/////////////////////////////////////////////////////////////////////
//shader options
cbuffer TexInfo : register(b5)
{
	float4 f4ColorAmbient : packoffset(c0);
	float fA : packoffset(c1); // specular sharpness
	float fH : packoffset(c1.y);// diffuse sharpness
	float fBumpStrength : packoffset(c1.z);
	float frTransparency : packoffset(c1.w);
	float4 f4ColorSSS : packoffset(c2);
	float4 f4SSSBRDFParams : packoffset(c3);
	uint uImage : packoffset(c4);
	uint uGlow : packoffset(c4.y);
	uint uSpecular : packoffset(c4.z);
	uint uBump : packoffset(c4.w);
	uint uImageBlack : packoffset(c5);
	uint uGlowAsImage : packoffset(c5.y);
	uint uSpecularAsImage : packoffset(c5.z);
	uint uHeightAsImage : packoffset(c5.w);
	uint uImageWhite : packoffset(c6);
	uint uGlowWhite : packoffset(c6.y);
	uint uSpecularWhite : packoffset(c6.z);
	uint uHeight : packoffset(c6.w);
	uint uShadingOn : packoffset(c7);
	uint uGlowAsAmbient : packoffset(c7.y);
	uint uChromaKeying : packoffset(c7.z);
	uint uEnvironment : packoffset(c7.w);
	uint uPOM : packoffset(c8);
	uint uTexBRDF : packoffset(c8.y);
	uint uTexSSS : packoffset(c8.z);
	uint uReflectionMap : packoffset(c8.w);
	uint uixPos : packoffset(c9);
	uint uiyPos : packoffset(c9.y);
	uint uixPics : packoffset(c9.z);
	uint uiyPics : packoffset(c9.w);
}

cbuffer ViewportArt : register(b6)
{
	float4 f4ColorViewportOutline : packoffset(c0);
	float4 f4FogParams : packoffset(c1);
	matrix mColorModification : packoffset(c2);

	uint uStyleColor : packoffset(c6);
	uint uStyleHalfTransparent : packoffset(c6.y);
	uint uStylePopart : packoffset(c6.z);
	uint uStyleOutlining : packoffset(c6.w);
	uint uStyleMonochrome : packoffset(c7);
	uint uStyleOwn : packoffset(c7.y);
	uint uStyleFog : packoffset(c7.z);
	uint uPad0 : packoffset(c7.w);
}

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
	float4 f4VertexPos : TEXCOORD2;
};

PS_INPUT RenderSpritesVS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.f4Pos = mul(input.f4Pos, g_mWorld);
	output.f4VertexPos = output.f4Pos;

	output.f3Normal = normalize(mul(input.f3Normal, (float3x3)g_mWorld));
	output.f3Tangent = normalize(mul(input.f3Tangent, (float3x3)g_mWorld));
	output.f3Bitangent = normalize(mul(input.f3Bitangent, (float3x3)g_mWorld));
	output.f2TexCoord = input.f2TexCoord;

	return output;
}

float4 RenderSpritesPS(PS_INPUT input) : SV_Target
{
	float4 f4TexCol = tex2D[0].Sample(linearSampler, input.f2TexCoord);

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

	float fTrans = f4TexCol.a;

	[branch]
	if (frTransparency != 0.f)
		fTrans = min(frTransparency, f4TexCol.a);

	//f4TexCol.a = 0.2f;
	return f4TexCol;
}
