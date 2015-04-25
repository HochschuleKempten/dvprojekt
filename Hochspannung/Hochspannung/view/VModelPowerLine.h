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
	CHVector * ConnectorPositions();
	CPlacement * Connectors();

	void Init(PYLONTYPE ePylonType = STRAIGHT, DIRECTION eDirection = NORTH, float fFoundationWidth = 0.1f, float fPylonHeight = 1.0f);
	void SetPosition(int x, int y);
	bool ConnectTo(VModelPowerLine *pPylon);
	bool AddConnection(VModelPowerLine * pPylon, DIRECTION eConnectorPosition);
	bool DisconnectFrom(VModelPowerLine * pPylon);
	bool DisconnectAll();


	bool ConnectedWest() {
		return bConnectedWest;
	};

	bool * ConnectedPositions();

	bool ConnectedSouth() {
		return bConnectedSouth;
	};
	bool ConnectedEast() {
		return bConnectedEast;
	};
	bool ConnectedNorth() {
		return bConnectedNorth;
	};

	virtual float getHeight() override; // including foundation
	virtual float getWidth() override;  // width of the foundation

private:
	void InitArm();
	vector<DIRECTION> DetermineArm(VModelPowerLine *pPylon);
	map<DIRECTION, vector<VModelPowerLine *> > m_connections;

	SHORT * GridPosition();
	DIRECTION Direction();

	CMaterial m_zmBlack;
	CMaterial m_zmGrey;

	// new pylon modeling (10.4.2015)
	CGeoCube m_zgArm;
	CGeoCube m_zgFoundation;
	CGeoCube m_zgPole;
	CGeoCube m_zgRoof;
	CGeoCube m_zgStrut;
	CGeoSphere m_zgSphere;
	CGeoCylinder m_zgConnector;
	CGeoTube m_zgRing;

	CPlacement m_zpFoundation;
	CPlacement m_zpArm[4];
	CPlacement m_zpPole[4];
	CPlacement m_zpRoof[4];
	//TODO (Trasse) consider using normal variable types instead of pointers here (less heap allocations)
	//You may be able to use std::vector<CPlacement> as well
	std::vector<CPlacement*> m_zpConnector;
	std::vector<CPlacement*> m_zpRing;
	CPlacement m_zpLine[8];
	CPlacement m_zpSphere[5];
	CPlacement * m_zpStruts = nullptr;

	CTriangleList *m_zpTriangleConnector;
	CTriangleList *m_zpTriangleRing;

	CHVector m_vConnectorPositions[4];
	SHORT m_iGridPosition[2];
	USHORT m_iMaxConnectionsPerConnector = 2;
	bool m_bConnectedPositions[4];

	SHORT m_iArmPosition       = 9;
	SHORT m_iStrutsCount       = 0;
	PYLONTYPE m_ePylonType      = STRAIGHT;
	DIRECTION m_eDirection      = NORTH;
	float m_fFoundationHeight   = 0;
	float m_fFoundationWidth    = 0;
	float m_fPoleDistance       = 0;
	float m_fPoleThickness      = 0;
	float m_fPylonHeight        = 0;
	float m_fStrutAngle         = 0;
	float m_fStrutHeight        = 0;
	float m_fStrutLength        = 0;
	float m_fStrutThickness     = 0;
	float m_fArmLength          = 0;
	float m_fConnectorLength    = 0;
	float m_fConnectorThickness = 0;
	float m_fRingRadius = 0;
	float m_fRingThickness = 0;
	bool bConnectedWest         = false;
	bool bConnectedSouth        = false;
	bool bConnectedEast         = false;
	bool bConnectedNorth        = false;
};


NAMESPACE_VIEW_E
