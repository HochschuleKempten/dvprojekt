#pragma once

#include "DirectX11FP.h"

namespace Vektoria
{
	class CForwardPlusRenderer;
	class CGeometryUtil;

	struct SGBufferAtlas
	{
		void Release();

		ID3D11Texture2D* m_pDepthTexture;
		ID3D11DepthStencilView* m_pDepthDSV;
		ID3D11ShaderResourceView* m_pDepthSRV;

		ID3D11Texture2D* m_pNormalTexture;
		ID3D11RenderTargetView* m_pNormalRTV;
		ID3D11ShaderResourceView* m_pNormalSRV;

		ID3D11Texture2D* m_pDiffuseTexture;
		ID3D11RenderTargetView* m_pDiffuseRTV;
		ID3D11ShaderResourceView* m_pDiffuseSRV;
	};

	class CDXUtilities;

	class CRSMRenderer
	{
	public:
		CRSMRenderer();
		~CRSMRenderer();

		void Init(ID3D11DeviceContext* pContext, ID3D11Device* pDevice, CShaderCache* pShadercache, CDXUtilities* pDxUtilities,
				  CGeometryUtil* pGeoUtil);
		void Tick();
		void Fini();

		void InitShader();
		void ResizeRT();

		void RenderSpotRSMs(int iNumSpotLights, ID3D11Buffer* pCBPerCamera, CForwardPlusRenderer* pCurrRenderer);
		void RenderPointRSMs(int iNumPointLights, ID3D11Buffer* pCBPerCamera, CForwardPlusRenderer* pCurrRenderer);
		void GenerateVPLs(CLightUtil& lightUtil);

		ID3D11ShaderResourceView* GetSpotDepthSRV() { return m_spotAtlas.m_pDepthSRV;  }
		ID3D11ShaderResourceView* GetSpotNormalSRV() { return m_spotAtlas.m_pNormalSRV; }
		ID3D11ShaderResourceView* GetSpotDiffuseSRV() { return m_spotAtlas.m_pDiffuseSRV; }

		ID3D11ShaderResourceView* GetPointDepthSRV() { return m_pointAtlas.m_pDepthSRV; }
		ID3D11ShaderResourceView* GetPointNormalSRV() { return m_pointAtlas.m_pNormalSRV; }
		ID3D11ShaderResourceView* GetPointDiffuseSRV() { return m_pointAtlas.m_pDiffuseSRV; }

		ID3D11ShaderResourceView* const* GetVPLCenterAndRadiusSRV() const { return &m_pVPLCenterAndRadiusSRV; }
		ID3D11ShaderResourceView* const* GetVPLDataSRV() const { return &m_pVPLDataSRV; }

		int ReadBackNumVPLs();

	private:
	
		void RenderRSMScene(CForwardPlusRenderer* pCurrRenderer);
		void UpdateCameraCB(const XMMATRIX& mViewProj, ID3D11Buffer* pCBPerCamera);

		SGBufferAtlas m_spotAtlas;
		SGBufferAtlas m_pointAtlas;

		ID3D11Buffer* m_pVPLCenterAndRadiusBuffer;
		ID3D11ShaderResourceView* m_pVPLCenterAndRadiusSRV;
		ID3D11UnorderedAccessView* m_pVPLCenterAndRadiusUAV;

		ID3D11Buffer* m_pVPLDataBuffer;
		ID3D11ShaderResourceView* m_pVPLDataSRV;
		ID3D11UnorderedAccessView* m_pVPLDataUAV;

		ID3D11Buffer* m_pSpotInvViewProjBuffer;
		ID3D11ShaderResourceView* m_pSpotInvViewProjSRV;

		ID3D11Buffer* m_pPointInvViewProjBuffer;
		ID3D11ShaderResourceView* m_pPointInvViewProjSRV;

		ID3D11Buffer* m_pNumVPLCB;
		ID3D11Buffer* m_pCPUReadBackCB;

		ID3D11VertexShader* m_pRSMVS;
		ID3D11PixelShader* m_pRSMPS;
		ID3D11InputLayout* m_pRSMLayout;

		ID3D11DepthStencilState* m_pDepthStencilStateLess;
		ID3D11SamplerState* m_pPointSampler;

		ID3D11ComputeShader* m_pGenerateSpotVPLsCS;
		ID3D11ComputeShader* m_pGeneratePointVPLsCS;

		ID3D11DeviceContext* m_pContext;
		ID3D11Device* m_pDevice;
		CGeometryUtil* m_pGeoUtil;
		
		CShaderCache* m_pShaderCache;
		CDXUtilities* m_pDxUtilities;
	};
}