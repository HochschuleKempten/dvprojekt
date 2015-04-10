#pragma once
#include "Vektoria\Root.h"
#include "VektoriaMath\Util.h"

using namespace Vektoria;

class CTrasseSling
{
public:
	CTrasseSling();
	~CTrasseSling();

	void Init(CScene * pScene);

private:
	CGeoCylinder m_zgBasePole;
	CGeoSlice m_zgWing;

	CPlacement m_zpBasePole;
	CPlacement m_zpWingLeft;
	CPlacement m_zpWingRight;

	CMaterial m_zmBasePole;
	CMaterial m_zmWing;

	float m_fPoleHeight;
	float m_fPoleRadius;
	float m_fWingHeight;
	float m_fWingBendRadius;


	CHVector m_zgvFoundation;  //for edge length
	CHVector m_zpvFoundation;  //for placement
	CMaterial m_zmGrey;

	CGeoCube m_zgFoundation;

	CPlacement m_zpFoundation;
};

