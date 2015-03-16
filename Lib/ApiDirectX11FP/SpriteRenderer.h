#pragma once

#include "DirectX11FP.h"

namespace Vektoria
{
	class CSpriteRenderer
	{
	public:
		CSpriteRenderer();
		~CSpriteRenderer();

		void Init(ID3D11DeviceContext* pContext, ID3D11Device* pDevice, CShaderCache* pShaderCache, CGeometryUtil* pGeoUtil);
		void InitShader();
		void RenderSprites(bool bWithMaterials, D3D11_VIEWPORT* pCurrD3DViewport, CForwardPlusRenderer* pCurrRenderer);
		void Fini();

	private:

		ID3D11InputLayout* m_pSpriteLayout;
		ID3D11VertexShader* m_pSpriteVS;
		ID3D11PixelShader* m_pSpritePS;

		ID3D11BlendState* m_pBlendStateSprites;
		ID3D11RasterizerState* m_pRasterizerStateSprites;

		ID3D11DeviceContext* m_pContext;
		ID3D11Device* m_pDevice;
		CGeometryUtil* m_pGeoUtil;
		
		CShaderCache* m_pShaderCache;
	};
}

