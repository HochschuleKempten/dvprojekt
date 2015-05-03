#pragma once

//------------------------------------------------------------------
// CDirectX11FP: Klasse zur DirectX-Anbindung
//
// Autor: Patrick Fleischmann & Prof. Dr. Tobias Breiner
// Letzte Änderung: 2012-06-05
//-------------------------------------------------------------------



#include "../Vektoria/ApiRender.h"
#include "../Vektoria/Vertex.h"
#include "../VektoriaMath/HMat.h"
#include "../Vektoria/GeoQuad.h"
#include "../ApiUtils/BufferMap.h"

#include "../ApiUtils/Shadercache.h"
#include "../ApiUtils/DrawObjects.h"

#include <d3d11.h>
#include <d3dx11.h>
#include <D3DCompiler.h>
#include <d3dx10.h>
#include <Windows.h>
#include <xnamath.h>
#include <D3D11shader.h>
#include <vector>
#include <thread>


// if we are debugging, then change compiling mode for shader  // Führte bei manchen Rechnern (insbesondere Laborrechner) zum Absturz!!! Musste es leider rausnehmen (TB) 
/*
@TB: Try to install the Windows 8 SDK on those PCs. At least that fixed the issue for me. (MR)
D3D11_CREATE_DEVICE_DEBUG:
"To use this flag, you must have D3D11*SDKLayers.dll installed; otherwise, device creation fails. To get D3D11_1SDKLayers.dll, install the SDK for Windows 8."
*/
// #ifndef VERKTORIA_DIRECTX11_SETTINGS // Include Guards for DirectX11Basic und DirectX11FP
// #define VERKTORIA_DIRECTX11_SETTINGS

#pragma comment (lib, "d3d11.lib")

// #define DEBUG_LABOR_ERROR

#ifdef DEBUG_LABOR_ERROR
#define D3D_DEBUG_INFO // Führte bei manchen Rechnern (insbesondere Laborrechner) zum Absturz!!! Musste es leider rausnehmen, kann aber leicht wieder durch ein define angeschaltet werden (TB)
#endif


#ifdef _DEBUG

#pragma comment (lib, "d3dx11d.lib")
#pragma comment (lib, "d3dx10d.lib")

#ifdef DEBUG_LABOR_ERROR
#define SHADER_COMPILEFLAGS D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION | D3D10_SHADER_SKIP_VALIDATION | D3D10_SHADER_OPTIMIZATION_LEVEL0 // rausgenommen, s.o. (TB)
#define DIRECTX_DEVICE_FLAGS D3D11_CREATE_DEVICE_DEBUG // rausgenommen, s.o. (TB)
#else
#define SHADER_COMPILEFLAGS D3D10_SHADER_OPTIMIZATION_LEVEL0
#define DIRECTX_DEVICE_FLAGS 0
#endif

#else

#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#define SHADER_COMPILEFLAGS D3D10_SHADER_OPTIMIZATION_LEVEL0
#define DIRECTX_DEVICE_FLAGS 0
#endif

// object count to allocate when out of memory
#define I_ALLOCBLOCK 1000

struct ID3DX11Scan;

#define MAT_ALLOCS 1024

namespace Vektoria
{
	class CViewport;
	class CMaterial;
	class CCamera;
	class TriangleList;
	class TriangleStrip;
	class Light;
	class ParallelLight;
	class PointLight;
	class SpotLight;
	class CDXUtilities;
	class CLightUtil;
	class CMaterialUtil;
	class CGeometryUtil;
	class CForwardPlusRenderer;
	class CPostProcessor;
	class CRSMRenderer;
	class CShadowRenderer;
	class CSpriteRenderer;

	struct VERTEX
	{
		FLOAT fx, fy, fz;								// Position
		FLOAT fxNormal, fyNormal, fzNormal;				// Normale 
		FLOAT fxTangent, fyTangent, fzTangent;			// Tangente 
		FLOAT fxBitangent, fyBitangent, fzBitangent;	// Bitangente
		FLOAT fu, fv;									// uv-Mapping fuers Texturing
	};

	struct LIGHT_STRUCTURE
	{
		FLOAT fx, fy, fz;	// Position
		UINT type;			// Light source type (parallel, point, spot)
		D3DXCOLOR color;	// Light's color
		FLOAT dx, dy, dz;	// Direction
		FLOAT fInnerCosAngle;
		FLOAT fOuterCosAngle;
		FLOAT fAttenuationConstant;
		FLOAT fAttenuationLinear;
		FLOAT fAttenuationQuadratic;
		BOOL bCauseShadow;
		BOOL bSoftShadow;
		BOOL bCascadedShadow;
		XMFLOAT4X4 mLightViewProj;
	};

	struct SPOSTPROCESSING_SHADER_CONSTANTS
	{
		XMFLOAT4X4 mWorldViewProjection;
	};

	struct SOBJECT_SHADER_CONSTANTS
	{
		XMFLOAT4X4 mWorld;
		XMFLOAT4X4 mView;
		XMFLOAT4X4 mViewInv;
		XMFLOAT4X4 mProjection;
		UINT iLightsAffectIndices[4];
		UINT iLightsAffectCount;
		int iBuffer[3];
	};

#pragma pack(push, 1)
	struct SMATERIALPARAMETERS
	{
		XMVECTOR d3dxcolor;			// Materialfarbe Ambient
		float fSpecularSharpness;
		float fDiffuseSharpness;
		float fBumpStrength;
		float frTransparency;
		XMVECTOR d3dxcolorSSS;			// Materialfarbe des Subsurface
		XMVECTOR f4SSSBRDFParams;		// Parameter für BRDF/SSS
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
		unsigned uTextureAddressMode;
	};
	struct SPOSTPROCESSING_BUFFER
	{
		float fBloomOriginalIntensity;
		float fBloomIntensity;
		float fBloomOriginalSaturation;
		float fBloomSaturation;
		float fRayExposure;
		float fRayDecay;
		float fRayDensity;
		float fRayWeight;
		float fTimeDelta;
		float fBloomBlurDistance;
		float fDoFNear;
		float fDoFFar;
		float fRcpFrameX;
		float fRcpFrameY;
		unsigned uPad5;
		unsigned uPad6;
		XMVECTOR f4GodRayPos;
		XMVECTOR f4rcpFrameOpt;
		XMVECTOR f4DoFParams;
	};

	struct SVIEWPORTSTYLE_BUFFER
	{
		XMVECTOR d3dxcolorOutline;		// Kontur-Viewportfarbe
		XMVECTOR d3dxcolorFogParams;	// Nebel-Parameter
		XMMATRIX mColorModification; // Farbveraenderungsmatrix

		unsigned uStyleColor;
		unsigned uStyleHalfTransparent;
		unsigned uStylePopart;
		unsigned uStyleOutlining;
		unsigned uStyleMonochrome;
		unsigned uStyleOwn;
		unsigned uStyleFog;
		unsigned uPad0;
	};
#pragma pack(pop)

	enum EShaderType
	{
		eCompute = 0x01,
		eVertex = 0x02,
		eHull = 0x04,
		eDomain = 0x08,
		eGeometry = 0x10,
		ePixel = 0x20,
	};

	static void * ppNULL[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { NULL };

	struct SShader
	{
		union
		{
			ID3D11ComputeShader  *pComputeShader;
			ID3D11VertexShader   *pVertexShader;
			ID3D11HullShader     *pHullShader;
			ID3D11DomainShader   *pDomainShader;
			ID3D11GeometryShader *pGeometryShader;
			ID3D11PixelShader    *pPixelShader;
		};
		ID3D11InputLayout *pinputLayout;
		EShaderType type;
	};

	class CDirectX11FP : public CApiRender
	{
		friend class CDXUtilities;
		friend class CLightUtil;

	public:
		EApiRender m_eApiRender;

		ID3D11Texture2D *m_ptextureBackBuffer;
		CDirectX11FP();
		void ChangeRenderStatePostprocessing(CViewport *pviewport);
		void Postprocessing(CViewport *pviewport);

		CDXUtilities* CDirectX11FP::Utils();
		
		void Init(HWND hwnd, int iWidthWindow, int iHeightWindow, EApiRender eApiRender, EShaderCreation eShaderCreation, EShaderAutoRecompilation eShaderAutoRecompilation);
		void Tick();
		void Fini();

		// Viewport-Methoden:
		void AddViewport(CViewport *pviewport);
		void BeginRenderViewport(CHMat & mProjection, CHMat & mView, CHMat & mViewInv, CViewport &viewport);
		void EndRenderViewport(CViewport * pviewport);
		void ChangeRenderState(CViewport *pviewport, bool bCullNone = false);
		void ChangeRenderStateShadow(CViewport *pviewport);
		void ChangeResolution(CViewport *pviewport);

		// lighting
		SRenderObjectHandle CreateLight(CLight *plight);
		void DestroyLight(SRenderObjectHandle & hLight);

		// shadows
		void ResizeShadowMap(int iPixelsWidth, int iPixelsHeight);
		void BeginRenderShadow(CLight *plight, CViewport *pviewport);
		void RenderShadowMap(SRenderObjectHandle &handle, CHMat &mGlobal);
		void EndRenderShadow();

		// triangle strip handling
		void UpdateTriangleList(CTriangleList *ptrianglelist, SRenderObjectHandle & phandle);
		void UpdateTriangleStrip(CTriangleStrip *ptrianglestrip, SRenderObjectHandle & phandle);
		SRenderObjectHandle CreateTriangleList(CTriangleList *ptrianglelist);
		SRenderObjectHandle CreateTriangleStrip(CTriangleStrip *ptrianglestrip);

		// custom buffer handling
	 //	SRenderObjectHandle CreateBuffer(CDrawable *pdrawable, void *pData, D3D11_BUFFER_DESC &bd, int *pIndices = 0, int iindicesCount = 0);
		HRESULT CreateSRVFromFile(char const *pFileName, ID3D11ShaderResourceView **ppSRV);
		HRESULT CreateSamplerState(D3D11_SAMPLER_DESC const *pSamplerDesc, ID3D11SamplerState **ppSamplerState);
		void FreeHandle(SRenderObjectHandle handle);
		void CopyBuffer(ID3D11Buffer *pDest, ID3D11Buffer *pSrc);

		
		void Draw(SRenderObjectHandle & handle, int & idTexture, float fDistanceToCameraSquare, int iKind, CHMat & mGlobal, CLight **aplightAffect, unsigned int iLightsAffectCount);
		void CreateMaterial(CMaterial * pmaterial);
		void UpdateMaterial(CMaterial * pmaterial);
		void UpdateMaterialAni(CMaterial * pmaterial);
		bool DeleteMaterial(CMaterial * pmaterial);

		EShaderCreation m_eShaderCreation;
		EShaderAutoRecompilation m_eShaderAutoRecompilation;

		//particles
		void AddEmitter(CEmitter * pEmitter);
		void UpdateEmitterData(CEmitter * pEmitter);
		//debugging
		DXGI_ADAPTER_DESC QueryGraphicsCard();
		void InitProfiling();

		int m_iShaders;
		int m_iViewports;

	protected:
		CDXUtilities *m_pUtils;
		IDXGISwapChain *m_pswapchain;

		// Hauptvariablen:
		CViewport *m_pcurrentViewort;
		IDXGISwapChain *m_pswapChain;
		ID3D11Device *m_pdevice;
		ID3D11DeviceContext *m_pdevicecontext;

		ID3D11Buffer *m_pbufferViewportStyle;

		LIGHT_STRUCTURE *m_plightstructure; // new TB 2013_09_27;

		// I need those for soft particles. I thought it is better to store them in this class instead of the particle renderer since someone else might need that as well later. (MR)
		float m_fNearClipping;
		float m_fFarClipping;

		SShader *m_pShader;
		D3D11_BUFFER_DESC m_bufferdescVertex;
		ID3D11Buffer *m_pVBuffer;
		ID3D11Buffer *m_pbufferLights;
		ID3D11ShaderResourceView *m_pshaderresourceviewLights;
		VERTEX *m_pvertexGeo;
		BufferMap m_buffermap;
		SOBJECT_SHADER_CONSTANTS m_objectshaderconstants;
		SOBJECT_SHADER_CONSTANTS m_objectshaderconstantsParallelProjection;
		ID3D11SamplerState *m_psamplerstateLinearWrap;
		ID3D11SamplerState *m_psamplerstateLinearClamp;
		ID3D11SamplerState *m_psamplerstateLinearMirror;
		ID3D11InfoQueue * m_pInformationQueue;
		int m_iCurMsg;
		ID3D11Query * m_pEventQuery;

		D3D11_TEXTURE2D_DESC m_texdescStencil;
		D3D11_DEPTH_STENCIL_VIEW_DESC m_depthstencilviewdesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC m_shaderresourceviewdesc;

		D3D11_TEXTURE2D_DESC * m_atexdescPostprocessing;
		ID3D11Texture2D **m_aptexturePostprocessing;
		ID3D11RenderTargetView ** m_aprendertargetviewPostprocessing;
		ID3D11ShaderResourceView ** m_apshaderresourceviewPostprocessing;
		D3D11_RENDER_TARGET_VIEW_DESC * m_arendertargetviewdescPostprocessing;
		D3D11_SHADER_RESOURCE_VIEW_DESC * m_ashaderresourceviewdescPostprocessing;

		D3D11_RASTERIZER_DESC * m_arasterizerdesc;
		ID3D11RasterizerState ** m_aprasterizerstate;
		ID3D11RenderTargetView *m_prendertargetviewBackBuffer;

		D3D11_RASTERIZER_DESC * m_arasterizerdescPostprocessing;
		ID3D11RasterizerState ** m_aprasterizerstatePostprocessing;
		// Depth Stencil:
		ID3D11DepthStencilView *m_pOpaqueDepthDSV;
		ID3D11Texture2D *m_pOpaqueDepthTexture;
		ID3D11ShaderResourceView * m_pOpaqueDepthSRV;
		ID3D11DepthStencilView *m_pTransparentDepthDSV;
		ID3D11Texture2D *m_pTransparentDepthTexture;
		ID3D11ShaderResourceView * m_pTransparentDepthSRV;

		// Hauptshader: 
		ID3D11PixelShader *m_ppixelshader;
		ID3D11VertexShader *m_pvertexshader;
		ID3D11InputLayout *m_pinputlayout;
		D3D11_INPUT_ELEMENT_DESC* m_pinputLayoutDesc;
		ID3D11Buffer *m_pbufferProjectionMatrix;
		ID3D11Buffer *m_pbufferTexInfo;
		ID3D11Buffer *m_pbufferGPU;

		ID3D11SamplerState * m_psamplerstateActive;

		// Postprozess-Shader-Variablen:
		ID3D11VertexShader *m_pvertexshaderPostprocessing;
		ID3D11PixelShader *m_ppixelshaderPostprocessing;
		ID3D11InputLayout *m_pinputlayoutPostprocessing;
		ID3D11Buffer *m_pbufferProjectionMatrixPostprocessing;

		ID3D11Buffer *m_pbufferTexInfoPostprocessing;

		// contains all lights
		std::vector<CLight*>m_vplightShadowCaster;	// TODO: make this an array
		CLight **m_pplight;
		int m_iLights;

		unsigned int GetMSAAQuality(unsigned int uiSamples, DXGI_FORMAT format);
		void InitShaderPostprocessing();

		void InitBackBuffer();
		void InitShader(EShaderCreation & eShaderCreation);
		ID3D11SamplerState * GetSamplerStateBasedOnTextureAddressMode(ETextureAddressMode eTextureAddressMode);

		SPOSTPROCESSING_SHADER_CONSTANTS m_postprocessingShaderConstants;
		bool m_bFirstDraw;
		bool m_bFirstPPDraw;
		SRenderObjectHandle** m_apPPRHND;

		D3D11_VIEWPORT* m_aviewport;

		unsigned int m_uiSampleCount;
		unsigned int m_uiSampleQuality;

		D3D_FEATURE_LEVEL m_featurelevel;

		
		CHMat m_mProjectionOverlay;
		CHMat m_mViewOverlay;
		CHMat m_mWorldOverlay;

		CShaderCache* m_pShaderCache;
		float m_fTempViewX;
		float m_fTempViewY;
		int m_iActiveViewportHeight;
		int m_iActiveViewportWidth;

		CLightUtil* m_pLightUtil;
		CForwardPlusRenderer** m_pForwardPlusRenderer;
		CShadowRenderer** m_pShadowRenderer;
		CRSMRenderer** m_pRSMRenderer;
		CViewport* m_pCurrView;	
		CSpriteRenderer** m_pSpriteRenderer;
		CPostProcessor** m_pPostProcessor;
		CGeometryUtil* m_pGeoUtil;
		CMaterialUtil* m_pMatUtil;

		bool m_bInit;
		bool m_bFistTick;
	};

}