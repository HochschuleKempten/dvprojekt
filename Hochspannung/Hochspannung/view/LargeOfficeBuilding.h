#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class CLargeOfficeBuilding
{
public:
	CLargeOfficeBuilding(float fResize);
	~CLargeOfficeBuilding(void);

	//void Init(HWND hwnd, CSplash * psplash);
	//void Tick(float fTime, float fTimeDelta);
	//void Fini();

	CPlacement* getPlacement();

	void WindowReSize(int iNewWidth, int iNewHeight); // WindowsReSize wird immer dann aufgerufen, wenn der Benutzer die Fenstergröße verändert hat

private:
	void InitWindows();
	void AddWindows();
	void InitWalls();
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
	CPlacement m_zpLargeOfficeBuilding;

	CPlacement m_zpWallNorth0;
	CPlacement m_zpWallNorth1;
	CPlacement m_zpWallNorth2;

	CPlacement m_zpWallSouth0;
	CPlacement m_zpWallSouth1;
	CPlacement m_zpWallSouth2;

	CPlacement m_zpWallWest;

	CPlacement m_zpWallEast0;
	CPlacement m_zpWallEast1;
	CPlacement m_zpWallEast2;

	CPlacement m_zpRoof0;
	CPlacement m_zpRoof1;
	CPlacement m_zpRoof2;

	//CPlacement m_zpGround;
	CPlacement m_zpDoor;
	CPlacement m_zpWindow;
	CPlacement m_zpWindowHigh;
	CPlacement m_zpWindowWide;


	//Walls
	CGeoWall m_zgWallNorth0;
	CGeoWall m_zgWallNorth1;
	CGeoWall m_zgWallNorth2;

	CGeoWall m_zgWallSouth0;
	CGeoWall m_zgWallSouth1;
	CGeoWall m_zgWallSouth2;

	CGeoWall m_zgWallEast0;
	CGeoWall m_zgWallEast1;
	CGeoWall m_zgWallEast2;
	CGeoWall m_zgWallWest;

	CGeoWall m_zgRoof0;
	CGeoWall m_zgRoof1;
	CGeoWall m_zgRoof2;

	//CGeoWall m_zgGround;

	//Windows
	CGeoWindow m_zgDoor;
	CGeoWindow m_zgWindow;
	CGeoWindow m_zgWindowHigh;
	CGeoWindow m_zgWindowWide;

	//Frame
	CGeoWall m_zgFrame;
	CGeoWall m_zgFrameHigh;

	//Combinations


	//Rest
	//CHardware m_zh;
	//CFrame m_zf;
	//CViewport m_zv;
	//CCamera m_zc;
	//CParallelLight m_zl;
	CMaterial m_zm;
	//CMaterial m_zmGround;
	//CMaterial m_zmGlass;
	//CDeviceKeyboard m_zdk;

};


NAMESPACE_VIEW_E
