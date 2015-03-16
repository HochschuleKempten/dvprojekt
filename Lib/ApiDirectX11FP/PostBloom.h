#pragma once

#include "PostProcessorStep.h"

namespace Vektoria
{
	class CPostBloom : public CPostProcessorStep
	{
	public:
		CPostBloom();
		~CPostBloom();

		void Init(ID3D11DeviceContext* pContext, ID3D11Device* pDevice, CDXUtilities* pDxUtilities, int iWindowWidth,
				  int iWindowHeight, unsigned int uiSampleCount, CGeometryUtil* pGeoUtil);
		void InitShader(CShaderCache* pShaderCache);
		void ResizeRT(CViewport* pViewport);
		ID3D11ShaderResourceView* Tick(CViewport* pViewport, D3D11_VIEWPORT* pDXViewport, ID3D11ShaderResourceView* pOpaqueSRV,
									   ID3D11ShaderResourceView* pTransparentSRV, ID3D11ShaderResourceView* pCurrTextureSRV, 
									   CForwardPlusRenderer* pCurrRenderer);
		void Fini();
		bool IsInitialized() const;

	private:

		ID3D11InputLayout* m_pLayout;

		ID3D11VertexShader* m_pBloomTextureVertex;
		ID3D11VertexShader* m_pBloomAccumVertex;
		ID3D11VertexShader* m_pBloomBlurVertex;
		ID3D11PixelShader* m_pBloomTexturePixel;
		ID3D11PixelShader* m_pBloomAccumPixel[3];
		ID3D11PixelShader* m_pBloomBlurPixel;
		ID3D11PixelShader* m_pLuminancePixel;
		ID3D11PixelShader* m_pAdaptLuminance;
		SPPRenderTarget m_renderTargetBloomTexture;
		SPPRenderTarget m_renderTargetBloomBlur;
		SPPRenderTarget m_renderTargetBloomAccum;

		SPPRenderTarget m_renderTargetLuminance;
		SPPRenderTarget m_renderTargetAdaptLuminance[2];

		CGeometryUtil* m_pGeoUtil;
		ID3D11DeviceContext* m_pContext;
		ID3D11Device* m_pDevice;

		CDXUtilities* m_pDxUtilities;
		UINT_PTR m_currLumTarget;

		unsigned int m_uiSampleCount;
		unsigned int m_uiLuminanceTextureSize;

		bool m_bIsInitialized;
	};
}

