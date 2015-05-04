#include "IViewModel.h"
#include "VGeneral.h"
#include <bitset>

NAMESPACE_VIEW_B

class VModelPowerLine : public IViewModel
{
public:
	enum DIRECTION
	{
		NONE  = 0x0,
		NORTH = 0x8,
		EAST  = 0x4,
		SOUTH = 0x2,
		WEST  = 0x1
	};

	enum PYLONTYPE
	{
		STRAIGHT, CROSS, ANGLE
	};

	friend VModelPowerLine::DIRECTION operator|(VModelPowerLine::DIRECTION a, VModelPowerLine::DIRECTION b);
	VModelPowerLine::DIRECTION Direction();
	VModelPowerLine(void);
	VModelPowerLine(float fFieldSize);
	virtual ~VModelPowerLine(void) override;

	void Init(VModelPowerLine::DIRECTION eDirection = DIRECTION::NONE, float fPylonHeight = 1.0f);
	void SetPosition(int x, int y);
	void SetDirection(VModelPowerLine::DIRECTION eDirection);
	SHORT * GetPosition();
	virtual float getHeight() override; // including foundation
	virtual float getWidth() override;  // width of the foundation

private:
	CPlacement m_zpIsolator[16];
	CPlacement m_zpIsolatorLoD1[16];
	CPlacement m_zpIsolatorLoD2[16];
	CPlacement m_zpIsolatorLoD3[16];
	CPlacement m_zpRing[16];
	CPlacement m_zpRingLoD1[16];
	CPlacement m_zpRingLoD2[16];
	CPlacement m_zpRingLoD3[16];
	CPlacement m_zpLine[4];
	CPlacement m_zpBendLine[4];

	CGeoCube m_zgArm;
	CGeoCube m_zgUpperArm;
	CGeoCube m_zgArmConnection;
	CGeoCube m_zgPole;
	CGeoCube m_zgRoof;
	CGeoCube m_zgStrut;
	CGeoCylinder m_zgLine;
	CGeoCylinder m_zgBendLine;
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
	CPlacement m_zpStruts[80];

	CTriangleList *m_zpTriangleIsolatorLoD1;
	CTriangleList *m_zpTriangleIsolatorLoD2;
	CTriangleList *m_zpTriangleIsolatorLoD3;
	CTriangleList *m_zpTriangleRingLoD1;
	CTriangleList *m_zpTriangleRingLoD2;
	CTriangleList *m_zpTriangleRingLoD3;
	CTriangleList *m_zpTriangleBendLine;


	SHORT m_saGridPosition[2];

	SHORT m_iArmPosition		                         = 8;
	SHORT m_iStrutsCount		                         = 0;
	PYLONTYPE m_ePylonType                               = STRAIGHT;
	VModelPowerLine::DIRECTION m_eDirection				 = DIRECTION::NONE | DIRECTION::NONE;
	float m_fFieldSize                                   = 0;
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
	float m_fLineLength									 = 0;
	float m_fLineThickness								 = 0;
	float m_fBendLineLength								 = 0;
	float dividedArm									 = 0;

	CHMat cablePathPoints[20];
	CHMats cablePath;
	CGeoSweep geosweepCable;

	bool m_fCablesDone = false;
	void InitCables(float fSegmentLength1 = 0.2, float fSegmentLength2 = 2.0, int iPrecision = 10, float fCableThickness = 0.1f);
};

NAMESPACE_VIEW_E
