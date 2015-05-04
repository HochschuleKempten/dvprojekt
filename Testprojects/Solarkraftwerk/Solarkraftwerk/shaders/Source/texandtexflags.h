//////////////////////////////////////////////////////////////////////
//input tex for shaders
Texture2D tex2D[7] : register (t15);

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
	float fSpecularRoughness : packoffset(c10.x);
	float fSpecularIOR : packoffset(c10.y);
	uint uPad1 : packoffset(c10.z);
	uint uPad2 : packoffset(c10.w);
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