#pragma once

#include "DirectX11FP.h"
#include "../ApiUtils/DXUtilities.h"

namespace Vektoria
{
	class CGeometryUtil;

	struct SPPRenderTarget
	{
		void Release()
		{
			SEC_RELEASE(m_pColorTexture);
			SEC_RELEASE(m_pColorSRV);
			SEC_RELEASE(m_pColorRTV);

			SEC_RELEASE(m_pDepthTexture);
			SEC_RELEASE(m_pDepthDSV);
			SEC_RELEASE(m_pDepthSRV);
		}

		ID3D11Texture2D* m_pColorTexture;
		ID3D11ShaderResourceView* m_pColorSRV;
		ID3D11RenderTargetView* m_pColorRTV;

		ID3D11Texture2D* m_pDepthTexture;
		ID3D11ShaderResourceView* m_pDepthSRV;
		ID3D11DepthStencilView* m_pDepthDSV;
	};

	class CPostProcessorStep
	{
	public:
		virtual void Init(ID3D11DeviceContext* pContext, ID3D11Device* pDevice, CDXUtilities* pDxUtilities,
						  int iWindowWidth, int iWindowHeight, unsigned int uiSampleCount, CGeometryUtil* pGeoUtil) = 0;
		virtual void InitShader(CShaderCache* pShaderCache) = 0;
		virtual void ResizeRT(CViewport* pViewport) = 0;
		virtual ID3D11ShaderResourceView* Tick(CViewport* pViewport, D3D11_VIEWPORT* pDXViewport, 
							ID3D11ShaderResourceView* pOpaqueSRV, ID3D11ShaderResourceView* pTransparentSRV,
							ID3D11ShaderResourceView* pCurrTextureSRV, CForwardPlusRenderer* pCurrRenderer) = 0;
		virtual void Fini() = 0;
		virtual bool IsInitialized() const = 0;
	};
}
