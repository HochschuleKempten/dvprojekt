//------------------------------------------------------------------
// CDXUtilities: This class contains helpful functions for DirectX development.
//
// Autor: Michael Ruecker
//-------------------------------------------------------------------

#pragma once
#include "DirectX11FP.h"

#define SEC_RELEASE(p)	{ if(p) {(p)->Release(); (p) = nullptr; } }
#define ARRAY_LENGTH( arry ) sizeof( arry ) / sizeof( arry[ 0 ] )

namespace Vektoria
{
	struct SRenderTarget
	{
		// Render texture
		ID3D11Texture2D* m_pRenderTexture;
		ID3D11RenderTargetView* m_pRenderRTV;
		ID3D11ShaderResourceView* m_pRenderSRV;
		ID3D11UnorderedAccessView* m_pRenderUAV;

		// Opaque depth stencil
		ID3D11Texture2D* m_pOpaqueDepthTexture;
		ID3D11DepthStencilView* m_pOpaqueDepthDSV;
		ID3D11ShaderResourceView* m_pOpaqueDepthSRV;
		ID3D11UnorderedAccessView* m_pOpaqueDepthUAV;

		// Transparent depth stencil
		ID3D11Texture2D* m_pTransparentDepthTexture;
		ID3D11DepthStencilView* m_pTransparentDepthDSV;
		ID3D11ShaderResourceView* m_pTransparentDepthSRV;	
		ID3D11UnorderedAccessView* m_pTransparentDepthUAV;

		void Release()
		{
			SEC_RELEASE(m_pRenderTexture);
			SEC_RELEASE(m_pRenderRTV);
			SEC_RELEASE(m_pRenderSRV);
			SEC_RELEASE(m_pRenderUAV);

			SEC_RELEASE(m_pOpaqueDepthTexture);
			SEC_RELEASE(m_pOpaqueDepthDSV);
			SEC_RELEASE(m_pOpaqueDepthSRV);
			SEC_RELEASE(m_pOpaqueDepthUAV);

			SEC_RELEASE(m_pTransparentDepthTexture);
			SEC_RELEASE(m_pTransparentDepthDSV);
			SEC_RELEASE(m_pTransparentDepthSRV);
			SEC_RELEASE(m_pTransparentDepthUAV);
		}
	};


	class CDXUtilities
	{
	public:
		CDXUtilities(CDirectX11FP *renderAPI);
		~CDXUtilities(void);
		HRESULT CreateBuffer( UINT uElementSize, UINT uCount, VOID * pInitData, ID3D11Buffer ** pBufOut, UINT uiBindFlags, UINT uiMiscFlags, D3D11_USAGE Usage = D3D11_USAGE_DEFAULT, UINT uiCPUAccessFlags = 0 );
		void TransferFromGPU(ID3D11Resource * pResource, int iSubresource, BYTE * pBuffer, int iSize);
		HRESULT CreateBufferUAV(ID3D11Buffer * pBuffer, ID3D11UnorderedAccessView ** pUAVOut, bool bAppendBuffer, bool bCounterIfNotAppend);
		HRESULT CreateBufferSRV(ID3D11Buffer * pBuffer, ID3D11ShaderResourceView ** pSRVOut);
		void RunComputeShaderIndirect( int iCS, ID3D11UnorderedAccessView ** aUAVs, int iUAVs, ID3D11ShaderResourceView ** aSRVs, int iSRVs, ID3D11Buffer * pbThreadGroups, UINT uiAlignedOffsetForArgs, UINT *piUAVElementCounts = 0 );
	
		// ID3D11ShaderResourceView and ID3D11DepthStencilView is optional
		HRESULT CreateDepthStencilSurface(ID3D11Texture2D** ppDepthStencilTex, ID3D11ShaderResourceView** ppDepthStencilSRV,
		ID3D11DepthStencilView** ppDepthStencilView, DXGI_FORMAT dsFormat, DXGI_FORMAT srvFormat, unsigned int uiWidth,
		unsigned int uiHeight, unsigned int uiSampleCount);

		HRESULT CreateSurface(ID3D11Texture2D** ppTexture, ID3D11ShaderResourceView** ppTextureSRV,
		ID3D11RenderTargetView** ppTextureRTV, ID3D11UnorderedAccessView** ppTextureUAV, DXGI_FORMAT format,
		unsigned int uiWidth, unsigned int uiHeight, unsigned int uiSampleCount);

		static void CopyXMFLOAT4X4ToCHMat(XMFLOAT4X4 &f4, CHMat &m);
		static void CopyCHMatToXMFLOAT4X4(CHMat & m, XMFLOAT4X4 &f4);
private:
		CDirectX11FP *m_pRenderAPI;
};

}