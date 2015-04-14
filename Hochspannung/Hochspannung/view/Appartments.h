#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class CAppartments
{
public:
	CAppartments(float fResize);
	~CAppartments(void);

	//void Init(HWND hwnd, CSplash * psplash);
	//void Tick(float fTime, float fTimeDelta);
	//void Fini();
	CPlacement* getPlacement();

	void WindowReSize(int iNewWidth, int iNewHeight); // WindowsReSize wird immer dann aufgerufen, wenn der Benutzer die Fenstergröße verändert hat

private:

	void InitWindows();
	void InitWalls();
	void AddWindows();
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
	CPlacement m_zpAppartments;


	CPlacement m_zpWallNorth;
	CPlacement m_zpWallSouth;
	CPlacement m_zpWallWest;
	CPlacement m_zpWallEast;

	CPlacement m_zpRoof;
	//CPlacement m_zpGround;

	CPlacement m_zpWindow;



	//Walls
	CGeoWall m_zgWallNorth;
	CGeoWall m_zgWallSouth;
	CGeoWall m_zgWallEast;
	CGeoWall m_zgWallWest;

	CGeoWall m_zgRoof;
	//CGeoWall m_zgGround;

	//Windows
	CGeoWindow m_zgWindow;

	//Frame
	CGeoWall m_zgFrame;




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
