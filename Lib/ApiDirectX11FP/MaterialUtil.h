#pragma once

#include "DirectX11FP.h"
#include "PostProcessorStep.h"

namespace Vektoria
{

	struct STEXTUREINFO
	{
		char acPath[MAX_PATH];
		ID3D11ShaderResourceView *ptex;
		int iUsedByMaterials;
	};

	struct SMATERIALINFO
	{
		int iImage;
		int iGlow;
		int iSpecular;
		int iBump;
		int iEnvironment;
		int iPOM;
		int iThickness;
		bool bChanged;
	};

	struct SMATERIALPARAMETERS_HOST
	{
		XMFLOAT4 d3dxcolor;			// Materialfarbe Ambient
		float fSpecularSharpness;
		float fDiffuseSharpness;
		float fBumpStrength;
		float frTransparency;
		XMFLOAT4 d3dxcolorSSS;			// Materialfarbe das Subsurface
		XMFLOAT4 f4SSSBRDFParams;		// Parameter für BRDF/SSS
		unsigned uImage;
		unsigned uGlow;
		unsigned uSpecular;
		unsigned uBump;
		unsigned uImageBlack;
		unsigned uGlowAsImage;
		unsigned uSpecularAsImage;
		unsigned uHeightAsImage;
		unsigned uImageWhite;
		unsigned uGlowWhite;
		unsigned uSpecularWhite;
		unsigned uHeight;
		unsigned uShadingOn;
		unsigned uGlowAsAmbient;
		unsigned uChromaKeying;
		unsigned uEnvironment;
		unsigned uPOM;
		unsigned uTexBRDF;
		unsigned uTexSSS;
		unsigned uReflectionMap;
		unsigned uixPos;
		unsigned uiyPos;
		unsigned uixPics;
		unsigned uiyPics;
		float fRoughness;
		float fIOR;
		float fSpecular;
		float fMetallic;
		float fSubSurface;
		float fAnistropic;
		float fSheen;
		float fSheenTint;
		float fClearCoat;
		float fClearCoatGloss;
		float fSpecularTint;
		ETextureAddressMode eTextureAddressMode;
	};

	class CMaterialUtil
	{
	public:
		CMaterialUtil();
		~CMaterialUtil();

		void Init(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, CDXUtilities* pUtils, CShaderCache* pShaderCache);
		void Fini();

		void CreateMaterial(CMaterial * pmaterial);
		void UpdateMaterial(CMaterial * pmaterial);
		void UpdateMaterialAni(CMaterial * pmaterial);
		bool DeleteMaterial(CMaterial * pmaterial);

		void SetPerObjectMaterialParams(int& idMaterial);
		
	private:

		int TexturePathExists(char *acPath);
		bool CreateTexture(CTexture * ptexture, int eDefaultImage, int & iTexture);
		bool DeleteTexture(int iTexture);
		void CreateLEANMap(int idMaterial);
		void GenerateLEANMap(int idMaterial);

		int m_iMaterials;
		int m_iMaterialAllocs;
		int m_iTextures;
		int m_iTextureAllocs;

		STEXTUREINFO* m_atextureinfo;
		SMATERIALINFO* m_amaterialinfo;
		SMATERIALPARAMETERS_HOST* m_amaterialparameters;
		SPPRENDERTARGET m_aleanMap[1024];

		ID3D11Buffer *m_pbufferTexInfo;
		
		ID3D11Device* m_pdevice;
		ID3D11DeviceContext* m_pdevicecontext;
		CDXUtilities* m_pUtils;
		CShaderCache* m_pShaderCache;
		ID3D11ComputeShader* m_pLEANMapCompute;
	};
}

