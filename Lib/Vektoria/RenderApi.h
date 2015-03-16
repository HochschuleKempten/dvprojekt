#pragma once
#include "../VektoriaMath/HMat.h"
#include "Material.h"
#include <Windows.h>
#include "Emitter.h"
// #include "..\ApiUtils\Shadercache.h"

//---------------------------------------------------
// CRenderApi
//
// Autoren: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2012-06-05
//---------------------------------------------------

namespace Vektoria
{

	// Render-API:
	enum ERenderApi
	{
		eRenderApi_Null,
		eRenderApi_DirectX11_Shadermodel41,
		eRenderApi_DirectX11_Shadermodel50,
		eRenderApi_DirectX11_ForwardPlus,
		eRenderApi_OpenGL40
	};

	// Input-API:
	enum EInputApi
	{
		eInputApi_Null,				// Nullinput.
		eInputApi_DirectInput,		// DirectInput8.
		eInputApi_SDL				// Not implemented yet.
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



/*
//	const CShaderCache::EShaderCreateType g_createType = CShaderCache::EShaderCreateType::eShaderCreation_UseCached;
//	const CShaderCache::EShaderCreateType g_createType = CShaderCache::EShaderCreateType::eShaderCreation_UseCached;
const CShaderCache::EShaderCreateType g_createType = CShaderCache::EShaderCreateType::eShaderCreation_CompileChanges;
const CShaderCache::EShaderAutoRecompilation g_compileType = CShaderCache::eShaderAutoRecompilation_Enabled;
*/

#define DRAWOBJECT_3D_OPAQUE 0 // undurchsichtige Textur ohne Alpha oder Transparent
#define DRAWOBJECT_3D_TRANSPARENT_CONTINUAL 1 // z.B. Textur mit Alphakanal > 1Bit
#define DRAWOBJECT_3D_TRANSPARENT_BINARY 2 // z.B. ChromaKeying-Textur
#define DRAWOBJECT_2D_OVERLAY_OPAQUE 3 
#define DRAWOBJECT_2D_OVERLAY_TRANSPARENT_CONTINUAL 4
#define DRAWOBJECT_2D_OVERLAY_TRANSPARENT_BINARY 5
#define DRAWOBJECT_2D_BACKGROUND 6


enum RTYPE
{
	RTYPE_UNDEFINED = -1,
	POLY,
	TRIANGLE_LIST,
	TRIANGLE_STRIP_INDEXED,
	DRAWABLE,
	LIGHT
};

class CDrawable;

struct RHND
{
	RTYPE type;
	unsigned int id;
  union
  {
	  unsigned int indexBufferId;
    CDrawable *pdrawable;
  };
};

class CViewport;
class CVertex;
class CTriangleList;
class CTriangleStrip;
class CLight;

class CRenderApi
{
public:
	CRenderApi(void);
	~CRenderApi(void);

	// Geburt, Leben und Sterben:
	virtual void Init(HWND hwnd, int iWidthWindow, int iHeightWindow, ERenderApi eRenderApi, EShaderCreation eShaderCreation, EShaderAutoRecompilation eShaderAutoRecompilation) = 0;
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
	virtual RHND CreateLight(CLight *plight) = 0;
	virtual void DestroyLight(RHND hLight) = 0;

	// Triangle Strip/List Handling:
	virtual RHND CreateTriangleList(CTriangleList *ptriangleList) = 0;
	virtual RHND CreateTriangleStrip(CTriangleStrip *ptriangleStrip) = 0;
	virtual void UpdateTriangleList(CTriangleList *ptriangleList, RHND & handle) = 0;
	virtual void UpdateTriangleStrip(CTriangleStrip *ptriangleStrip, RHND & handle) = 0;

	// Zeichnen:
	virtual void Draw(RHND & handle, int & idTexture,float fDistanceToCameraSquare, int iKind, CHMat & mGlobal, CLight **pLightsAffect, unsigned int iLightsAffectCount) = 0;
	virtual void FreeHandle(RHND handle) = 0;

	// Particles:
	virtual void AddEmitter(CEmitter * pEmitter) = 0;
	virtual void UpdateEmitterData(CEmitter * pEmitter) = 0;

};

}