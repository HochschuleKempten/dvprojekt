#include "VModelPowerLine.h"

NAMESPACE_VIEW_B

#define SIZEOF_ARRAY(array) (sizeof(array) / sizeof(*array))

VModelPowerLine::VModelPowerLine(void)
{
	// set number of connections to zero
	m_connections[WEST] = *new vector < VModelPowerLine * > ;
	m_connections[SOUTH] = *new vector < VModelPowerLine * > ;
	m_connections[EAST] = *new vector < VModelPowerLine * > ;
	m_connections[NORTH] = *new vector < VModelPowerLine * > ;
}

VModelPowerLine::~VModelPowerLine(void)
{
	m_connections[WEST].clear();
	m_connections[SOUTH].clear();
	m_connections[EAST].clear();
	m_connections[NORTH].clear();
	delete &m_connections[WEST];
	delete &m_connections[SOUTH];
	delete &m_connections[EAST];
	delete &m_connections[NORTH];
	m_connections.clear();
}

void VModelPowerLine::SetPosition(int x, int y) {
	m_iGridPosition[0] = x;
	m_iGridPosition[1] = y;

	// translate
	TranslateXDelta((float)x);
	TranslateZDelta((float)y);
}

void VModelPowerLine::Init(PYLONTYPE ePylonType, DIRECTION eDirection, float fFoundationWidth, float fPylonHeight)
{
	m_zmGrey.MakeTextureDiffuse("textures\\grey_image.jpg");
	m_zmBlack.MakeTextureDiffuse("textures\\black_image.jpg");

	// set necessary attributes depending on foundationWidth and pylonHeight
	m_fFoundationWidth    = fFoundationWidth;
	m_fFoundationHeight   = fFoundationWidth * 0.1f;
	m_fPylonHeight        = fPylonHeight;
	m_fPoleDistance       = fFoundationWidth * 0.8f;
	m_fPoleThickness      = m_fPoleDistance * 0.1f;
	m_fStrutHeight        = fPylonHeight * 0.1f;
	m_fStrutLength        = sqrtf(powf(m_fPoleDistance, 2) + powf(m_fStrutHeight, 2));
	m_fStrutAngle         = asinf(m_fStrutHeight / m_fStrutLength);;
	m_fStrutThickness     = m_fPoleDistance * 0.08f;
	m_iStrutsCount        = (int)(m_fPylonHeight / m_fStrutHeight);
	m_ePylonType          = ePylonType;
	m_eDirection          = eDirection;
	m_fArmLength          = m_fPylonHeight * 0.3f;
	m_fConnectorLength    = m_fStrutHeight;
	m_fConnectorThickness = m_fConnectorLength * 0.1f;

	// init geometries (foundation, pole, strut)
	m_zgFoundation.Init(CHVector(m_fFoundationWidth, m_fFoundationHeight, m_fFoundationWidth), &m_zmGrey);
	m_zgPole.Init(CHVector(m_fPoleThickness, m_fPylonHeight, m_fPoleThickness), &m_zmBlack);
	m_zgStrut.Init(CHVector(m_fStrutLength, m_fStrutThickness, m_fStrutThickness), &m_zmBlack);
	m_zgRoof.Init(CHVector(m_fStrutThickness, m_fStrutLength, m_fStrutThickness), &m_zmBlack);
	m_zgSphere.Init(2 * m_fPoleThickness, &m_zmBlack);
	m_zgArm.Init(CHVector(m_fPoleDistance * 4, m_fStrutThickness, m_fStrutThickness), &m_zmBlack);
	m_zgConnector.Init(m_fConnectorThickness, m_fConnectorThickness, m_fConnectorLength, &m_zmBlack);

	// preparing struts (rotate)
	m_zpStruts = new CPlacement[m_iStrutsCount * 8];
	for (int i = 0; i < m_iStrutsCount * 8; i++) {
		m_zpStruts[i].AddGeo(&m_zgStrut);
	}

	// preparing spheres
	for (int i = 0; i < 5; i++)
		m_zpSphere[i].AddGeo(&m_zgSphere);

	int index1, index2;
	float iYTranslation;
	// adding struts to poles
	for (int i = 0; i < 4; i++) {
		m_zpPole[i].AddGeo(&m_zgPole);
		m_zpRoof[i].AddGeo(&m_zgRoof);

		//// adding struts
		for (int j = 0; j < m_iStrutsCount; j++) {
			index1 = (i * m_iStrutsCount * 2) + j;
			index2 = index1 + m_iStrutsCount;
			iYTranslation = j * m_fStrutHeight * 2 - m_fPylonHeight + m_fStrutHeight;

			m_zpPole[i].AddPlacement(&m_zpStruts[index1]);
			m_zpPole[i].AddPlacement(&m_zpStruts[index2]);

			m_zpStruts[index1].RotateZDelta(-m_fStrutAngle);
			m_zpStruts[index2].RotateZDelta(m_fStrutAngle);

			m_zpStruts[index1].TranslateDelta(m_fPoleDistance, iYTranslation, 0);
			m_zpStruts[index2].TranslateDelta(m_fPoleDistance, iYTranslation, 0);
		}

		// adding roof
		m_zpRoof[i].RotateZDelta(-asinf((m_fPoleDistance + m_fPoleThickness) / (2 * (m_fStrutHeight - m_fStrutThickness))));
		m_zpRoof[i].RotateYDelta(CHelper::AngleToRad(45));
		m_zpRoof[i].TranslateDelta(m_fPoleDistance * 0.5f, m_fPylonHeight + m_fStrutHeight * 1.1f, -4 * m_fPoleThickness);
		m_zpPole[i].AddPlacement(&m_zpRoof[i]);
		m_zpSphere[i].TranslateYDelta(m_fPylonHeight);
		m_zpPole[i].AddPlacement(&m_zpSphere[i]);

		// adding arms
		m_zpArm[i].AddGeo(&m_zgArm);
		m_zpArm[i].TranslateDelta(-4 * m_fPoleDistance - m_fPoleDistance, 2 * m_iArmPosition * m_fStrutHeight + m_fStrutHeight + m_fStrutHeight, -m_fPoleDistance);
		m_zpArm[i].RotateYDelta(i * HALFPI);
		m_zpFoundation.AddPlacement(&m_zpArm[i]);

		// adding connectors for arms
		CTriangleList *triangles = m_zgConnector.CopyToTriangleList();
		triangles->Subdivide(m_fConnectorLength * 0.1f);
		triangles->WaveY(0.5f, 0.01f, 0);
		m_zpConnector[i].AddGeo(triangles);
		m_zpConnector[i].Translate(-m_fArmLength, -m_fConnectorLength, 0);
		m_zpArm[i].AddPlacement(&m_zpConnector[i]);

		// rotate modeled pole and add it to foundation
		m_zpPole[i].RotateYDelta(i * HALFPI);
		m_zpFoundation.AddPlacement(&m_zpPole[i]);
	}


	this->InitArm();


	// finally move the 4 poles into place
	m_zpPole[0].TranslateDelta(-m_fPoleDistance, m_fPylonHeight, m_fPoleDistance);
	m_zpPole[1].TranslateDelta(m_fPoleDistance, m_fPylonHeight, m_fPoleDistance);
	m_zpPole[2].TranslateDelta(m_fPoleDistance, m_fPylonHeight, -m_fPoleDistance);
	m_zpPole[3].TranslateDelta(-m_fPoleDistance, m_fPylonHeight, -m_fPoleDistance);

	m_zpFoundation.AddGeo(&m_zgFoundation);
	//m_zpFoundation.RotateY(m_eDirection * HALFPI);
	this->AddPlacement(&m_zpFoundation);
}


void VModelPowerLine::InitArm() {
	for (int i = 0; i < 4; i++) {
		switch (m_ePylonType) {
		case STRAIGHT:
			if (m_eDirection == NORTH || m_eDirection == SOUTH)
			{
				m_zpArm[0].SwitchOff();
				m_zpArm[1].SwitchOn();
				m_zpArm[2].SwitchOff();
				m_zpArm[3].SwitchOn();
			}
			else if (m_eDirection == WEST || m_eDirection == EAST)
			{
				m_zpArm[0].SwitchOn();
				m_zpArm[1].SwitchOff();
				m_zpArm[2].SwitchOn();
				m_zpArm[3].SwitchOff();
			}
			break;
		case CROSS:
			//m_zpArm[0].TranslateYDelta(m_fStrutHeight  * m_iArmPosition);
			//m_zpArm[2].TranslateYDelta(m_fStrutHeight * m_iArmPosition);
			m_zpArm[0].SwitchOn();
			m_zpArm[1].SwitchOn();
			m_zpArm[2].SwitchOn();
			m_zpArm[3].SwitchOn();

			break;
		case ANGLE:
			switch (m_eDirection)
			{
			case VModelPowerLine::WEST:
				m_zpArm[0].SwitchOn();
				m_zpArm[1].SwitchOn();
				m_zpArm[2].SwitchOff();
				m_zpArm[3].SwitchOff();
				break;
			case VModelPowerLine::SOUTH:
				m_zpArm[0].SwitchOff();
				m_zpArm[1].SwitchOn();
				m_zpArm[2].SwitchOn();
				m_zpArm[3].SwitchOff();
				break;
			case VModelPowerLine::EAST:
				m_zpArm[0].SwitchOff();
				m_zpArm[1].SwitchOff();
				m_zpArm[2].SwitchOn();
				m_zpArm[3].SwitchOn();
				break;
			case VModelPowerLine::NORTH:
				m_zpArm[0].SwitchOn();
				m_zpArm[1].SwitchOff();
				m_zpArm[2].SwitchOff();
				m_zpArm[3].SwitchOn();
				break;
			default:
				break;
			}
			break;
		}
	}
}

VModelPowerLine::DIRECTION VModelPowerLine::Direction() {
	return m_eDirection;
}

SHORT * VModelPowerLine::GridPosition() {
	return m_iGridPosition;
}

//void VModelPowerLine::placeFoundation()
//{
//	//create foundation
//	m_zgFoundation.Init(m_zvFoundation1, &m_zmGrey);
//	m_zpFoundation.Translate(m_zvFoundation2);
//	m_zpFoundation.AddGeo(&m_zgFoundation);
//}
//
//void VModelPowerLine::placeBasis()
//{
//	//right hand bottom corner
//	m_zgPole1.Init(m_zgvPoles, &m_zmBlack);
//	m_zpPole1.Translate(m_zpvPole1);
//
//	//left hand bottom corner
//	m_zgPole2.Init(m_zgvPoles, &m_zmBlack);
//	m_zpPole2.Translate(m_zpvPole2);
//
//	//right hand upper corner
//	m_zgPole3.Init(m_zgvPoles, &m_zmBlack);
//	m_zpPole3.Translate(m_zpvPole3);
//
//	//left hand upper corner
//	m_zgPole4.Init(m_zgvPoles, &m_zmBlack);
//	m_zpPole4.Translate(m_zpvPole4);
//
//	m_zpPole1.AddGeo(&m_zgPole1);
//	m_zpPole2.AddGeo(&m_zgPole2);
//	m_zpPole3.AddGeo(&m_zgPole3);
//	m_zpPole4.AddGeo(&m_zgPole4);
//
//	float rotate = m_Helper.AngleToRad(50.0f);
//
//	for (int i = 0; i < SIZEOF_ARRAY(m_zpBasisPoles); i += 2)
//	{
//		m_zgBasisPoles[i].Init(m_zgvBasisPoles, &m_zmBlack);
//		m_zpBasisPoles[i].RotateZDelta(rotate);
//		m_zgBasisPoles[i + 1].Init(m_zgvBasisPoles, &m_zmBlack);
//		m_zpBasisPoles[i + 1].RotateZDelta(-rotate);
//
//		switch (i)
//		{
//		case 0:
//			m_zpBasisPoles[i].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.25f);
//			m_zpBasisPoles[i + 1].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.25f);
//			break;
//		case 2:
//			m_zpBasisPoles[i].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.325f + 0.325f);
//			m_zpBasisPoles[i + 1].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.325f + 0.325f);
//			break;
//		case 4:
//			m_zpBasisPoles[i].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.35f + 0.35f + 0.35f);
//			m_zpBasisPoles[i + 1].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.35f + 0.35f + 0.35f);
//			break;
//		case 6:
//			m_zpBasisPoles[i].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.365f + 0.365f + 0.365f + 0.365f);
//			m_zpBasisPoles[i + 1].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.365f + 0.365f + 0.365f + 0.365f);
//			break;
//		case 8:
//			m_zpBasisPoles[i].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.375f + 0.375f + 0.375f + 0.375f + 0.375f);
//			m_zpBasisPoles[i + 1].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.375f + 0.375f + 0.375f + 0.375f + 0.375f);
//			break;
//		}
//	}
//
//	//place front/back/right/left poles and add them to basis placement
//	for (int i = 0; i < SIZEOF_ARRAY(m_zpBasisPoles); i++)
//	{
//		m_zpBasisPoles[i].AddGeo(&m_zgBasisPoles[i]);
//
//		m_zpFrontPoles.AddPlacement(&m_zpBasisPoles[i]);
//		m_zpBackPoles.AddPlacement(&m_zpBasisPoles[i]);
//		m_zpRightPoles.AddPlacement(&m_zpBasisPoles[i]);
//		m_zpLeftPoles.AddPlacement(&m_zpBasisPoles[i]);
//	}
//
//	m_zpFrontPoles.TranslateDelta(CHVector(m_zvFoundation2.GetX(), m_zvFoundation2.GetY(), m_zpvPole2.GetZ()));
//
//	m_zpBackPoles.TranslateDelta(CHVector(m_zvFoundation2.GetX(), m_zvFoundation2.GetY(), m_zpvPole4.GetZ()));
//
//	m_zpRightPoles.RotateYDelta(m_Helper.AngleToRad(90.0f));
//	m_zpRightPoles.TranslateDelta(CHVector(m_zpvPole4.GetX(), m_zvFoundation2.GetY(), m_zvFoundation2.GetZ()));
//
//	m_zpLeftPoles.RotateYDelta(m_Helper.AngleToRad(90.0f));
//	m_zpLeftPoles.TranslateDelta(CHVector(m_zpvPole3.GetX(), m_zvFoundation2.GetY(), m_zvFoundation2.GetZ()));
//
//	//place base poles
//	m_zpBasis.AddPlacement(&m_zpPole1);
//	m_zpBasis.AddPlacement(&m_zpPole2);
//	m_zpBasis.AddPlacement(&m_zpPole3);
//	m_zpBasis.AddPlacement(&m_zpPole4);
//
//	m_zpBasis.AddPlacement(&m_zpFrontPoles);
//	m_zpBasis.AddPlacement(&m_zpBackPoles);
//	m_zpBasis.AddPlacement(&m_zpRightPoles);
//	m_zpBasis.AddPlacement(&m_zpLeftPoles);
//}
//
//void VModelPowerLine::placeHead()
//{
//	//upper front
//	m_zgUpperPole1.Init(m_zgvUpperPole1, &m_zmBlack);
//	m_zpUpperPole1.Translate(m_zpvUpperPole1);
//
//	//upper right
//	m_zgUpperPole2.Init(m_zgvUpperPole2, &m_zmBlack);
//	m_zpUpperPole2.Translate(m_zpvUpperPole2);
//
//	//upper back
//	m_zgUpperPole3.Init(m_zgvUpperPole1, &m_zmBlack);
//	m_zpUpperPole3.Translate(m_zpvUpperPole3);
//
//	//upper left
//	m_zgUpperPole4.Init(m_zgvUpperPole2, &m_zmBlack);
//	m_zpUpperPole4.Translate(m_zpvUpperPole4);
//
//	m_zgRoofPole1.Init(CHVector(0.005f, 0.23f, 0.005f), &m_zmBlack);
//	m_zpRoofPole1.RotateXDelta(m_Helper.AngleToRad(-45.0f));
//	m_zpRoofPole1.RotateYDelta(m_Helper.AngleToRad(45.0f));
//	m_zpRoofPole1.TranslateDelta(CHVector(m_zvFoundation2.GetX() + 0.115f, m_zgvPoles.GetY() * 2.0f + 0.165f, m_zvFoundation2.GetZ() + 0.1175f));
//
//	m_zgRoofPole2.Init(CHVector(0.005f, 0.23f, 0.005f), &m_zmBlack);
//	m_zpRoofPole2.RotateXDelta(m_Helper.AngleToRad(-135.0f));
//	m_zpRoofPole2.RotateYDelta(m_Helper.AngleToRad(135.0f));
//	m_zpRoofPole2.TranslateDelta(CHVector(m_zvFoundation2.GetX() - 0.115f, m_zgvPoles.GetY() * 2.0f + 0.165f, m_zvFoundation2.GetZ() + 0.1175f));
//
//	m_zgRoofPole3.Init(CHVector(0.005f, 0.23f, 0.005f), &m_zmBlack);
//	m_zpRoofPole3.RotateXDelta(m_Helper.AngleToRad(-225.0f));
//	m_zpRoofPole3.RotateYDelta(m_Helper.AngleToRad(225.0f));
//	m_zpRoofPole3.TranslateDelta(CHVector(m_zvFoundation2.GetX() - 0.115f, m_zgvPoles.GetY() * 2.0f + 0.165f, m_zvFoundation2.GetZ() - 0.1175f));
//
//	m_zgRoofPole4.Init(CHVector(0.005f, 0.23f, 0.005f), &m_zmBlack);
//	m_zpRoofPole4.RotateXDelta(m_Helper.AngleToRad(-315.0f));
//	m_zpRoofPole4.RotateYDelta(m_Helper.AngleToRad(315.0f));
//	m_zpRoofPole4.TranslateDelta(CHVector(m_zvFoundation2.GetX() + 0.115f, m_zgvPoles.GetY() * 2.0f + 0.165f, m_zvFoundation2.GetZ() - 0.1175f));
//
//	m_zpUpperPole1.AddGeo(&m_zgUpperPole1);
//	m_zpUpperPole2.AddGeo(&m_zgUpperPole2);
//	m_zpUpperPole3.AddGeo(&m_zgUpperPole3);
//	m_zpUpperPole4.AddGeo(&m_zgUpperPole4);
//
//	m_zpRoofPole1.AddGeo(&m_zgRoofPole1);
//	m_zpRoofPole2.AddGeo(&m_zgRoofPole2);
//	m_zpRoofPole3.AddGeo(&m_zgRoofPole3);
//	m_zpRoofPole4.AddGeo(&m_zgRoofPole4);
//
//	//place upper poles
//	m_zpHead.AddPlacement(&m_zpUpperPole1);
//	m_zpHead.AddPlacement(&m_zpUpperPole2);
//	m_zpHead.AddPlacement(&m_zpUpperPole3);
//	m_zpHead.AddPlacement(&m_zpUpperPole4);
//	m_zpHead.AddPlacement(&m_zpRoofPole1);
//	m_zpHead.AddPlacement(&m_zpRoofPole2);
//	m_zpHead.AddPlacement(&m_zpRoofPole3);
//	m_zpHead.AddPlacement(&m_zpRoofPole4);
//}
//
//void VModelPowerLine::placeConduit(void)
//{
//	m_zgRightConduit1.Init(CHVector(0.49f, 0.005f, 0.005f), &m_zmBlack);
//	m_zgRightConduit2.Init(CHVector(0.49f, 0.005f, 0.005f), &m_zmBlack);
//	m_zgRightConduit3.Init(CHVector(0.55f, 0.005f, 0.005f), &m_zmGrey);
//	m_zgRightConduit4.Init(CHVector(0.55f, 0.005f, 0.005f), &m_zmGrey);
//
//	m_zpRightConduit1.RotateYDelta(m_Helper.AngleToRad(14.5f));
//	m_zpRightConduit1.TranslateDelta(CHVector(m_zpvPole1.GetX() + 0.465f, m_zvFoundation2.GetY() * 2 + 0.375f + 0.375f + 0.375f + 0.375f + 0.17f, m_zpvPole1.GetZ() - 0.12f));
//
//	m_zpRightConduit2.RotateYDelta(m_Helper.AngleToRad(-14.5f));
//	m_zpRightConduit2.TranslateDelta(CHVector(m_zpvPole1.GetX() + 0.465f, m_zvFoundation2.GetY() * 2 + 0.375f + 0.375f + 0.375f + 0.375f + 0.17f, m_zpvPole3.GetZ() + 0.12f));
//
//	m_zpRightConduit3.RotateYDelta(m_Helper.AngleToRad(15.0f));
//	m_zpRightConduit3.RotateXDelta(m_Helper.AngleToRad(-65.0f));
//	m_zpRightConduit3.TranslateDelta(CHVector(m_zpvPole1.GetX() + 0.55f, m_zvFoundation2.GetY() * 2 + 0.375f + 0.375f + 0.375f + 0.375f + 0.375f + 0.095f, m_zpvPole1.GetZ() - 0.1f));
//
//	m_zpRightConduit4.RotateYDelta(m_Helper.AngleToRad(-15.0f));
//	m_zpRightConduit4.RotateXDelta(m_Helper.AngleToRad(-65.0f));
//	m_zpRightConduit4.TranslateDelta(CHVector(m_zpvPole1.GetX() + 0.475f, m_zvFoundation2.GetY() * 2 + 0.375f + 0.375f + 0.375f + 0.375f + 0.375f, m_zpvPole3.GetZ() + 0.1f));
//
//	m_zpRightConduit1.AddGeo(&m_zgRightConduit1);
//	m_zpRightConduit2.AddGeo(&m_zgRightConduit2);
//	m_zpRightConduit3.AddGeo(&m_zgRightConduit3);
//	m_zpRightConduit4.AddGeo(&m_zgRightConduit4);
//
//	m_zpRightConduit.AddPlacement(&m_zpRightConduit1);
//	m_zpRightConduit.AddPlacement(&m_zpRightConduit2);
//	m_zpRightConduit.AddPlacement(&m_zpRightConduit3);
//	m_zpRightConduit.AddPlacement(&m_zpRightConduit4);
//}

float VModelPowerLine::getWidth() {
	return m_fFoundationWidth;
}


float VModelPowerLine::getHeight() {
	return m_fPylonHeight;
}

CHVector * VModelPowerLine::ConnectorPositions() {
	for (int i = 0; i < 4; i++){
		m_vConnectorPositions[i] = this->GetTranslation() + m_zpFoundation.GetTranslation() + m_zpArm[i].GetTranslation() + m_zpConnector[i].GetTranslation();
	}
	return m_vConnectorPositions;
}

CPlacement * VModelPowerLine::Connectors() {
	return m_zpConnector;
}

bool * VModelPowerLine::ConnectedPositions() {
	return m_bConnectedPositions;
}

bool VModelPowerLine::ConnectTo(VModelPowerLine *pPylon) {
	// get possible connectors pairs based on pylon type, direction and position
	// check whether pairs are free (1 connector has max. capacity of 2 connections - 1 in and 1 out)
	vector<DIRECTION> vec_aArmPairs = DetermineArm(pPylon);
	if (vec_aArmPairs.size() < 1 || !AddConnection(pPylon, vec_aArmPairs[0]))
		return false;

	// calculate distance between 2 power lines
	CHVector * vpConnectorPositions = pPylon->ConnectorPositions();
	CHVector * m_vConnectorPositions = this->ConnectorPositions();

	CHVector vTranslation1 = m_vConnectorPositions[vec_aArmPairs[0]];
	CHVector vTranslation2 = vpConnectorPositions[vec_aArmPairs[0]];

	//float distance = vTranslation1.Dist(vTranslation2);
	float distance = this->GetTranslation().Dist(pPylon->GetTranslation());
	float angle    = vTranslation1.Angle(vTranslation2);

	// generate line
	CGeoCylinder * gLine = new CGeoCylinder;
	gLine->Init(m_fConnectorThickness * 0.5f, m_fConnectorThickness * 0.5f, distance, &m_zmGrey);
	m_zpLine[vec_aArmPairs[0]].AddGeo(gLine);


	// rotate in right direction
	if (vec_aArmPairs[0] == SOUTH && (m_iGridPosition[0] < pPylon->GridPosition()[0])) {
		m_zpLine[vec_aArmPairs[0]].RotateX(HALFPI);
	}
	else if (vec_aArmPairs[0] == SOUTH && (m_iGridPosition[0] > pPylon->GridPosition()[0])) {
		m_zpLine[vec_aArmPairs[0]].RotateX(HALFPI);
	}
	else if (vec_aArmPairs[0] == NORTH && (m_iGridPosition[0] > pPylon->GridPosition()[0])) {
		m_zpLine[vec_aArmPairs[0]].RotateX(HALFPI);
	}
	else if (vec_aArmPairs[0] == NORTH && (m_iGridPosition[0] < pPylon->GridPosition()[0])) {
		m_zpLine[vec_aArmPairs[0]].RotateX(-HALFPI);
	}
	else if (vec_aArmPairs[0] == WEST && (m_iGridPosition[1] < pPylon->GridPosition()[1])) {
		m_zpLine[vec_aArmPairs[0]].RotateX(HALFPI);
	}
	else if (vec_aArmPairs[0] == WEST && (m_iGridPosition[1] > pPylon->GridPosition()[1])) {
		m_zpLine[vec_aArmPairs[0]].RotateX(-HALFPI);
	}
	else if (vec_aArmPairs[0] == EAST && (m_iGridPosition[1] > pPylon->GridPosition()[1])) {
		m_zpLine[vec_aArmPairs[0]].RotateX(HALFPI);
	}
	else if (vec_aArmPairs[0] == EAST && (m_iGridPosition[1] < pPylon->GridPosition()[1])) {
		m_zpLine[vec_aArmPairs[0]].RotateX(-HALFPI);
	}

	// move the arms up and down if necessary (so cables won't cross)
	m_zpConnector[vec_aArmPairs[0]].AddPlacement(&m_zpLine[vec_aArmPairs[0]]);

	return true;
}

map<VModelPowerLine::DIRECTION, vector<VModelPowerLine *>> * VModelPowerLine::Connections() {
	return &m_connections;
}

bool VModelPowerLine::AddConnection(VModelPowerLine * pPylon, DIRECTION eConnectorPosition) {
	// see whether connector capacity is available
	if ((m_connections[eConnectorPosition].size() >= m_iMaxConnectionsPerConnector) || ((*pPylon->Connections())[eConnectorPosition].size() >= m_iMaxConnectionsPerConnector)) {
		return false;
	}

	m_connections[eConnectorPosition].push_back(pPylon);
	(*pPylon->Connections())[eConnectorPosition].push_back(this);

	return true;
}

VModelPowerLine::PYLONTYPE VModelPowerLine::PylonType() {
	return m_ePylonType;
}

vector<VModelPowerLine::DIRECTION> VModelPowerLine::DetermineArm(VModelPowerLine *pPylon) {
	vector<DIRECTION> vecaArmPairs;
	DIRECTION eDirection   = pPylon->Direction();
	PYLONTYPE ePylonType   = pPylon->PylonType();
	SHORT * ipGridPosition = pPylon->GridPosition();

	switch (m_ePylonType)
	{
	case STRAIGHT:
		switch (ePylonType)
		{
		case VModelPowerLine::STRAIGHT:
			if ((m_eDirection == NORTH || m_eDirection == SOUTH) && (eDirection == NORTH || eDirection == SOUTH)) {
				if ((m_iGridPosition[0] != ipGridPosition[0]) && (m_iGridPosition[1] == ipGridPosition[1])) {
					vecaArmPairs.push_back(SOUTH);
					vecaArmPairs.push_back(NORTH);
				}
			}
			else if ((m_eDirection == WEST || m_eDirection == EAST) && eDirection == WEST || eDirection == EAST) {
				if ((m_iGridPosition[0] == ipGridPosition[0]) && (m_iGridPosition[1] != ipGridPosition[1])) {
					vecaArmPairs.push_back(WEST);
					vecaArmPairs.push_back(EAST);
				}
			}
			break;
		case VModelPowerLine::CROSS:
			if ((m_eDirection == NORTH || m_eDirection == SOUTH)) {
				if ((m_iGridPosition[0] != ipGridPosition[0]) && (m_iGridPosition[1] == ipGridPosition[1])) {
					vecaArmPairs.push_back(SOUTH);
					vecaArmPairs.push_back(NORTH);
				}
			}
			else {
				if ((m_iGridPosition[0] == ipGridPosition[0]) && (m_iGridPosition[1] != ipGridPosition[1])) {
					vecaArmPairs.push_back(WEST);
					vecaArmPairs.push_back(EAST);
				}
			}
			break;
		case VModelPowerLine::ANGLE:
			if ((m_eDirection == NORTH || m_eDirection == SOUTH)) {
				if ((m_iGridPosition[0] != ipGridPosition[0]) && (m_iGridPosition[1] == ipGridPosition[1])) {
					if (eDirection == WEST || eDirection == SOUTH) {
						vecaArmPairs.push_back(SOUTH);
					}
					else {
						vecaArmPairs.push_back(NORTH);
					}
				}
			}
			else {
				if ((m_iGridPosition[0] == ipGridPosition[0]) && (m_iGridPosition[1] != ipGridPosition[1])) {
					if (eDirection == WEST || eDirection == NORTH) {
						vecaArmPairs.push_back(WEST);
					}
					else {
						vecaArmPairs.push_back(EAST);
					}
				}
			}
			break;
		default:
			break;
		}
		break;
	case CROSS:
		switch (ePylonType)
		{
		case VModelPowerLine::STRAIGHT:
			if ((m_iGridPosition[0] == ipGridPosition[0]) && (m_iGridPosition[1] != ipGridPosition[1])) {
				if (eDirection == WEST || eDirection == EAST) {
					vecaArmPairs.push_back(WEST);
					vecaArmPairs.push_back(EAST);
				}
			}
			else if ((m_iGridPosition[0] != ipGridPosition[0]) && (m_iGridPosition[1] == ipGridPosition[1])) {
				vecaArmPairs.push_back(NORTH);
				vecaArmPairs.push_back(SOUTH);
			}
			break;
		case VModelPowerLine::CROSS:
			if ((m_iGridPosition[0] == ipGridPosition[0]) && (m_iGridPosition[1] != ipGridPosition[1])) {
				vecaArmPairs.push_back(WEST);
				vecaArmPairs.push_back(EAST);
			}
			else {
				vecaArmPairs.push_back(NORTH);
				vecaArmPairs.push_back(SOUTH);
			}
		case VModelPowerLine::ANGLE:
			if ((m_iGridPosition[0] != ipGridPosition[0]) && (m_iGridPosition[1] == ipGridPosition[1])) {
				if (eDirection == WEST || eDirection == SOUTH) {
					vecaArmPairs.push_back(SOUTH);
				}
				else {
					vecaArmPairs.push_back(NORTH);
				}
			}
			else if ((m_iGridPosition[0] == ipGridPosition[0]) && (m_iGridPosition[1] != ipGridPosition[1])) {
				if (eDirection == NORTH || eDirection == WEST) {
					vecaArmPairs.push_back(WEST);
				}
				else {
					vecaArmPairs.push_back(EAST);
				}
			}
			break;
		default:
			break;
		}
		break;
	case ANGLE:
		switch (ePylonType)
		{
		case VModelPowerLine::STRAIGHT:
			if ((m_iGridPosition[0] != ipGridPosition[0]) && (m_iGridPosition[1] == ipGridPosition[1])) {
				if ((m_eDirection == WEST || m_eDirection == EAST) && (eDirection == NORTH || eDirection == SOUTH))
					vecaArmPairs.push_back(SOUTH);
				else
					vecaArmPairs.push_back(NORTH);
			}
			else if ((m_iGridPosition[0] == ipGridPosition[0]) && (m_iGridPosition[1] != ipGridPosition[1])) {
				if ((m_eDirection == WEST || m_eDirection == NORTH) && (eDirection == WEST || eDirection == EAST))
					vecaArmPairs.push_back(WEST);
				else
					vecaArmPairs.push_back(EAST);
			}
			break;
		case VModelPowerLine::CROSS:
			if ((m_iGridPosition[0] != ipGridPosition[0]) && (m_iGridPosition[1] == ipGridPosition[1])) {
				if (m_eDirection == WEST || m_eDirection == SOUTH)
					vecaArmPairs.push_back(SOUTH);
				else
					vecaArmPairs.push_back(NORTH);
			}
			else if ((m_iGridPosition[0] == ipGridPosition[0]) && (m_iGridPosition[1] != ipGridPosition[1])) {
				if (m_eDirection == WEST || m_eDirection == NORTH)
					vecaArmPairs.push_back(WEST);
				else
					vecaArmPairs.push_back(EAST);
			}
			break;
		case VModelPowerLine::ANGLE:
			if ((m_iGridPosition[0] != ipGridPosition[0]) && (m_iGridPosition[1] == ipGridPosition[1])) {
				if ((m_eDirection == WEST || m_eDirection == SOUTH) && (eDirection == WEST || eDirection == SOUTH))
					vecaArmPairs.push_back(SOUTH);
				else
					vecaArmPairs.push_back(NORTH);
			}
			else if ((m_iGridPosition[0] == ipGridPosition[0]) && (m_iGridPosition[1] != ipGridPosition[1])) {
				if ((m_eDirection == WEST || m_eDirection == NORTH) && (eDirection == WEST || eDirection == NORTH))
					vecaArmPairs.push_back(WEST);
				else
					vecaArmPairs.push_back(EAST);
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return vecaArmPairs;
}

// TODO: implement disconnection from given active connection to a pylon
bool VModelPowerLine::DisconnectFrom(VModelPowerLine * pPylon) {
	return false;
}

// TODO: implement disconnection function for all active connections
bool VModelPowerLine::DisconnectAll() {
	return false;
}

NAMESPACE_VIEW_E