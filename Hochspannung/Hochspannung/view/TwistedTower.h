#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class CTwistedTower
{
public:
	CTwistedTower(void);
	~CTwistedTower(void);

	//void Init(HWND hwnd, CSplash * psplash);
	//void Tick(float fTime, float fTimeDelta);
	//void Fini();

	CPlacement* getPlacement();

	void WindowReSize(int iNewWidth, int iNewHeight); // WindowsReSize wird immer dann aufgerufen, wenn der Benutzer die Fenstergröße verändert hat

private:

	void InitWindows();
	void InitWalls();
	void AddWindows();
	void CreateMiters();
	void AddPlacements();
	void RotateAll();
	void TranslateAll();

	float fResize;
	//HWND m_hwnd;
	//bool m_bReSized;
	// Hier ist Platz für Deine Vektoriaobjekte:
	//CRoot m_zr;
	//CScene m_zs;

	// Placements
	//CPlacement m_zpCamera;
	CPlacement m_zpTwistedTower;

	CPlacement m_zpWindow;

	//CPlacement m_zpGround;
	CPlacement m_zpRoof;

	CPlacement m_zpWallNorth;
	CPlacement m_zpWallEast;
	CPlacement m_zpWallWest;

	//Walls
	//CGeoWall m_zgGround;
	CGeoWall m_zgRoof;

	CGeoWall m_zgWallNorth;
	CGeoWall m_zgWallEast;
	CGeoWall m_zgWallWest;

	//Windows
	CGeoWindow m_zgWindow;



	//Rest
	//CHardware m_zh;
	//CFrame m_zf;
	//CViewport m_zv;
	//CCamera m_zc;
	//CParallelLight m_zl;
	CMaterial m_zm;
	//CDeviceKeyboard m_zdk;;

};


NAMESPACE_VIEW_E
