#include "IViewModel.h"
#include "VGeneral.h"

NAMESPACE_VIEW_B


class VModelPowerLine : public IViewModel
{
public:
	enum PYLONTYPE {
		STRAIGHT, CROSS, ANGLE
	};
	enum DIRECTION {
		WEST, SOUTH, EAST, NORTH
	};

public:
	VModelPowerLine(void);
	virtual ~VModelPowerLine(void) override;
	map<DIRECTION, vector<VModelPowerLine *>> * Connections();
	VModelPowerLine::PYLONTYPE PylonType();
	vector<CHVector> * ConnectorPositions(VModelPowerLine::DIRECTION armPosition);

	void Init(PYLONTYPE ePylonType = STRAIGHT, DIRECTION eDirection = NORTH, float fFoundationWidth = 0.1f, float fPylonHeight = 1.0f);
	void SetPosition(int x, int y);
	bool ConnectTo(VModelPowerLine *pPylon);
	USHORT AddConnection(VModelPowerLine * pPylon, DIRECTION eConnectorPosition);
	bool DisconnectFrom(VModelPowerLine * pPylon);
	bool DisconnectAll();

	virtual float getHeight() override; // including foundation
	virtual float getWidth() override;  // width of the foundation

private:
	void InitArm();
	std::vector<DIRECTION> DetermineArm(VModelPowerLine *pPylon);
	//TODO (Pylon) consider using normal variable types instead of pointers here (less heap allocations)
	//You may be able to use std::vector<CPlacement> as well
	std::vector <CPlacement> m_zpConnector;
	std::vector<CPlacement> m_zpRing;
	std::map<DIRECTION, std::vector<CPlacement>> m_zpLine;
	std::map<DIRECTION, std::vector<VModelPowerLine *> > m_connections;
	std::map<DIRECTION, std::vector<CHVector>> m_vConnectorPositions;
	//std::map<DIRECTION, std::vector<CPlacement*>> m_zpLine;
	SHORT * GridPosition();
	DIRECTION Direction();

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
	CGeoCylinder m_zgConnector;
	CGeoTube m_zgRing;

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
	CPlacement * m_zpStruts = nullptr;

	CTriangleList *m_zpTriangleConnector;
	CTriangleList *m_zpTriangleRing;

	SHORT m_iGridPosition[2];
	bool m_bConnectedPositions[4];

	USHORT m_iMaxConnectionsPerConnector = 2;
	USHORT m_iConnectorPerArm            = 4;
	SHORT m_iArmPosition		         = 9;
	SHORT m_iStrutsCount		         = 0;
	PYLONTYPE m_ePylonType               = STRAIGHT;
	DIRECTION m_eDirection               = NORTH;
	float m_fFoundationHeight            = 0;
	float m_fFoundationWidth             = 0;
	float m_fPoleDistance                = 0;
	float m_fPoleThickness               = 0;
	float m_fPylonHeight                 = 0;
	float m_fStrutAngle                  = 0;
	float m_fStrutHeight                 = 0;
	float m_fStrutLength                 = 0;
	float m_fStrutThickness              = 0;
	float m_fArmLength                   = 0;
	float m_fConnectorLength             = 0;
	float m_fConnectorThickness          = 0;
	float m_fRingRadius			         = 0;
	float m_fRingThickness		         = 0;
	float m_fArmAngle			         = 0;
	float m_fUpperArmLength		         = 0;
	float m_fLowerArmPosition	         = 0;
	float m_fUpperArmPosition	         = 0;
	float m_fOppositeLeg		         = 0;
};


NAMESPACE_VIEW_E
