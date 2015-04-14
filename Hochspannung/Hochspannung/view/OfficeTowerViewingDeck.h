#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class COfficeTowerViewingDeck
{
public:
	COfficeTowerViewingDeck(float fResize);
	~COfficeTowerViewingDeck(void);

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
	void TranslateAll();
	void Round();


	float fResize;
	//HWND m_hwnd;
	//bool m_bReSized;


	// Hier ist Platz für Deine Vektoriaobjekte:
	//CRoot m_zr;
	//CScene m_zs;

	// Placements
	//CPlacement m_zpCamera;
	CPlacement m_zpOfficeTower;


	CPlacement m_zpWall;
	CPlacement m_zpWallTop;

	CPlacement m_zpRoof;
	CPlacement m_zpRoofTop;
	//CPlacement m_zpGround;


	CPlacement m_zpWindow;
	CPlacement m_zpRailing;


	//Walls
	CGeoWall m_zgWall;


	CGeoWall m_zgWallTop;
	CGeoWall m_zgRoof;
	CGeoWall m_zgRoofTop;
	//CGeoWall m_zgGround;

	//Windows
	CGeoWindow m_zgWindow;
	CGeoWindow m_zgRailing;

	//Frame
	CGeoWall m_zgFrame;

	//Combinations


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
