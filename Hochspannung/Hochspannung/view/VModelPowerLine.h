#include "VGeneral.h"
#include "Helper.h"

NAMESPACE_VIEW_B

class VModelPowerLine : public CPlacement
{
public:
	enum PYLONTYPE {
		STRAIGHT, CROSS, ANGLE
	};
	enum DIRECTION {
		WEST, SOUTH, EAST, NORTH
	};
	struct armPosition
	{
		CHVector vWest;
		CHVector vSouth;
		CHVector vEast;
		CHVector vNorth;
	};

	VModelPowerLine(void);
	~VModelPowerLine(void);

	void Init(PYLONTYPE ePylonType = STRAIGHT, DIRECTION eDirection = NORTH, float fFoundationWidth = 0.1f, float fPylonHeight = 1.0f);
	bool ConnectTo(VModelPowerLine *pPylon);
	bool ConnectedWest() {
		return bConnectedWest;
	};

	bool * ConnectedPositions();
	CHVector * ConnectorPositions();
	CPlacement * Connectors();

	bool ConnectedSouth() {
		return bConnectedSouth;
	};
	bool ConnectedEast() {
		return bConnectedEast;
	};
	bool ConnectedNorth() {
		return bConnectedNorth;
	};

	float getHeight(); // including foundation
	float getWidth();  // width of the foundation

private:
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

	CPlacement m_zpFoundation;
	CPlacement m_zpArm[4];
	CPlacement m_zpPole[4];
	CPlacement m_zpRoof[4];
	CPlacement m_zpConnector[4];
	CPlacement m_zpLine[8];
	CPlacement m_zpSphere[5];
	CPlacement * m_zpStruts = NULL;

	float m_fFoundationHeight = 0;
	float m_fFoundationWidth = 0;
	float m_fPoleDistance = 0;
	float m_fPoleThickness = 0;
	float m_fPylonHeight = 0;
	float m_fStrutAngle = 0;
	float m_fStrutHeight = 0;
	float m_fStrutLength = 0;
	float m_fStrutThickness = 0;
	float m_fArmLength = 0;
	float m_fConnectorLength = 0;
	float m_fConnectorThickness = 0;
	int m_iArmPosition = 9;
	int m_iStrutsCount = 0;
	PYLONTYPE m_ePylonType = STRAIGHT;
	DIRECTION m_eDirection = NORTH;

	armPosition sArmPositions;
	CHVector m_vConnectorPositions[4];
	bool m_bConnectedPositions[4];

	bool bConnectedWest = false;
	bool bConnectedSouth = false;
	bool bConnectedEast = false;
	bool bConnectedNorth = false;

};

NAMESPACE_VIEW_E
