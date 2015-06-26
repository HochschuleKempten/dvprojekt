#pragma once

#include "VGeneral.h"
#include "IViewModel.h"

NAMESPACE_VIEW_B


class CAppartments : public CPlacement, public IViewModel
{
public:
	CAppartments();
	explicit CAppartments(float fResize);
	~CAppartments(void);
	virtual void init() override;

	void InitWindows();
	void InitWalls();
	void AddWindows();
	void AddPlacements();
	void RotateAll();
	void TranslateAll();
	void ScaleForLod();
	
private:



	float fResize;


	CPlacement m_zpWallNorth;
	CPlacement m_zpWallSouth;
	CPlacement m_zpWallWest;
	CPlacement m_zpWallEast;

	CPlacement m_zpRoof;
	

	CPlacement m_zpWindow;



	//Walls
	CGeoWall m_zgWallNorth;
	CGeoWall m_zgWallSouth;
	CGeoWall m_zgWallEast;
	CGeoWall m_zgWallWest;

	CGeoWall m_zgRoof;
	

	//Windows
	CGeoWindow m_zgWindow;

	//Frame
	CGeoWall m_zgFrame;

};


NAMESPACE_VIEW_E
