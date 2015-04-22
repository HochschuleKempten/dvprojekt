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


	void Add(CPlacement * pplacement);
	void Add(CPlacements * pplacements); // addiert gleich eine ganze Reihe von Placments dazu

	bool Sub(CPlacement * pplacement);
	void Clear();

	CPlacement * Make();
	bool Kill(CPlacement * pplacement);

	void Draw(CCamera * pcamera, CHMat & mGlobalFather, int & itFatherIsInFrustum, bool & bTickTack);
	void DontDraw(bool &bTickTack);

	void SearchForCameras(CCameras * pcameras);

	void SetFrustumCullingOn();
	void SetFrustumCullingOff();
	void SetBVHExactCalculationOn();
	void SetBVHExactCalculationOff();



	CPlacement ** m_applacement;
	int m_iPlacementAllocs;
	int m_iAllocBlock;
	int m_iPlacements;

	void SetRoot(CRoot * proot);
	CRoot * m_proot;
};

}