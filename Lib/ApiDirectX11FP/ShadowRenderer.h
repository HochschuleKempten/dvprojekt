#pragma once

#include "DirectX11FP.h"

namespace Vektoria
{
	class CDXUtilities;

	class CShadowRenderer
	{
	public:
		CShadowRenderer();
		~CShadowRenderer();

		void Init(ID3D11DeviceContext* pContext, CDXUtilities* pdxUtils, CForwardPlusRenderer* pForwardPlusRenderer);
		void Fini();

		void RenderPointLightMap(int iNumShadowCastingPointLights, ID3D11Buffer* pCBPerCamera);
		void RenderSpotLightMap(int iNumShadowCastingSpotLights, ID3D11Buffer* pCBPerCamera);

		ID3D11ShaderResourceView* const* GetPointLightAtlasSRV() const
		{
			return &m_pPointLightAtlasSRV;
		}

		ID3D11ShaderResourceView* const* GetSpotLightAtlasSRV() const
		{
			return &m_pSpotLightAtlasSRV;
		}

		void UpdateSpotShadowSize(unsigned uWidthHeight);
		void UpdatePointShadowSize(unsigned uWidthHeight);
		unsigned GetPointShadowSize();
		unsigned GetSpotShadowSize();

	private:

		void UpdateCameraCB(const XMMATRIX& mViewProj, ID3D11Buffer* pCBPerCamera);

		ID3D11Texture2D* m_pPointLightAtlasTex;
		ID3D11DepthStencilView* m_pPointLightAtlasView;
		ID3D11ShaderResourceView* m_pPointLightAtlasSRV;

		ID3D11Texture2D* m_pSpotLightAtlasTex;
		ID3D11DepthStencilView* m_pSpotLightAtlasView;
		ID3D11ShaderResourceView* m_pSpotLightAtlasSRV;

		int m_iPointShadowRes;
		int m_iSpotShadowRes;

		CDXUtilities* m_pdxUtils;
		ID3D11DeviceContext* m_pContext;
		CForwardPlusRenderer* m_pForwardPlusRenderer;
	};
}

