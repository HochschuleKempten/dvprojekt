#include "VGeneral.h"
#include "Helper.h"

NAMESPACE_VIEW_B

class VModelPowerLine : public CPlacement
{
public:
	VModelPowerLine(void);
	~VModelPowerLine(void);

	void Init();
private:
	CHelper m_Helper;

	//vectors for foundation
	CHVector m_zvFoundation1;		//for edge length
	CHVector m_zvFoundation2;		//for placement

	//vector for base poles
	CHVector m_zgvPoles;
	CHVector m_zpvPole1;
	CHVector m_zpvPole2;
	CHVector m_zpvPole3;
	CHVector m_zpvPole4;

	//vector for upper poles
	CHVector m_zpvUpperPole1;
	CHVector m_zpvUpperPole2;
	CHVector m_zpvUpperPole3;
	CHVector m_zpvUpperPole4;

	CHVector m_zgvUpperPole1;
	CHVector m_zgvUpperPole2;

	////vector for basis poles
	CHVector m_zgvBasisPoles;

	CMaterial m_zmBlack;
	CMaterial m_zmGrey;

	CGeoCube m_zgFoundation;
	
	CPlacement m_zpFoundation;

	CPlacement m_zpBasis;
	CPlacement m_zpHead;
	CPlacement m_zpRightConduit;
	CPlacement m_zpLeftConduit;

	//base poles
	CGeoCube m_zgPole1;
	CGeoCube m_zgPole2;
	CGeoCube m_zgPole3;
	CGeoCube m_zgPole4;

	CPlacement m_zpPole1;
	CPlacement m_zpPole2;
	CPlacement m_zpPole3;
	CPlacement m_zpPole4;

	//upper poles
	CGeoCube m_zgUpperPole1;
	CGeoCube m_zgUpperPole2;
	CGeoCube m_zgUpperPole3;
	CGeoCube m_zgUpperPole4;

	CPlacement m_zpUpperPole1;
	CPlacement m_zpUpperPole2;
	CPlacement m_zpUpperPole3;
	CPlacement m_zpUpperPole4;

	//geo and placement for basis poles
	CGeoCube m_zgBasisPoles[10];
	CGeoCube m_zgBasisPole1;
	CGeoCube m_zgBasisPole2;
	CGeoCube m_zgBasisPole3;
	CGeoCube m_zgBasisPole4;
	CGeoCube m_zgBasisPole5;
	CGeoCube m_zgBasisPole6;
	CGeoCube m_zgBasisPole7;
	CGeoCube m_zgBasisPole8;
	CGeoCube m_zgBasisPole9;
	CGeoCube m_zgBasisPole10;

	CPlacement m_zpBasisPoles[10];
	CPlacement m_zpBasisPole1;
	CPlacement m_zpBasisPole2;
	CPlacement m_zpBasisPole3;
	CPlacement m_zpBasisPole4;
	CPlacement m_zpBasisPole5;
	CPlacement m_zpBasisPole6;
	CPlacement m_zpBasisPole7;
	CPlacement m_zpBasisPole8;
	CPlacement m_zpBasisPole9;
	CPlacement m_zpBasisPole10;

	//placement for basis poles -> right/left/front/back
	CPlacement m_zpFrontPoles;
	CPlacement m_zpBackPoles;
	CPlacement m_zpLeftPoles;
	CPlacement m_zpRightPoles;

	//poles for roof
	CGeoCube m_zgRoofPole1;
	CGeoCube m_zgRoofPole2;
	CGeoCube m_zgRoofPole3;
	CGeoCube m_zgRoofPole4;

	CPlacement m_zpRoofPole1;
	CPlacement m_zpRoofPole2;
	CPlacement m_zpRoofPole3;
	CPlacement m_zpRoofPole4;

	//poles for right conduit
	CGeoCube m_zgRightConduit1;
	CGeoCube m_zgRightConduit2;
	CGeoCube m_zgRightConduit3;
	CGeoCube m_zgRightConduit4;

	CPlacement m_zpRightConduit1;
	CPlacement m_zpRightConduit2;
	CPlacement m_zpRightConduit3;
	CPlacement m_zpRightConduit4;

	void placeFoundation(void);
	void placeBasis(void);
	void placeHead(void);
	void placeConduit(void);


	void makeWall(void);

	CGeoWall m_zgBaseWall;
	CPlacement m_zpBaseWall;
	CGeoWindow m_zgWindowTri;
	CGeoWindow m_zgWindowRect;

	float m_fWidth = 1.0f;
	float m_fHeight = 2.0f;
	float m_fThickness = 0.05f;
};

NAMESPACE_VIEW_E
