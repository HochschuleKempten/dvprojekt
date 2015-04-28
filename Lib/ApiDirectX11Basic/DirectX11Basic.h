#pragma once

//------------------------------------------------------------------
// CDirectX11Basic: Klasse zur DirectX-Anbindung (Basic-Renderer)
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


#pragma comment (lib, "d3d11.lib")


#ifdef _DEBUG

#pragma comment (lib, "d3dx11d.lib")
#pragma comment (lib, "d3dx10d.lib")


#ifdef DEBUG_LABOR_ERROR
#define D3D_DEBUG_INFO // Führte bei manchen Rechnern (insbesondere Laborrechner) zum Absturz!!! Musste es leider rausnehmen, kann aber leicht wieder durch ein define angeschaltet werden (TB)
#endif

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


namespace Vektoria
{
	/*
//	const CShaderCache::EShaderCreateType g_createType = CShaderCache::EShaderCreateType::eCreateTypeUseCached;
//	const CShaderCache::EShaderCreateType g_createType = CShaderCache::EShaderCreateType::eCreateTypeUseCached;
	const CShaderCache::EShaderCreateType g_createType = CShaderCache::EShaderCreateType::eCreateTypeCompileChanges;
	const CShaderCache::EShaderAutoRecompilation g_compileType = CShaderCache::eShaderAutoRecompilation_Enabled;
	*/
	class CViewport;
	class CMaterial;
	class CCamera;
	class TriangleList;
	class TriangleStrip;
	class Light;
	class ParallelLight;
	class PointLight;
	class SpotLight;
	class CParticleRenderer;
	class CDXUtilities;
	class CLightUtil;

	struct SVertexBuffer
	{
		FLOAT fx, fy, fz;								// Position
		FLOAT fxNormal, fyNormal, fzNormal;				// Normale 
		FLOAT fxTangent, fyTangent, fzTangent;			// Tangente 
		FLOAT fxBitangent, fyBitangent, fzBitangent;	// Bitangente
		FLOAT fu, fv;									// uv-Mapping fuers Texturing
	};

	struct SLightStructure
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


	// changed data type to xmfloat4x4, because
	// xmmatrix cant be used in class (memory alignment on x86!)
	struct SPostprocessingShaderConstants
	{
		XMFLOAT4X4 mWorldViewProjection;
	};


	
	struct SObjectShaderConstants
	{
		XMFLOAT4X4 mWorld;
		XMFLOAT4X4 mView;
		XMFLOAT4X4 mViewInv;
		XMFLOAT4X4 mProjection;
		UINT iLightsAffectIndices[4];
		UINT iLightsAffectCount;
		int iBuffer[3];
	};
	

	// constant buffer structure for shadow map
	struct SShadowmapShaderConstants
	{
		XMFLOAT4X4 mWorld;
		XMFLOAT4X4 mLightView;
		int iBuffer1[16];
		XMFLOAT4X4 mProjection;
		int iBuffer2[8];
	};

	struct SDrawObject
	{
		SRenderObjectHandle handle;
		int idTexture;
		float fDistanceToCameraSquare;
		CHMat mGlobal;
		unsigned int iLightsAffectIndices[4];
		unsigned int iLightsAffectCount;
	};

	struct STextureInfo
	{
		char acPath[MAX_PATH];
		ID3D11ShaderResourceView *ptex;
		int iUsedByMaterials;
	};

	struct SMaterialInfo
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

	struct SMaterialParametersHost
	{
		XMFLOAT4 d3dxcolor;			// Materialfarbe Ambient
		float fSpecularSharpness;
		float fDiffuseSharpness;
		float fBumpStrength;
		float frTransparency;
		XMFLOAT4 d3dxcolorSSS;			// Materialfarbe des Subsurface
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
		ETextureAddressMode eTextureAddressMode;
		XMFLOAT4 offset;
	};

	struct SPostprocessingBufferHost
	{
		XMFLOAT4 d3dxcolor;
		float fParam0;
		float fParam1;
		float fBlurStrength;
		float frCamFocus;

		unsigned uBlur;
		unsigned uMotionBlur;
		unsigned uDistanceBlur;
		unsigned uEnhancedEdges;
		unsigned uLightGlow;
		unsigned uHighlightGlow;
		unsigned uFilmex;
		unsigned uMeanFilter;
		unsigned uGodRays;
		unsigned uGlowWhite;
		unsigned uSpecularWhite;
		unsigned uPad0;
		unsigned uRedStereo;
		unsigned uGreenBlueStereo;
		XMFLOAT2 f2rcpFrame;
		XMFLOAT4 f4rcpFrameOpt;
	};

	struct SViewportstyleBufferHost
	{
		XMFLOAT4 d3dxcolorOutline;		// Kontur-Viewportfarbe
		XMFLOAT4 d3dxcolorFogParams;		// Nebel-Parameter
		XMFLOAT4X4 mColorModification; // Farbveraenderungsmatrix

		unsigned uStyleColor;
		unsigned uStyleHalfTransparent;
		unsigned uStylePopart;
		unsigned uStyleOutlining;
		unsigned uStyleMonochrome;
		unsigned uStyleOwn;
		unsigned uStyleFog;
		unsigned uPad0;
	};

#pragma pack(push, 1)
	struct SMaterialParameters
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
		unsigned uTextureAddressMode;
		XMVECTOR offset;
	};
	
	struct SPostprocessingBuffer
	{
		XMVECTOR d3dxcolor;
		float fBlurStrength;
		unsigned uBlur;
		unsigned uEnhancedEdges;
		unsigned uMeanFilter;
		float fBloomOriginalIntensity;
		float fBloomIntensity;
		float fBloomOriginalSaturation;
		float fBloomSaturation;
		float fRayExposure;
		float fRayDecay;
		float fRayDensity;
		float fRayWeight;
		unsigned uPad0;
		float fBloomBlurDistance;
		unsigned uPad1;
		unsigned uPad3;
		XMVECTOR f2RayLightPos;
		XMVECTOR f2rcpFrame;
		XMVECTOR f4rcpFrameOpt;
	};
	

	struct SViewportstyleBuffer
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

	/*
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
	*/
	class CDirectX11Basic : public CApiRender
	{
		friend class CDXUtilities;

	protected:
		CDXUtilities *m_pUtils;
		IDXGISwapChain *m_pswapchain;

		// Hauptvariablen:
		CViewport *m_pcurrentViewort;
		IDXGISwapChain *m_pswapChain;
		ID3D11Device *m_pdevice;
		ID3D11DeviceContext *m_pdevicecontext;
		ID3D11RenderTargetView *m_prendertargetviewBackBuffer;

		ID3D11Buffer *m_pbufferViewportStyle;

		SLightStructure *m_plightstructure; 

		// I need those for soft particles. I thought it is better to store them in this class instead of the particle renderer since someone else might need that as well later. (MR)
		float m_fNearClipping;
		float m_fFarClipping;
		int m_iActiveViewportHeight;
		int m_iActiveViewportWidth;

		// SShader *m_pShader;
		D3D11_BUFFER_DESC m_bufferdescVertex;
		ID3D11Buffer *m_pVBuffer;
		ID3D11Buffer *m_pbufferLights;
		ID3D11ShaderResourceView *m_pshaderresourceviewLights;
		SVertexBuffer *m_pvertexGeo;
		BufferMap m_buffermap;
		SObjectShaderConstants m_objectshaderconstants;
		SObjectShaderConstants m_objectshaderconstantsParallelProjection;
		SObjectShaderConstants m_objectshaderconstantsParallelProjectionMirror;
		ID3D11SamplerState *m_psamplerstateLinearWrap;
		ID3D11SamplerState *m_psamplerstateLinearClamp;
		ID3D11SamplerState *m_psamplerstateLinearMirror;
		ID3D11InfoQueue * m_pInformationQueue;
		int m_iCurMsg;
		ID3D11Query * m_pEventQuery;

		// Depth Stencil:
		ID3D11DepthStencilView *m_pdepthstencilview;
		ID3D11Texture2D *m_ptextureDepthStencil;
		ID3D11ShaderResourceView * m_psrvDepthStencil;

		// Hauptshader: 
		ID3D11PixelShader *m_ppixelshader;
		ID3D11VertexShader *m_pvertexshader;
		ID3D11InputLayout *m_pinputlayout;
		D3D11_INPUT_ELEMENT_DESC* m_pinputLayoutDesc;
		ID3D11Buffer *m_pbufferProjectionMatrix;
		ID3D11Buffer *m_pbufferTexInfo;
		ID3D11Buffer *m_pbufferGPU;
		SMaterialParametersHost * m_amaterialparameters;
		SViewportstyleBufferHost m_viewportstylebuffer;
		D3D11_RASTERIZER_DESC * m_arasterizerdesc;
		ID3D11RasterizerState ** m_aprasterizerstate;
		ID3D11SamplerState * m_psamplerstateActive;

		// Shadowmapping
		SShadowmapShaderConstants m_shadowmapshaderconstants;
		ID3D11Buffer *m_pbufferProjectionMatrixShadowMap;
		ID3D11VertexShader *m_pvertexshaderShadowMap;
		ID3D11PixelShader *m_ppixelshaderShadowMap;
		ID3D11Texture2D *m_ptextureShadowMap;
		ID3D11DepthStencilView *m_pdepthstencilviewShadowMap;
		ID3D11ShaderResourceView *m_pshaderresourceviewShadowMap;
		ID3D11SamplerState *m_psamplerstateShadow;

		// Anderes:
		void CopyCHMatToXMFLOAT4X4(CHMat &m, XMFLOAT4X4 &f4);
		void CopyXMFLOAT4X4ToCHMat(XMFLOAT4X4 &f4, CHMat &m);


		// Postprozess-Shader-Variablen:
		ID3D11VertexShader *m_pvertexshaderPostprocessing;
		ID3D11PixelShader *m_ppixelshaderPostprocessing;
		ID3D11InputLayout *m_pinputlayoutPostprocessing;
		ID3D11Buffer *m_pbufferProjectionMatrixPostprocessing;

		ID3D11Buffer *m_pbufferTexInfoPostprocessing;

		SPostprocessingBufferHost m_viewportstylebufferPostprocessing;
		D3D11_RASTERIZER_DESC * m_arasterizerdescPostprocessing;
		ID3D11RasterizerState ** m_aprasterizerstatePostprocessing;

		ID3D11VertexShader *m_pvertexShaderOcc;
		ID3D11PixelShader *m_ppixelShaderOcc;

		// contains all lights
		std::vector<CLight*>m_vplightShadowCaster;	// TODO: make this an array
		CLight **m_pplight;
		int m_iLights;

		int TexturePathExists(char *acPath);
		bool CreateTexture(CTexture * ptexture, int eDefaultImage, int & iTexture);

		void PassToGPU(SRenderObjectHandle & handle, int & idTexture);
		void SetObjectDrawingParameters(CHMat &m, const unsigned int * pLightsAffectIndices, const unsigned int iLightsAffectCount);
		void SetSpriteDrawingParameters(CHMat &m);

		unsigned int GetMSAAQuality(unsigned int uiSamples, DXGI_FORMAT format);

		void InitShaderPostprocessing();
		void InitOcculusShader();
	public:
		EApiRender m_eApiRender;

		// Texturen:
		int m_iTextures;
		int m_iTextureAllocs;
		STextureInfo * m_atextureinfo;

		ID3D11Texture2D *m_ptextureBackBuffer;
		CDirectX11Basic();
		void ChangeRenderStatePostprocessing(CViewport *pviewport);
		void Postprocessing(CViewport *pviewport);

		CDXUtilities* CDirectX11Basic::Utils();
		// Die heilige Dreifaltigkeit der Gameentwickler: 
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
		// SRenderObjectHandle CreateBuffer(CDrawable *pdrawable, void *pData, D3D11_BUFFER_DESC &bd, int *pIndices = 0, int iindicesCount = 0);
		HRESULT CreateSRVFromFile(char const *pFileName, ID3D11ShaderResourceView **ppSRV);
		HRESULT CreateSamplerState(D3D11_SAMPLER_DESC const *pSamplerDesc, ID3D11SamplerState **ppSamplerState);
		void FreeHandle(SRenderObjectHandle handle);
		void CopyBuffer(ID3D11Buffer *pDest, ID3D11Buffer *pSrc);

		// drawing
		void SetShaderResources(int iShaderTypes, int iStartSlot, int iCount, ID3D11ShaderResourceView **apSRVs = 0);
		void SetShaderSamplers(int iShaderTypes, int iStartSlot, int iCount, ID3D11SamplerState **apSamplers = 0);
		void Draw(SRenderObjectHandle & handle, int & idTexture, float fDistanceToCameraSquare, int iKind, CHMat & mGlobal, CLight **aplightAffect, unsigned int iLightsAffectCount);
		void CreateMaterial(CMaterial * pmaterial);
		void UpdateMaterial(CMaterial * pmaterial);
		void UpdateMaterialAni(CMaterial * pmaterial);

		bool DeleteMaterial(CMaterial * pmaterial);
		bool DeleteTexture(int iTexture);

		/*

		// shading
		int CreateShader(WCHAR *pFilename, LPCSTR pFunctionname, LPCSTR pShaderModel, EShaderType type, D3D11_INPUT_ELEMENT_DESC const *pied = 0, int iiedCount = 0, bool bforceCompile = false);
		void SetShader(int iShader, ID3D11ShaderResourceView **aSRVs = 0, int iSRVs = 0);
		void UnsetShader(EShaderType etype, int iSRVs);


		// computing
		ID3D11ShaderResourceView *GetLightsSRV() { return m_pshaderresourceviewLights; }
		void SetConstantBuffers(ID3D11Buffer **apConstantBuffers, int iStartSlot, int iCount, int iShaderTypes = -1);
		void RunComputeShader(int iCS, ID3D11UnorderedAccessView ** aUAVs, int iUAVs, ID3D11ShaderResourceView ** aSRVs, int iSRVs, int aThreadGroups[3], UINT *piUAVElementCounts = 0);
		void RunComputeShaderIndirect(int iCS, ID3D11UnorderedAccessView ** aUAVs, int iUAVs, ID3D11ShaderResourceView ** aSRVs, int iSRVs, ID3D11Buffer * pbThreadGroups, UINT uiAlignedOffsetForArgs, UINT *piUAVElementCounts = 0);
		void TransferFromGPU(ID3D11Resource * pResource, int iSubresource, BYTE * pBuffer, int iSize);
		void TransferToGPU(ID3D11Resource * pResource, int iSubresource, BYTE * pBuffer, int iSize, bool bUseStagingBuffer = false);
		HRESULT CreateStructuredBuffer(UINT uElementSize, UINT uCount, VOID * pInitData, ID3D11Buffer ** pBufOut, bool bOrdered);
		HRESULT CreateTypedBuffer(UINT uElementSize, UINT uCount, VOID* pInitData, ID3D11Buffer ** pBufOut, ID3D11UnorderedAccessView ** pUAVOut, bool bOrdered);
		HRESULT CreateConstantBuffer(UINT uElementSize, UINT uCount, VOID * pInitData, ID3D11Buffer ** pBufOut);
		HRESULT CreateBufferUAV(SRenderObjectHandle handle, ID3D11UnorderedAccessView ** pUAVOut);
		HRESULT CreateBufferUAV(ID3D11Buffer * pBuffer, ID3D11UnorderedAccessView ** pUAVOut, bool bAppendBuffer = false, bool bCounterIfNotAppend = false);
		HRESULT CreateBufferSRV(ID3D11Buffer * pBuffer, ID3D11ShaderResourceView ** pSRVOut);
		HRESULT CreateScan(ID3DX11Scan **ppScan, int iMaxElementScanSize);
		*/
		//particles
		void AddEmitter(CEmitter * pEmitter);
		void UpdateEmitterData(CEmitter * pEmitter);
		//debugging
		void CreateInformationQueue();
		bool GetNextMessage(char * pMsg, unsigned int uiSize);
		DXGI_ADAPTER_DESC QueryGraphicsCard();
		void InitProfiling();
		void WaitForShaderExecution();

		int m_iShaders;
		int m_iViewports;

		// feel free to enhance this method so that passing a buffer is OPTIONAL (don't remove it completely). (MR)
		UINT GetStructureCount(ID3D11UnorderedAccessView * UAV, ID3D11Buffer * buffer, UINT uiDstAlignedByteOffset = 0);
	protected:
		void DrawTriangleList(ID3D11Buffer *pbuffer);
		void DrawTriangleStrip(ID3D11Buffer *pbuffer, ID3D11Buffer *indexBuffer);
	
		void DrawOpaqueObjects(bool bWithMaterials);
		void DrawTransparentObjects(bool bWithMaterials);
		void DrawPPGeometrie(CViewport* pViewport);
		void DrawBackGroundObjects();
		void DrawTransparentBinaryObjects(bool bWithMaterials);
		void DrawSprites();
		void SortTransparentObjects();

		void InitBackBuffer();
		void InitShader(EShaderCreation eShaderCreation);
		ID3D11SamplerState * GetSamplerStateBasedOnTextureAddressMode(ETextureAddressMode eTextureAddressMode);

		// Für Postprozessingeffekte (gerade in Arbeit) (TB):
		D3D11_TEXTURE2D_DESC * m_atexdescPostprocessing;
		ID3D11Texture2D **m_aptexturePostprocessing; // Textur, in die das fertig gerenderte Bild zwischengespeichert wird, dort unterliegt es einem Postprozess und wird danach erst in den Backbuffer geschrieben
		ID3D11RenderTargetView ** m_aprendertargetviewPostprocessing;
		ID3D11ShaderResourceView ** m_apshaderresourceviewPostprocessing;
		D3D11_RENDER_TARGET_VIEW_DESC * m_arendertargetviewdescPostprocessing;
		D3D11_SHADER_RESOURCE_VIEW_DESC * m_ashaderresourceviewdescPostprocessing;
		SPostprocessingShaderConstants m_postprocessingShaderConstants;
		bool m_bFirstPPDraw;
		CGeoQuad m_gPPQuad;
		CTriangleList* m_pgPPGeo;
		CMaterial m_mPPMaterial;
		SRenderObjectHandle** m_apPPRHND;

		bool m_bFirstDraw;

		D3D11_TEXTURE2D_DESC m_texdescStencil;
		D3D11_DEPTH_STENCIL_VIEW_DESC m_depthstencilviewdesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC m_shaderresourceviewdesc;

		D3D11_TEXTURE2D_DESC * m_atexdescShadow;
		D3D11_VIEWPORT * m_aviewport;
		D3D11_VIEWPORT * m_aviewportShadow;

		unsigned int m_uiSampleCount;
		unsigned int m_uiSampleQuality;

		D3D_FEATURE_LEVEL m_featurelevel;

		SMaterialInfo *m_amaterialinfo;
		int m_iMaterials;
		int m_iMaterialAllocs;

		// Variablen, um Objekte fuer die Transparenz bzw. Spites zu sortieren:
		CDrawObjects m_drawobjectsBackground;
		CDrawObjects m_drawobjectsSprite;
		CDrawObjects m_drawobjectsSpriteTransparent;
		CDrawObjects m_drawobjectsOpaque;
		CDrawObjects m_drawobjectsTransparent;
		CDrawObjects m_drawobjectsTransparentBinary;


		EShaderCreation m_eShaderCreation;
		EShaderAutoRecompilation m_eShaderAutoRecompilation;
		bool m_bInit;

		int m_iShadowMapWidth;
		int m_iShadowMapHeight;

		CHMat m_mProjectionOverlayMirror;
		CHMat m_mProjectionOverlay;
		CHMat m_mViewOverlay;
		CHMat m_mWorldOverlay;

		CShaderCache* m_pShaderCache;
	};

}