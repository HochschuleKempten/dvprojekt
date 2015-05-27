#pragma once
#include "../VektoriaMath/HMat.h"
#include "Material.h"
#include <Windows.h>
#include "Emitter.h"
// #include "..\ApiUtils\Shadercache.h"

//---------------------------------------------------
// CApiRender
//
// Autoren: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2015-01-28
//---------------------------------------------------

namespace Vektoria
{

#define DRAWOBJECT_3D_OPAQUE 0 // undurchsichtige Textur ohne Alpha oder Transparent
#define DRAWOBJECT_3D_TRANSPARENT_CONTINUAL 1 // z.B. Textur mit Alphakanal > 1Bit
#define DRAWOBJECT_3D_TRANSPARENT_BINARY 2 // z.B. ChromaKeying-Textur
#define DRAWOBJECT_2D_OVERLAY_OPAQUE 3  // Undurchsichtige Overlay-Textur
#define DRAWOBJECT_2D_OVERLAY_TRANSPARENT_CONTINUAL 4// z.B. Textur mit Alphakanal > 1Bit
#define DRAWOBJECT_2D_OVERLAY_TRANSPARENT_BINARY 5 // z.B. ChromaKeying-Textur
#define DRAWOBJECT_2D_BACKGROUND 6 // Undurchsichtige Background-Textur

	class CViewport;
	class CVertex;
	class CTriangleList;
	class CTriangleStrip;
	class CLight;

	// Render-API:
	enum EApiRender
	{
		eApiRender_Null,
		eApiRender_DirectX11_Shadermodel41,
		eApiRender_DirectX11_Shadermodel50_Own,
		eApiRender_DirectX11_Shadermodel50_Minimalistic,
		eApiRender_DirectX11_Shadermodel50_Reduced,
		eApiRender_DirectX11_Shadermodel50_Basic,
		eApiRender_DirectX11_Shadermodel50,
		eApiRender_DirectX11_ForwardPlus,
		eApiRender_OpenGL40
	};

	// Input-API:
	enum EApiInput
	{
		eApiInput_Null,				// Nullinput.
		eApiInput_DirectInput,		// DirectInput8.
		eApiInput_SDL				// Not implemented yet.
	};

	// Erstellungsmodus für Shader
	enum EShaderCreation
	{
		eShaderCreation_ForceCompile,		// Leere den Cache und kompiliere alle Shader neu
		eShaderCreation_CompileChanges,		// Kompiliere die Shader, die sich geändert haben
		eShaderCreation_UseCached			// Benutze nur die Shader aus dem Cache		
	};

	// Automatisches Shader-Rekompilieren
	enum EShaderAutoRecompilation
	{
		eShaderAutoRecompilation_Disabled, // Shader nur beim Programmstart kompilieren
		eShaderAutoRecompilation_Enabled   // Automatisches Rekompilieren von Shadern
	};

	// Arten der Renderobjekte, die an den Shader übergeben werden können.
	enum ERenderObjectType
	{
		eRenderObjectType_Undefined = -1,
		eRenderObjectType_TriangleList,
		eRenderObjectType_TriangleStrip,
		eRenderObjectType_Light
	};

	// Handle für jedes Objekt, welches an den Shader übergeben wurde
	struct SRenderObjectHandle
	{
		ERenderObjectType eRenderObjectType;
		unsigned int id;
		unsigned int indexBufferId;
	};





class CApiRender
{
public:
	// Konstruktor und Destruktor:
	CApiRender(void);
	~CApiRender(void);

	// Geburt, Leben und Sterben:
	virtual void Init(HWND hwnd, int iWidthWindow, int iHeightWindow, EApiRender eApiRender, EShaderCreation eShaderCreation, EShaderAutoRecompilation eShaderAutoRecompilation) = 0;
	virtual void Tick() = 0;
	virtual void Fini() = 0;

	// Viewport-Methoden:
	virtual void AddViewport(CViewport *pviewport) = 0;
	virtual void BeginRenderViewport(CHMat & mProjection, CHMat & mView, CHMat & mViewInv, CViewport &viewport) = 0;
	virtual void EndRenderViewport(CViewport * pviewport) = 0;
	virtual void ChangeRenderState(CViewport *pviewport, bool bCullNone = false) = 0;

	// Schatten:
	virtual void ResizeShadowMap(int iWidth, int iHeight) = 0;
	virtual void BeginRenderShadow(CLight *plight, CViewport *pviewport) = 0;
	virtual void EndRenderShadow() = 0;

	// Postprozess:
	virtual void Postprocessing(CViewport *pviewport) = 0;
	
	// Materialien:
	virtual void CreateMaterial(CMaterial * pmaterial) = 0;
	virtual void UpdateMaterial(CMaterial * pmaterial) = 0;
	virtual void UpdateMaterialAni(CMaterial * pmaterial) = 0;
	virtual bool DeleteMaterial(CMaterial * pmaterial) = 0;

	// Viewports:
	virtual void ChangeRenderStateShadow(CViewport *pviewport) = 0;
	virtual void ChangeResolution(CViewport *pviewport) = 0;

	// Licht:
	virtual SRenderObjectHandle CreateLight(CLight *plight) = 0;
	virtual void DestroyLight(SRenderObjectHandle & handleLight) = 0;

	// Triangle Strip/List Handling:
	virtual SRenderObjectHandle CreateTriangleList(CTriangleList *ptriangleList) = 0;
	virtual SRenderObjectHandle CreateTriangleStrip(CTriangleStrip *ptriangleStrip) = 0;
	virtual void UpdateTriangleList(CTriangleList *ptriangleList, SRenderObjectHandle & handle) = 0;
	virtual void UpdateTriangleStrip(CTriangleStrip *ptriangleStrip, SRenderObjectHandle & handle) = 0;

	// Zeichnen:
	virtual void Draw(SRenderObjectHandle & handle, int & idTexture,float fDistanceToCameraSquare, int iKind, CHMat & mGlobal, CLight **pLightsAffect, unsigned int iLightsAffectCount) = 0;
	virtual void FreeHandle(SRenderObjectHandle handle) = 0;

	// Particles:
	virtual void AddEmitter(CEmitter * pEmitter) = 0;
	virtual void UpdateEmitterData(CEmitter * pEmitter) = 0;
};

}