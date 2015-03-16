#pragma once

//------------------------------------------------------------------
// OpenGL40: Klasse zur OpenGL 4.0-Anbindung
//
// Autor:  
// Letzte Änderung: 2014-07-15
//-------------------------------------------------------------------

#include "../Vektoria/ApiRender.h"

namespace Vektoria
{

class COpenGL40 : public CApiRender
{
public:
	COpenGL40(void);
	~COpenGL40(void);

	// Geburt, Leben und Sterben:
	void Init(HWND hwnd, int iWidthWindow, int iHeightWindow, EApiRender eApiRender, EShaderCreation eShaderCreation, EShaderAutoRecompilation eShaderAutoRecompilation);
	void Tick();
	void Fini();

	// Viewport:
	void AddViewport(CViewport *pviewport);
	void BeginRenderViewport(CHMat & mProjection, CHMat & mView,  CHMat & mViewInv, CViewport &mViewport);
	void EndRenderViewport(CViewport * pviewport);
	void ChangeRenderState(CViewport *pviewport, bool bCullNone = false);
	void ChangeResolution(CViewport *pviewport);
	void Postprocessing(CViewport *pviewport);

	// Schatten:
	void ResizeShadowMap(int iWidth, int iHeight);
	void BeginRenderShadow(CLight *plight, CViewport *pViewport);
	void EndRenderShadow();
	void ChangeRenderStateShadow(CViewport *pviewport);

	// Texturen und Materialien:
	void CreateMaterial(CMaterial * pmaterial);
	void UpdateMaterial(CMaterial * pmaterial); 		
	void UpdateMaterialAni(CMaterial * pmaterial);
	bool DeleteMaterial(CMaterial * pmaterial);

	// Licht:
	SRenderObjectHandle CreateLight(CLight *plight);
	void DestroyLight(SRenderObjectHandle & hLight);


	// Geometrie:
	SRenderObjectHandle CreateTriangleList(CTriangleList *ptriangleList);
	SRenderObjectHandle CreateTriangleStrip(CTriangleStrip *ptriangleStrip);
	void UpdateTriangleList(CTriangleList *ptrianglelist, SRenderObjectHandle & handle);
	void UpdateTriangleStrip(CTriangleStrip *ptrianglestrip, SRenderObjectHandle & handle);
	void FreeHandle(SRenderObjectHandle handle);
	void Draw(SRenderObjectHandle & handle, int & idTexture,float fDistanceToCameraSquare, int iKind, CHMat & mGlobal, CLight **pLightsAffect, unsigned int iLightsAffectCount);
	
	// Particles: 
	void AddEmitter(CEmitter * pEmitter);
	void UpdateEmitterData(CEmitter * pEmitter);
};

}