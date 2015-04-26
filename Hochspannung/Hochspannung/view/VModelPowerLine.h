#include "IViewModel.h"
#include "VGeneral.h"
#include <bitset>

NAMESPACE_VIEW_B

class VModelPowerLine : public IViewModel
{
public:
	enum DIRECTION
	{
		NORTH = 0x1,
		EAST = 0x2,
		SOUTH = 0x4,
		WEST = 0x8
	};

	enum PYLONTYPE
	{
		STRAIGHT, CROSS, ANGLE
	};

	friend DIRECTION operator|(DIRECTION a, DIRECTION b);
	VModelPowerLine(float fFieldSize);
	VModelPowerLine(void);
	virtual ~VModelPowerLine(void) override;
	map<DIRECTION, vector<VModelPowerLine *>> * Connections();
	VModelPowerLine::PYLONTYPE PylonType();
	vector<CHVector> * ConnectorPositions(VModelPowerLine::DIRECTION armPosition);

	void Init(VModelPowerLine::DIRECTION eDirection, float fFoundationWidth = 0.1f, float fPylonHeight = 1.0f);
	void SetPosition(int x, int y);
	//bool ConnectTo(VModelPowerLine *pPylon);
	//USHORT AddConnection(VModelPowerLine * pPylon, DIRECTION eConnectorPosition);
	//bool DisconnectFrom(VModelPowerLine * pPylon);
	//bool DisconnectAll();

	virtual float getHeight() override; // including foundation
	virtual float getWidth() override;  // width of the foundation

private:
	std::vector<VModelPowerLine::DIRECTION> DetermineArm(VModelPowerLine *pPylon);
	//TODO (Pylon) consider using normal variable types instead of pointers here (less heap allocations)
	//You may be able to use std::vector<CPlacement> as well
	std::vector<CPlacement> m_zpIsolator;
	std::vector<CPlacement> m_zpIsolatorLoD1;
	std::vector<CPlacement> m_zpIsolatorLoD2;
	std::vector<CPlacement> m_zpIsolatorLoD3;
	std::vector<CPlacement> m_zpRing;
	std::vector<CPlacement> m_zpRingLoD1;
	std::vector<CPlacement> m_zpRingLoD2;
	std::vector<CPlacement> m_zpRingLoD3;
	CPlacement m_zpLine[8];
	std::map<VModelPowerLine::DIRECTION, std::vector<CHVector>> m_vConnectorPositions;
	SHORT * GridPosition();
	VModelPowerLine::DIRECTION Direction();
	CMaterial m_zmBlack;
	CMaterial m_zmGrey;

	// new pylon modeling (10.4.2015)
	CGeoCube m_zgArm;
	CGeoCube m_zgUpperArm;
	CGeoCube m_zgFoundation;
	CGeoCube m_zgArmConnection;
	CGeoCube m_zgPole;
	CGeoCube m_zgRoof;
	CGeoCube m_zgStrut;
	CGeoSphere m_zgSphere;
	CGeoCylinder m_zgLine;
	CGeoCylinder m_zgIsolatorLoD1;
	CGeoCylinder m_zgIsolatorLoD2;
	CGeoCylinder m_zgIsolatorLoD3;
	CGeoTube m_zgRingLoD1;
	CGeoTube m_zgRingLoD2;
	CGeoCube m_zgRingLoD3;

	CPlacement m_zpFoundation;
	CPlacement m_zpArmConnection;
	CPlacement m_zpArm[4];
	CPlacement m_zpLeftArmPole[4];
	CPlacement m_zpRightArmPole[4];
	CPlacement m_zpUpperLeftArmPole[4];
	CPlacement m_zpUpperRightArmPole[4];
	CPlacement m_zpPole[4];
	CPlacement m_zpRoof[4];
	CPlacement m_zpSphere[5];
	CPlacement *m_zpStruts = nullptr;

	CTriangleList *m_zpTriangleIsolatorLoD1;
	CTriangleList *m_zpTriangleIsolatorLoD2;
	CTriangleList *m_zpTriangleIsolatorLoD3;
	CTriangleList *m_zpTriangleRingLoD1;
	CTriangleList *m_zpTriangleRingLoD2;
	CTriangleList *m_zpTriangleRingLoD3;


	SHORT m_iGridPosition[2];
	bool m_bConnectedPositions[4];

	USHORT m_iMaxConnectionsPerConnector                 = 2;
	USHORT m_iConnectorPerArm                            = 4;
	SHORT m_iArmPosition		                         = 8;
	SHORT m_iStrutsCount		                         = 0;
	PYLONTYPE m_ePylonType                               = STRAIGHT;
	VModelPowerLine::DIRECTION m_eDirection				 = DIRECTION::NORTH | DIRECTION::SOUTH;
	float m_fFieldSize                                   = 0;
	float m_fFoundationHeight                            = 0;
	float m_fFoundationWidth                             = 0;
	float m_fPoleDistance                                = 0;
	float m_fPoleThickness                               = 0;
	float m_fPylonHeight                                 = 0;
	float m_fStrutAngle                                  = 0;
	float m_fStrutHeight                                 = 0;
	float m_fStrutLength                                 = 0;
	float m_fStrutThickness                              = 0;
	float m_fArmLength                                   = 0;
	float m_fIsolatorLength				                 = 0;
	float m_fIsolatorThickness                           = 0;
	float m_fRingRadius			                         = 0;
	float m_fRingThickness		                         = 0;
	float m_fArmAngle			                         = 0;
	float m_fUpperArmLength		                         = 0;
	float m_fLowerArmPosition	                         = 0;
	float m_fUpperArmPosition	                         = 0;
	float m_fOppositeLeg		                         = 0;
};

NAMESPACE_VIEW_E
