#pragma once




#include "VGeneral.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


class COfficeTowerViewingDeck : public CPlacement
{
public:
	COfficeTowerViewingDeck();
	explicit COfficeTowerViewingDeck(float fResize);
	~COfficeTowerViewingDeck(void);
	void InitWindows();
	void AddWindows();
	void InitWalls();
	void AddPlacements();
	void TranslateAll();
	void Round();
	void ScaleForLod();
	



private:




	float fResize;



	CPlacement m_zpWall;
	CPlacement m_zpWallTop;

	CPlacement m_zpRoof;
	CPlacement m_zpRoofTop;

	CPlacement m_zpWindow;
	CPlacement m_zpRailing;


	//Walls
	CGeoWall m_zgWall;


	CGeoWall m_zgWallTop;
	CGeoWall m_zgRoof;
	CGeoWall m_zgRoofTop;

	//Windows
	CGeoWindow m_zgWindow;
	CGeoWindow m_zgRailing;

	//Frame
	CGeoWall m_zgFrame;

};



NAMESPACE_VIEW_E