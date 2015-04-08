#include "postconstants.h"
#include "fxaa.h"

//--------------------------------------------------------------------------------------
// Copyright (c) Tobias Breiner
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// Textur Buffer
//--------------------------------------------------------------------------------------

Texture2D tex2D[8] : register ( t15 ); // texture

//--------------------------------------------------------------------------------------

struct VS_INPUT_POST
{
    float4 f4Pos : POSITION;
    float3 f3Normal : NORMAL;
    float2 f2TexCoord : TEXCOORD; 
    float3 f3Tangent : TANGENT;
    float3 f3Bitangent : BITANGENT;
};


struct PS_INPUT_POST
{
   float4 f4Pos : SV_POSITION0;
   float2 f2TexCoord : TEXCOORD0;
   float4 f4VertexPos : TEXCOORD2;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT_POST VS_POST( VS_INPUT_POST input )
{
    PS_INPUT_POST output = (PS_INPUT_POST)0;
	output.f2TexCoord = input.f2TexCoord;

	output.f4Pos = mul(input.f4Pos, World);

    return output;
}


// --------------------------------------------------------------------------------------
//  | 1/9 1/9 1/9 |
//  | 1/9 1/9 1/9 |
//  | 1/9 1/9 1/9 |
//--------------------------------------------------------------------------------------
float4 MeanFilter(float2 f2TexCoord)
{
	float fWidth, fHeight;
	tex2D[7].GetDimensions(fWidth, fHeight);
	float fOffsetX = 1.f / fWidth;
	float fOffsetY = 1.f / fHeight;
	float4 f4ColorOut = float4(0.f, 0.f, 0.f, 1.f);
	float2 fTex1 = float2(f2TexCoord.x + fOffsetX,			  f2TexCoord.y);
	float2 fTex2 = float2(f2TexCoord.x			 , f2TexCoord.y + fOffsetY);
	float2 fTex3 = float2(f2TexCoord.x - fOffsetX, f2TexCoord.y			  );
	float2 fTex4 = float2(f2TexCoord.x			 , f2TexCoord.y - fOffsetY);
	float2 fTex5 = float2(f2TexCoord.x			 , f2TexCoord.y			  );
	float2 fTex6 = float2(f2TexCoord.x - fOffsetX, f2TexCoord.y - fOffsetY);
	float2 fTex7 = float2(f2TexCoord.x + fOffsetX, f2TexCoord.y - fOffsetY);
	float2 fTex8 = float2(f2TexCoord.x - fOffsetX, f2TexCoord.y + fOffsetY);
	float2 fTex9 = float2(f2TexCoord.x + fOffsetX, f2TexCoord.y + fOffsetY);

	f4ColorOut += tex2D[7].Sample(linearSampler, fTex1);
	f4ColorOut += tex2D[7].Sample(linearSampler, fTex2);
	f4ColorOut += tex2D[7].Sample(linearSampler, fTex3);
	f4ColorOut += tex2D[7].Sample(linearSampler, fTex4);
	f4ColorOut += tex2D[7].Sample(linearSampler, fTex5);
	f4ColorOut += tex2D[7].Sample(linearSampler, fTex6);
	f4ColorOut += tex2D[7].Sample(linearSampler, fTex7);
	f4ColorOut += tex2D[7].Sample(linearSampler, fTex8);
	f4ColorOut += tex2D[7].Sample(linearSampler, fTex9);
	return (f4ColorOut *= 0.11111f); // *1/9
}
// --------------------------------------------------------------------------------------
//		  | 1 2 1 |
// 1/16 * | 2 4 2 |
//		  | 1 2 1 |
//--------------------------------------------------------------------------------------
float4 BinomialFilter(float2 f2TexCoord, float fRadius)
{
	float fWidth, fHeight;
	tex2D[7].GetDimensions(fWidth, fHeight);
	float fOffsetX = 1.f / fWidth;
	float fOffsetY = 1.f / fHeight;
	fOffsetX *= fRadius;
	fOffsetY *= fRadius;
	float4 f4ColorOut = float4(0.f, 0.f, 0.f, 1.f);
	float2 fTex1 = float2(f2TexCoord.x + fOffsetX,			  f2TexCoord.y);
	float2 fTex2 = float2(f2TexCoord.x			 , f2TexCoord.y + fOffsetY);
	float2 fTex3 = float2(f2TexCoord.x - fOffsetX,			  f2TexCoord.y);
	float2 fTex4 = float2(f2TexCoord.x			 , f2TexCoord.y - fOffsetY);
	float2 fTex5 = float2(f2TexCoord.x			 ,			  f2TexCoord.y);
	float2 fTex6 = float2(f2TexCoord.x - fOffsetX, f2TexCoord.y - fOffsetY);
	float2 fTex7 = float2(f2TexCoord.x + fOffsetX, f2TexCoord.y - fOffsetY);
	float2 fTex8 = float2(f2TexCoord.x - fOffsetX, f2TexCoord.y + fOffsetY);
	float2 fTex9 = float2(f2TexCoord.x + fOffsetX, f2TexCoord.y + fOffsetY);

	f4ColorOut += 2*tex2D[7].Sample(linearSampler, fTex1);
	f4ColorOut += 2*tex2D[7].Sample(linearSampler, fTex2);
	f4ColorOut += 2*tex2D[7].Sample(linearSampler, fTex3);
	f4ColorOut += 2*tex2D[7].Sample(linearSampler, fTex4);
	f4ColorOut += 4*tex2D[7].Sample(linearSampler, fTex5);
	f4ColorOut += tex2D[7].Sample(linearSampler, fTex6);
	f4ColorOut += tex2D[7].Sample(linearSampler, fTex7);
	f4ColorOut += tex2D[7].Sample(linearSampler, fTex8);
	f4ColorOut += tex2D[7].Sample(linearSampler, fTex9);
	return (f4ColorOut *= 0.0625f); // *1/16
}
// --------------------------------------------------------------------------------------
// | 1 0 -1 |
// | 2 0 -2 |
// | 1 0 -1 |
//--------------------------------------------------------------------------------------
float4 SobelOperatorLR(float2 f2TexCoord)
{
	const float fStrength = 1.f;
	float fWidth, fHeight;
	tex2D[7].GetDimensions(fWidth, fHeight);
	float fOffsetX = 1.f / fWidth;
	float fOffsetY = 1.f / fHeight;
	float4 f4ColorOut = float4(0.f, 0.f, 0.f, 1.f);
	float2 fTex1 = float2(f2TexCoord.x + fOffsetX, f2TexCoord.y			  );
	float2 fTex2 = float2(f2TexCoord.x			 , f2TexCoord.y + fOffsetY);
	float2 fTex3 = float2(f2TexCoord.x - fOffsetX, f2TexCoord.y			  );
	float2 fTex4 = float2(f2TexCoord.x			 , f2TexCoord.y - fOffsetY);
	float2 fTex5 = float2(f2TexCoord.x           , f2TexCoord.y			  );
	float2 fTex6 = float2(f2TexCoord.x - fOffsetX, f2TexCoord.y - fOffsetY);
	float2 fTex7 = float2(f2TexCoord.x + fOffsetX, f2TexCoord.y - fOffsetY);
	float2 fTex8 = float2(f2TexCoord.x - fOffsetX, f2TexCoord.y + fOffsetY);
	float2 fTex9 = float2(f2TexCoord.x + fOffsetX, f2TexCoord.y + fOffsetY);

	f4ColorOut += (fStrength * -2) * tex2D[7].Sample(linearSampler, fTex1);
	//f4ColorOut +=  0 * tex2D[7].Sample(linearSampler, fTex2);
	f4ColorOut += (fStrength * 2) * tex2D[7].Sample(linearSampler, fTex3);
	//f4ColorOut += 0 * tex2D[7].Sample(linearSampler, fTex4);
	//f4ColorOut += 0 * tex2D[7].Sample(linearSampler, fTex5);
	f4ColorOut += fStrength * tex2D[7].Sample(linearSampler, fTex6);
	f4ColorOut += (fStrength -1) * tex2D[7].Sample(linearSampler, fTex7);
	f4ColorOut += fStrength *tex2D[7].Sample(linearSampler, fTex8);
	f4ColorOut += (fStrength * -1) * tex2D[7].Sample(linearSampler, fTex9);
	return (f4ColorOut);
}
// --------------------------------------------------------------------------------------
// |  1  2  1 |
// |  0  0  0 |
// | -1 -2 -1 |
//--------------------------------------------------------------------------------------
float4 SobelOperatorUD(float2 f2TexCoord)
{
	const float fStrength = 1.f;
	float fWidth, fHeight;
	tex2D[7].GetDimensions(fWidth, fHeight);
	float fOffsetX = 1.f / fWidth;
	float fOffsetY = 1.f / fHeight;
	float4 f4ColorOut = float4(0.f, 0.f, 0.f, 1.f);
	float2 fTex1 = float2(f2TexCoord.x + fOffsetX, f2TexCoord.y			  );
	float2 fTex2 = float2(f2TexCoord.x			 , f2TexCoord.y + fOffsetY);
	float2 fTex3 = float2(f2TexCoord.x - fOffsetX, f2TexCoord.y			  );
	float2 fTex4 = float2(f2TexCoord.x			 , f2TexCoord.y - fOffsetY);
	float2 fTex5 = float2(f2TexCoord.x			 , f2TexCoord.y			  );
	float2 fTex6 = float2(f2TexCoord.x - fOffsetX, f2TexCoord.y - fOffsetY);
	float2 fTex7 = float2(f2TexCoord.x + fOffsetX, f2TexCoord.y - fOffsetY);
	float2 fTex8 = float2(f2TexCoord.x - fOffsetX, f2TexCoord.y + fOffsetY);
	float2 fTex9 = float2(f2TexCoord.x + fOffsetX, f2TexCoord.y + fOffsetY);
	//f4ColorOut += 0 * tex2D[7].Sample(linearSampler, fTex1);
	f4ColorOut += (fStrength * -2) * tex2D[7].Sample(linearSampler, fTex2);
	//f4ColorOut += 0 * tex2D[7].Sample(linearSampler, fTex3);
	f4ColorOut += (fStrength * -2) * tex2D[7].Sample(linearSampler, fTex4);
	//f4ColorOut += 0 * tex2D[7].Sample(linearSampler, fTex5);
	f4ColorOut += (fStrength * -1) * tex2D[7].Sample(linearSampler, fTex6);
	f4ColorOut += (fStrength * -1) * tex2D[7].Sample(linearSampler, fTex7);
	f4ColorOut += fStrength * tex2D[7].Sample(linearSampler, fTex8);
	f4ColorOut += fStrength * tex2D[7].Sample(linearSampler, fTex9);
	return (f4ColorOut);
}

float4 SobelOperatorLRAndUD(float2 f2TexCoord)
{
	float4 f4ColorOutLR = float4(0.f, 0.f, 0.f, 1.f);
	float4 f4ColorOutUD = float4(0.f, 0.f, 0.f, 1.f);
	f4ColorOutLR = SobelOperatorLR(f2TexCoord);
	f4ColorOutUD = SobelOperatorUD(f2TexCoord);
	return (abs(f4ColorOutLR) * abs(f4ColorOutUD));
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS_POST( PS_INPUT_POST input) : SV_Target
{
	float4 f4ColorOut = tex2D[7].Sample(linearSampler, input.f2TexCoord);

	if (f2rcpFrame.x) // FXAA enabled
	{
		FxaaTex tex;
		tex.smpl = linearSampler;
		tex.tex = tex2D[7];
		f4ColorOut = FxaaPixelShader(input.f2TexCoord,
								     float4(0.f, 0.f, 0.f, 0.f),
									 tex,
		                             f2rcpFrame,
									 f4rcpFrameOpt);
	}
		
	if (uBlur)
	{
		f4ColorOut = saturate(f4ColorOut + BinomialFilter(input.f2TexCoord, fBlurStrength));
	}
	if (uEnhancedEdges)
	{
		f4ColorOut += SobelOperatorLRAndUD(input.f2TexCoord);
		f4ColorOut.rgb *= 0.33f;
	}
	if (uMeanFilter)
	{
		f4ColorOut += MeanFilter(input.f2TexCoord);
		f4ColorOut.rgb *= 0.5f;
	}

	f4ColorOut.a = 1.f;
	return f4ColorOut;
}