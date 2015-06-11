#pragma once

#include "Placement.h"
#include "Cameras.h"

//------------------------------------
// CPlacements, Pluralklasse von CPlacement
// Copyright: Prof. Dr. Tobias Breiner
// Pfungstadt, 11.10.2011
//------------------------------------

namespace Vektoria
{

class CPlacements
{
public:
	CPlacements();
	~CPlacements();
	CPlacements operator=(CPlacements placements);

	void Init();
	void Tick(CHMat & m, float & fTimeDelta, bool & bTickTack);
	void Fini();


	void Add(CPlacement * pplacement); // Fügt pplacement in die Liste hinzu
	bool AddOnce(CPlacement * pplacement); // Schaut, ob Placement schon in der Liste vorhanden ist, nur wenn nicht,  wird es hinzugefügt und true ausgegeben
	void Add(CPlacements * pplacements); // Addiert gleich eine ganze Reihe von Placments dazu

	bool Has(CPlacement * pplacement); // Schaut, ob pplacement in der Liste vorhanden ist, wenn ja, wird true ausgegeben

	bool Sub(CPlacement * pplacement);
	void Clear();

	CPlacement * Make();
	bool Kill(CPlacement * pplacement);

	void Draw(CCamera * pcamera, CHMat & mGlobalFather, int & itFatherIsInFrustum, bool & bTickTack);
	void DontDraw(bool &bTickTack);

	void SearchForCameras(CCameras * pcameras);

	CPlacement * Pick(CRay & r);


	CPlacement ** m_applacement;
	int m_iPlacementAllocs;
	int m_iAllocBlock;
	int m_iPlacements;

	int * m_aiInst; // Instzanzennummer des i. Placements für den Vater


	void SetRoot(CRoot * proot);
	CRoot * m_proot;
};

}