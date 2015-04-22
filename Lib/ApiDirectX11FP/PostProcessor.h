#pragma once

#include "PostBloom.h"
#include "PostGodRays.h"
#include "PostDoF.h"
#include "PostLuma.h"

namespace Vektoria
{
	class CViewport;

	class CPostProcessor
	{
	public:
		CPostProcessor();
		~CPostProcessor();

		void Init(ID3D11DeviceContext* pContext, ID3D11Device* pDevice, CShaderCache* pShaderCache, CDXUtilities* pDxUtilities,
				  int iWindowWidth, int iWindowHeight, unsigned int uiSampleCount, CGeometryUtil* pGeoUtil);
		void InitShader();
		void ResizeRT(CViewport* pViewport);
		void Tick(CViewport* pViewport, D3D11_VIEWPORT* pDXViewport,
				  ID3D11DepthStencilView* pOpaqueDSV, ID3D11ShaderResourceView* pOpaqueSRV,
				  ID3D11DepthStencilView* pTransparentDSV, ID3D11ShaderResourceView* pTransparentSRV,
				  ID3D11ShaderResourceView* pRenderTextureSRV,
				  CForwardPlusRenderer* pCurrRenderer);
		void UpdatePostProcessingCB(CViewport* pViewport);
		void Fini();

		ID3D11ShaderResourceView* GetCurrentRenderTextureSRV();
	
	private:
		unsigned int m_uiSampleCount;

		ID3D11ShaderResourceView* m_pCurrTextureSRV;
		ID3D11Buffer* m_pPostProcessingCB;
		ID3D11SamplerState* m_pPointSampler;

		CGeometryUtil* m_pGeoUtil;
		ID3D11DeviceContext* m_pContext;
		ID3D11Device* m_pDevice;

		CShaderCache* m_pShaderCache;
		CDXUtilities* m_pDxUtilities;

		CPostGodRays m_postGodRays;
		CPostBloom m_postBloom;
		CPostDoF m_postDof;
		CPostLuma m_postLuma;
		bool m_bIsInitialized;
	};
}
