#pragma once

#include "LightUtil.h"

namespace Vektoria
{
	class CShadowRenderer;
	class CDirectX11FP;
	class CViewport;
	class CRSMRenderer;
	class CGeometryUtil;

#pragma pack(push,1)
	struct SCB_PER_OBJECT
	{
		XMMATRIX m_mWorld;
	};

	struct SCB_PER_CAMERA
	{
		XMMATRIX m_mViewProjection;
	};

	struct SCB_PER_FRAME
	{
		XMMATRIX m_mView;
		XMMATRIX m_mViewInv;
		XMMATRIX m_mProjection;
		XMMATRIX m_mProjectionInv;
		XMMATRIX m_mViewProjectionInvViewport;
		XMVECTOR m_vAmbientColorUp;
		XMVECTOR m_vAmbientColorDown;
		XMVECTOR m_vCameraPosAndAlphaTest;
		unsigned m_uNumPointLights;
		unsigned m_uNumSpotLights;
		unsigned m_uWindowWidth;
		unsigned m_uWindowHeight;
		unsigned m_uMaxLightsPerTile;
		unsigned m_uMaxNumElementsPerTile;
		unsigned m_uNumTilesX;
		unsigned m_uNumTilesY;
		unsigned m_uMaxVPLs;
		unsigned m_uMaxNumVPLsPerTile;
		unsigned m_uMaxNumVPLElementsPerTile;
		float m_fVPLSpotStrength;
		float m_fVPLSpotRadius;
		float m_fVPLPointStrength;
		float m_fVPLPointRadius;
		float m_fVPLRemoveBackFaceContrib;
		float m_fVPLColorThreshold;
		float m_fVPLBrightnessThreshold;
		float m_fPerFramePad1;
		float m_fPerFramePad2;
	};

	struct SCB_SHADOW_CONSTANTS
	{
		XMMATRIX m_mPointShadowViewProj[MAX_SHADOWCASTING_LIGHT_NUM][6];
		XMMATRIX m_mSpotShadowViewProj[MAX_SHADOWCASTING_LIGHT_NUM];
		XMVECTOR m_vShadowBias;
	};
#pragma pack(pop)

	enum MSAASetting
	{
		MSAA_SETTING_NO_MSAA = 0,
		MSAA_SETTING_2X_MSAA,
		MSAA_SETTING_4X_MSAA,
		NUM_MSAA_SETTINGS
	};

	static const int g_nMSAASampleCount[NUM_MSAA_SETTINGS] = { 1, 2, 4 };

	class CForwardPlusRenderer
	{
	public:
		CForwardPlusRenderer();
		~CForwardPlusRenderer();

		void Init(ID3D11DeviceContext* pContext, ID3D11Device* pDevice, CShaderCache* pShaderCache, CGeometryUtil* pGeoUtil);
		void Tick(float fElapsedTime, ID3D11RenderTargetView* pRTV, ID3D11DepthStencilView* pOpaqueDSV, 
				  ID3D11ShaderResourceView* pOpaqueSRV, ID3D11DepthStencilView* pTransparentDSV,
				  ID3D11ShaderResourceView* pTransparentSRV,CLightUtil& lightUtil, CShadowRenderer& shadowRenderer, 
				  CRSMRenderer& RSMRenderer, D3D11_VIEWPORT* pActiveD3DViewport);
		void Fini();
		void RenderSceneForShadowMaps();
		void ResizeRT(CViewport* pViewport);
		void UpdateShadowConstantsCB(CViewport* pViewport);
		void UpdateCameraCB(const XMMATRIX& mViewProj);
		void UpdateWorldCB(const XMMATRIX& mViewProj);
		void UpdateSceneCB(CViewport* pViewport, CHMat& mView, CHMat& mProj, CHMat& mViewProj, CLightUtil& lightUtil,
						   CShadowRenderer& shadowRenderer);
		void InitShader();
		void PerformPreRenderSteps(CLightUtil& lightUtil, CShadowRenderer& shadowRenderer,
			CRSMRenderer& RSMRenderer, CViewport& viewport);
		void ClearResourcesAndContext();
	
	private:

		static const unsigned TILE_RES = 32;
		static const unsigned MAX_NUM_LIGHTS_PER_TILE = 272;
		static const unsigned MAX_NUM_VPLS_PER_TILE = 1024;

		bool m_bMSAA;
		bool m_bShadowsEnabled;
		bool m_bVPLs;
		unsigned m_uMSAASamples;
		ELightMode m_eLightMode;
		bool m_bUpdateSpot;
		bool m_bUpdatePoint;
		bool m_bFixedSpotShadow;
		bool m_bFixedPointShadow;
		bool m_bTransparancey;
		bool m_bWireframe;

		unsigned m_uRTHeight;
		unsigned m_uRTWidth;

		XMFLOAT4X4 m_xf4x4CurrViewProj;

		int m_iUpdateShadowMap;
		int m_iUpdateRSM;

		int m_iUpdateSpotShadow;
		int m_iUpdatePointShadow;

		ID3D11PixelShader* GetScenePS(bool bAlphaTest, bool bShadows, bool bVPLs) const;
		ID3D11ComputeShader* GetLightCullCS(unsigned uMSAASamples, bool bVPLs) const;
		ID3D11ComputeShader* GetLightCullCSBlended(unsigned uMSAASamples) const;

		unsigned CalcNumTilesX() const;
		unsigned CalcNumTilesY() const;
		unsigned CalcMaxNumLightsPerTile() const;
		unsigned CalcMaxNumElementsPerTile() const;
		unsigned CalcMaxNumVPLsPerTile() const;
		unsigned CalcMaxNumVPLElementsPerTile() const;

		void RenderShadows(CShadowRenderer& shadowRenderer, XMMATRIX& viewProj);
		void RenderTransparentObjects(bool bShadows, bool bDepthOnly);
		
		ID3D11Buffer* m_pCBPerObject;
		ID3D11Buffer* m_pCBPerCamera;
		ID3D11Buffer* m_pCBPerFrame;
		ID3D11Buffer* m_pCBShadowConstants;

		ID3D11VertexShader* m_pScenePosOnlyVS;
		ID3D11VertexShader* m_pScenePosAndTexVS;
		ID3D11VertexShader* m_pSceneForwardVS;
		ID3D11PixelShader*  m_pSceneAplhaTestOnlyPS;
		ID3D11InputLayout*  m_pLayoutPosOnly;
		ID3D11InputLayout*  m_pLayoutPosAndTex;
		ID3D11InputLayout*  m_pLayoutForward;
		ID3D11VertexShader* m_pSceneBlendedVS;
		ID3D11VertexShader* m_pSceneBlendedDepthVS;
		ID3D11PixelShader*  m_pSceneBlendedPS;
		ID3D11PixelShader*  m_pSceneBlendedPSShadows;
		ID3D11InputLayout*	m_pSceneBlendedLayout;
		ID3D11InputLayout*  m_pSceneBlendedDepthLayout;

		static const int NUM_FORWARD_PS = 2 * 2 * 2;
		ID3D11PixelShader* m_pSceneForwardPS[NUM_FORWARD_PS];

		static const int NUM_LIGHT_CULLING_CS = 2 * NUM_MSAA_SETTINGS;
		ID3D11ComputeShader* m_pLightCullCS[NUM_LIGHT_CULLING_CS];
		static const int NUM_LIGHT_CULLING_CS_FOR_BLENDED_OBJ = NUM_MSAA_SETTINGS;
		ID3D11ComputeShader* m_pLighCullCSBlended[NUM_LIGHT_CULLING_CS_FOR_BLENDED_OBJ];

		ID3D11BlendState* m_pBlendStateOpaque;
		ID3D11BlendState* m_pBlendStateOpaqueDepthOnly;
		ID3D11BlendState* m_pBlendStateAlphaToCoverageDepthOnly;
		ID3D11BlendState* m_pBlendStateAlpha;

		ID3D11DepthStencilState* m_pDepthStencilStateDepthLess;
		ID3D11DepthStencilState* m_pDepthStencilStateGreater;
		ID3D11DepthStencilState* m_pDepthStencilStateDisableDepthTest;
		ID3D11DepthStencilState* m_pDepthStencilStateEqualAndDisableDepthWrite;
		ID3D11DepthStencilState* m_pDepthStencilStateGreaterAndDisableDepthWrite;

		ID3D11RasterizerState* m_pRasterizerStateDisableCulling;
		ID3D11RasterizerState* m_pRasterizerStateWireframe;
		ID3D11RasterizerState* m_pRasterizerStateSolid;

		ID3D11SamplerState* m_pSamplerStateAniso;
		ID3D11SamplerState* m_pSamplerStateShadow;

		ID3D11Buffer* m_pPointLightIndexBuffer;
		ID3D11ShaderResourceView* m_pPointLightIndexBufferSRV;
		ID3D11UnorderedAccessView* m_pPointLightIndexBufferUAV;

		ID3D11Buffer* m_pPointLightIndexBlendedBuffer;
		ID3D11ShaderResourceView* m_pPointLightIndexBlendedBufferSRV;
		ID3D11UnorderedAccessView* m_pPointLightIndexBlendedBufferUAV;

		ID3D11Buffer* m_pSpotLightIndexBuffer;
		ID3D11ShaderResourceView* m_pSpotLightIndexBufferSRV;
		ID3D11UnorderedAccessView* m_pSpotLightIndexBufferUAV;

		ID3D11Buffer* m_pSpotLightIndexBlendedBuffer;
		ID3D11ShaderResourceView* m_pSpotLightIndexBlendedBufferSRV;
		ID3D11UnorderedAccessView* m_pSpotLightIndexBlendedBufferUAV;

		ID3D11Buffer* m_pVPLIndexBuffer;
		ID3D11ShaderResourceView* m_pVPLIndexBufferSRV;
		ID3D11UnorderedAccessView* m_pVPLIndexBufferUAV;

		ID3D11Buffer* m_pBlendedTransformBuffer;
		ID3D11ShaderResourceView* m_pBlendedTransformSRV;

		ID3D11DeviceContext* m_pContext;
		ID3D11Device* m_pDevice;

		CGeometryUtil* m_pGeoUtil;
		CShaderCache* m_pShaderCache;
	};
}

