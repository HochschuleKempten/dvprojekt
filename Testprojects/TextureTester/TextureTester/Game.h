#pragma once


#ifdef _WIN64
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug64.lib")
#pragma comment (lib, "VektoriaMath_Debug64.lib")
#pragma comment (lib, "ApiUtils_Debug64.lib")
#pragma comment (lib, "ApiNullRenderer_Debug64.lib")
#pragma comment (lib, "ApiDirectX11Basic_Debug64.lib")
#pragma comment (lib, "ApiDirectInput08_Debug64.lib")
#pragma comment (lib, "ApiDirectX11FP_Debug64.lib")
#pragma comment (lib, "ApiOpenGL40_Debug64.lib")
#pragma comment (lib, "ApiNullSound_Debug64.lib")
#pragma comment (lib, "ApiDirectSound_Debug64.lib")
#else
#pragma comment (lib, "Vektoria_Release64.lib")
#pragma comment (lib, "VektoriaMath_Release64.lib")
#pragma comment (lib, "ApiUtils_Release64.lib")
#pragma comment (lib, "ApiNullRenderer_Release64.lib")
#pragma comment (lib, "ApiDirectX11Basic_Release64.lib")
#pragma comment (lib, "ApiDirectInput08_Release64.lib")
#pragma comment (lib, "ApiDirectX11FP_Release64.lib")
#pragma comment (lib, "ApiOpenGL40_Release64.lib")
#pragma comment (lib, "ApiNullSound_Release64.lib")
#pragma comment (lib, "ApiDirectSound_Release64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug.lib")
#pragma comment (lib, "VektoriaMath_Debug.lib")
#pragma comment (lib, "ApiUtils_Debug.lib")
#pragma comment (lib, "ApiNullRenderer_Debug.lib")
#pragma comment (lib, "ApiDirectX11Basic_Debug.lib")
#pragma comment (lib, "ApiDirectInput08_Debug.lib")
#pragma comment (lib, "ApiDirectX11FP_Debug.lib")
#pragma comment (lib, "ApiOpenGL40_Debug.lib")
#pragma comment (lib, "ApiNullSound_Debug.lib")
#pragma comment (lib, "ApiDirectSound_Debug.lib")
#else
#pragma comment (lib, "Vektoria_Release.lib")
#pragma comment (lib, "VektoriaMath_Release.lib")
#pragma comment (lib, "ApiUtils_Release.lib")
#pragma comment (lib, "ApiNullRenderer_Release.lib")
#pragma comment (lib, "ApiDirectX11Basic_Release.lib")
#pragma comment (lib, "ApiDirectInput08_Release.lib")
#pragma comment (lib, "ApiDirectX11FP_Release.lib")
#pragma comment (lib, "ApiOpenGL40_Release.lib")
#pragma comment (lib, "ApiNullSound_Release.lib")
#pragma comment (lib, "ApiDirectSound_Release.lib")
#endif
#endif




#include "Vektoria\Root.h"
#include "VektoriaMath\Util.h"

using namespace Vektoria;


class CGame
{
public:
    CGame(void);
    ~CGame(void);

	void Init(HWND hwnd, CSplash * psplash);
	void Tick(float fTime, float fTimeDelta);
	void Fini();

	void WindowReSize(int iNewWidth, int iNewHeight); // WindowsReSize wird immer dann aufgerufen, wenn der Benutzer die Fenstergr��e ver�ndert hat

private:
    // Hier ist Platz f�r Deine Vektoriaobjekte:
	CRoot m_root;
	CFrame m_frame;
	CViewport m_viewport;
	CCamera m_camera;
	CPlacement m_placeCamera;
	CScene m_scene;
	CPlacement m_placeLight;
	CParallelLight m_light;
	CPlacement m_placeQuad0;
	CPlacement m_placeQuad1;
	CPlacement m_placeQuad2;
	CPlacement m_placeQuad3;
	CPlacement m_placeQuad4;
	CPlacement m_placeQuad5;
	CPlacement m_placeQuad6;
	CPlacement m_placeQuad7;
	CPlacement m_placeQuad8;
	CMaterial m_quadMaterial;
	CGeoQuad m_quad;
	CGeoSphere m_sphere;
};


