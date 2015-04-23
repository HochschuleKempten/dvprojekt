#include "VModelPowerLine.h"

NAMESPACE_VIEW_B


#define SIZEOF_ARRAY(array) (sizeof(array) / sizeof(*array))

VModelPowerLine::VModelPowerLine(void)
{
	// set number of connections to zero
	//TODO (Pylon) sure this here is what you want?
	m_connections[WEST]  = *new vector < VModelPowerLine * > ;
	m_connections[SOUTH] = *new vector < VModelPowerLine * > ;
	m_connections[EAST]  = *new vector < VModelPowerLine * > ;
	m_connections[NORTH] = *new vector < VModelPowerLine * > ;
	
	m_zpLine[WEST] = * new std::vector < CPlacement > ;
	m_zpLine[SOUTH] = * new std::vector < CPlacement > ;
	m_zpLine[EAST] = * new std::vector < CPlacement > ;
	m_zpLine[NORTH] = * new std::vector < CPlacement > ;
}

VModelPowerLine::~VModelPowerLine(void)
{
	m_connections[WEST].clear();
	m_connections[SOUTH].clear();
	m_connections[EAST].clear();
	m_connections[NORTH].clear();
	//delete &m_connections[WEST];	//TODO (Trasse) fix error on closing
	//delete &m_connections[SOUTH];
	//delete &m_connections[EAST];
	//delete &m_connections[NORTH];
	m_connections.clear();

	// TODO: add clean up for lines
}

void VModelPowerLine::SetPosition(int x, int y) {
	m_iGridPosition[0] = x;
	m_iGridPosition[1] = y;

	// translate
	m_zpMain.TranslateXDelta(CASTS<float>(x));
	m_zpMain.TranslateZDelta(CASTS<float>(y));
}

void VModelPowerLine::Init(PYLONTYPE ePylonType, DIRECTION eDirection, float fFoundationWidth, float fPylonHeight)
{
	m_zmGrey.MakeTextureDiffuse("textures\\texture_concrete_diffuse.png");
	m_zmGrey.MakeTextureBump("textures\\texture_concrete_normal.png");
	m_zmGrey.MakeTextureSpecular("textures\\texture_concrete_specular.png");
	m_zmBlack.MakeTextureDiffuse("textures\\black_image.jpg");

	// set necessary attributes depending on foundationWidth and pylonHeight
	m_fFoundationWidth		= fFoundationWidth;
	m_fFoundationHeight		= fFoundationWidth * 0.1f;
	m_fPylonHeight			= fPylonHeight;
	m_fPoleDistance			= fFoundationWidth * 0.8f;
	m_fPoleThickness		= m_fPoleDistance * 0.1f;
	m_fStrutHeight			= fPylonHeight * 0.1f;
	m_fStrutLength			= sqrtf(powf(m_fPoleDistance, 2) + powf(m_fStrutHeight, 2));
	m_fStrutAngle			= asinf(m_fStrutHeight / m_fStrutLength);;
	m_fStrutThickness		= m_fPoleDistance * 0.08f;
	m_iStrutsCount          = CASTS<int>(m_fPylonHeight / m_fStrutHeight);
	m_ePylonType			= ePylonType;
	m_eDirection			= eDirection;
	
	m_fArmLength			= m_fPylonHeight * 0.3f;
	m_fLowerArmPosition		= 2 * m_iArmPosition * m_fStrutHeight;
	m_fUpperArmPosition		= m_fLowerArmPosition + m_fStrutHeight * 2.0f;
	m_fUpperArmLength		= sqrt(pow(m_fStrutHeight, 2) + pow(m_fArmLength, 2));
	m_fArmAngle				= asinf(m_fStrutHeight / m_fUpperArmLength);

	m_fConnectorLength    = m_fStrutHeight;
	m_fConnectorThickness = m_fConnectorLength * 0.1f;
	m_fRingRadius         = m_fConnectorThickness;
	m_fRingThickness      = m_fConnectorThickness / 4.0f;

	// init geometries (foundation, pole, strut)
	m_zgFoundation.Init(CHVector(m_fFoundationWidth, m_fFoundationHeight, m_fFoundationWidth), &m_zmGrey);
	m_zgPole.Init(CHVector(m_fPoleThickness, m_fPylonHeight, m_fPoleThickness), &m_zmBlack);
	m_zgStrut.Init(CHVector(m_fStrutLength, m_fStrutThickness, m_fStrutThickness), &m_zmBlack);
	m_zgRoof.Init(CHVector(m_fStrutThickness, m_fStrutLength, m_fStrutThickness), &m_zmBlack);
	m_zgSphere.Init(2 * m_fPoleThickness, &m_zmBlack);
	m_zgArm.Init(CHVector(m_fArmLength, m_fStrutThickness, m_fStrutThickness), &m_zmBlack);
	m_zgUpperArm.Init(CHVector(m_fUpperArmLength, m_fStrutThickness, m_fStrutThickness), &m_zmBlack);
	m_zgConnector.Init(m_fConnectorThickness, m_fConnectorThickness, m_fConnectorLength, &m_zmBlack);
	m_zgRing.InitArc(m_fRingThickness, m_fRingThickness, m_fRingRadius, TWOPI, &m_zmBlack);
	m_zgArmConnection.Init(CHVector(m_fStrutThickness, m_fStrutThickness, m_fPoleDistance), &m_zmBlack);

	// init ring vector
	for (int i = 0; i < 16; i++) {
		m_zpRing.push_back(*new CPlacement);
		m_zpConnector.push_back(*new CPlacement);
	}

	// preparing struts (rotate)
	m_zpStruts = new CPlacement[m_iStrutsCount * 8];
	for (int i = 0; i < m_iStrutsCount * 8; i++) {
		m_zpStruts[i].AddGeo(&m_zgStrut);
		m_zpStruts[i].FixAndFasten();
	}

	// preparing spheres
	for (int i = 0; i < 5; i++) {
		m_zpSphere[i].AddGeo(&m_zgSphere);
	}

	int index1, index2;
	float iYTranslation;
	// adding struts to poles
	for (int i = 0; i < 4; i++) {
		m_zpPole[i].AddGeo(&m_zgPole);
		m_zpPole[i].FixAndFasten();
		m_zpRoof[i].AddGeo(&m_zgRoof);
		m_zpPole[i].FixAndFasten();

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
		m_zpPole[i].FixAndFasten();

		// adding roof
		m_zpRoof[i].RotateZDelta(-asinf((m_fPoleDistance + m_fPoleThickness) / (2 * (m_fStrutHeight - m_fStrutThickness))));
		m_zpRoof[i].RotateYDelta(AngleToRad(45));
		m_zpRoof[i].TranslateDelta(m_fPoleDistance * 0.5f, m_fPylonHeight + m_fStrutHeight * 1.1f, -4 * m_fPoleThickness);
		m_zpPole[i].AddPlacement(&m_zpRoof[i]);
		m_zpSphere[i].TranslateYDelta(m_fPylonHeight);
		m_zpPole[i].AddPlacement(&m_zpSphere[i]);
		m_zpRoof[i].FixAndFasten();

		// adding bottom arm poles
		m_zpLeftArmPole[i].AddGeo(&m_zgArm);
		m_zpLeftArmPole[i].TranslateDelta(-m_fArmLength - m_fPoleDistance, m_fLowerArmPosition, -m_fPoleDistance);
		m_zpArm[i].AddPlacement(&m_zpLeftArmPole[i]);

		m_zpRightArmPole[i].AddGeo(&m_zgArm);
		m_zpRightArmPole[i].TranslateDelta(-m_fArmLength - m_fPoleDistance, m_fLowerArmPosition, m_fPoleDistance);
		m_zpArm[i].AddPlacement(&m_zpRightArmPole[i]);

		// adding arm connection
		m_zpArmConnection.AddGeo(&m_zgArmConnection);
		m_zpArmConnection.Translate(-m_fArmLength + m_fStrutThickness * 2.0f, 0, m_fPoleDistance);
		m_zpLeftArmPole[i].AddPlacement(&m_zpArmConnection);

		// adding upper arm poles
		m_zpUpperLeftArmPole[i].RotateZDelta(m_fArmAngle);
		m_zpUpperLeftArmPole[i].AddGeo(&m_zgUpperArm);
		m_zpUpperLeftArmPole[i].TranslateDelta(-m_fArmLength - m_fPoleDistance, m_fUpperArmPosition, -m_fPoleDistance);
		m_zpUpperLeftArmPole[i].TranslateYDelta(-m_fStrutHeight);
		m_zpArm[i].AddPlacement(&m_zpUpperLeftArmPole[i]); 

		m_zpUpperRightArmPole[i].RotateZDelta(m_fArmAngle);
		m_zpUpperRightArmPole[i].AddGeo(&m_zgUpperArm);
		m_zpUpperRightArmPole[i].TranslateDelta(-m_fArmLength - m_fPoleDistance, m_fUpperArmPosition, m_fPoleDistance);
		m_zpUpperRightArmPole[i].TranslateYDelta(-m_fStrutHeight);
		m_zpArm[i].AddPlacement(&m_zpUpperRightArmPole[i]);
		m_zpArm[i].FixAndFasten();

		// adding arms
		m_zpArm[i].RotateYDelta(i * HALFPI);
		m_zpFoundation.AddPlacement(&m_zpArm[i]);
		
		// adding connectors for arms
		m_zpTriangleConnector = m_zgConnector.CopyToTriangleList();
		m_zpTriangleConnector->Subdivide(m_fConnectorLength * 0.1f);
		m_zpTriangleConnector->WaveY(0.5f, 0.01f, 0);
		float dividedArm = m_fArmLength / 4.0f;
		m_zpConnector[i * 4].AddGeo(m_zpTriangleConnector);
		m_zpConnector[i * 4 + 1].AddGeo(m_zpTriangleConnector);
		m_zpConnector[i * 4 + 2].AddGeo(m_zpTriangleConnector);
		m_zpConnector[i * 4 + 3].AddGeo(m_zpTriangleConnector);

		m_zpConnector[i * 4].Translate(dividedArm * -3.0f, -m_fConnectorLength, 0);
		m_zpConnector[i * 4 + 1].Translate(dividedArm * -2.0f, -m_fConnectorLength, 0);
		m_zpConnector[i * 4 + 2].Translate(dividedArm * 3.0f, -m_fConnectorLength, 0);
		m_zpConnector[i * 4 + 3].Translate(dividedArm * 2.0f, -m_fConnectorLength, 0);

		m_zpLeftArmPole[i].AddPlacement(&m_zpConnector[i * 4]);
		m_zpLeftArmPole[i].AddPlacement(&m_zpConnector[i * 4 + 1]);
		m_zpLeftArmPole[i].AddPlacement(&m_zpConnector[i * 4 + 2]);
		m_zpLeftArmPole[i].AddPlacement(&m_zpConnector[i * 4 + 3]);
		//m_zpLeftArmPole[i].FixAndFasten();

		m_zpRightArmPole[i].AddPlacement(&m_zpConnector[i * 4]);
		m_zpRightArmPole[i].AddPlacement(&m_zpConnector[i * 4 + 1]);
		m_zpRightArmPole[i].AddPlacement(&m_zpConnector[i * 4 + 2]);
		m_zpRightArmPole[i].AddPlacement(&m_zpConnector[i * 4 + 3]);
		//m_zpRightArmPole[i].FixAndFasten();

		// add rings to connectors
		m_zpRing[i].AddGeo(&m_zgRing);
		m_zpRing[i].RotateXDelta(HALFPI);
		m_zpRing[i].TranslateDelta(0,0 -m_fRingRadius, 0);
		m_zpRing[i].SetFrustumCullingOn();	
		m_zpConnector[i * 4].AddPlacement(&m_zpRing[i]);
		m_zpConnector[i * 4 + 1].AddPlacement(&m_zpRing[i]);
		m_zpConnector[i * 4 + 2].AddPlacement(&m_zpRing[i]);
		m_zpConnector[i * 4 + 3].AddPlacement(&m_zpRing[i]);

		// rotate modeled pole and add it to foundation
		m_zpPole[i].RotateYDelta(i * HALFPI);
		m_zpPole[i].FixAndFasten();
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
	m_zpMain.AddPlacement(&m_zpFoundation);
}


void VModelPowerLine::InitArm() {
	//for (int i = 0; i < 4; i++) {
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
	//}
}

VModelPowerLine::DIRECTION VModelPowerLine::Direction() {
	return m_eDirection;
}

SHORT * VModelPowerLine::GridPosition() {
	return m_iGridPosition;
}

float VModelPowerLine::getWidth() {
	return m_fFoundationWidth;
}


float VModelPowerLine::getHeight()
{
	return m_fPylonHeight;
}


std::vector<CHVector> * VModelPowerLine::ConnectorPositions(VModelPowerLine::DIRECTION armPosition) {
	for (int i = 0; i < 4; i++) {
		m_vConnectorPositions[armPosition].push_back (m_zpMain.GetTranslation() + m_zpFoundation.GetTranslation() + m_zpArm[i].GetTranslation() + m_zpConnector[i].GetTranslation());
	}
	return &m_vConnectorPositions[armPosition];
}


bool VModelPowerLine::ConnectTo(VModelPowerLine *pPylon) {
	// get possible arm pairs based on pylon type, direction and position
	vector<DIRECTION> vec_aArmPairs = DetermineArm(pPylon);
	if (vec_aArmPairs.size() < 1)
		return false;

	// try to logically add a new connection
	SHORT connectedPosition = -1;
	SHORT iArm = 0;
	for (USHORT i = 0; i < vec_aArmPairs.size() && connectedPosition == -1; i++) {
		connectedPosition = AddConnection(pPylon, vec_aArmPairs[i]);
		iArm = i;
	}
	if (connectedPosition < 0)
		return false;

	// get all the connector positions for the available arm pair
	CHVector vTranslation1 = pPylon->ConnectorPositions(vec_aArmPairs[iArm])->at(connectedPosition);
	CHVector vTranslation2 = this->ConnectorPositions(vec_aArmPairs[iArm])->at(connectedPosition);

	// below are geometry part of the connection //
	float distance = m_zpMain.GetTranslation().Dist(pPylon->getMainPlacement()->GetTranslation());
	//float angle    = vTranslation1.Angle(vTranslation2);

	// generate line
	CGeoCylinder * gLine = new CGeoCylinder;
	gLine->Init(m_fConnectorThickness * 0.5f, m_fConnectorThickness * 0.5f, distance, &m_zmGrey);
	m_zpLine.at(vec_aArmPairs[iArm]).push_back(*new CPlacement);
	CPlacement * newLine = &m_zpLine.at(vec_aArmPairs[iArm]).back();
	newLine->AddGeo(gLine);

	// rotate in right direction
	if (vec_aArmPairs[iArm] == SOUTH && (m_iGridPosition[0] < pPylon->GridPosition()[0])) {
		newLine->RotateX(HALFPI);
	}
	else if (vec_aArmPairs[iArm] == SOUTH && (m_iGridPosition[0] > pPylon->GridPosition()[0])) {
		newLine->RotateX(HALFPI);
	}
	else if (vec_aArmPairs[iArm] == NORTH && (m_iGridPosition[0] > pPylon->GridPosition()[0])) {
		newLine->RotateX(HALFPI);
	}
	else if (vec_aArmPairs[iArm] == NORTH && (m_iGridPosition[0] < pPylon->GridPosition()[0])) {
		newLine->RotateX(-HALFPI);
	}
	else if (vec_aArmPairs[iArm] == WEST && (m_iGridPosition[1] < pPylon->GridPosition()[1])) {
		newLine->RotateX(HALFPI);
	}
	else if (vec_aArmPairs[iArm] == WEST && (m_iGridPosition[1] > pPylon->GridPosition()[1])) {
		newLine->RotateX(-HALFPI);
	}
	else if (vec_aArmPairs[iArm] == EAST && (m_iGridPosition[1] > pPylon->GridPosition()[1])) {
		newLine->RotateX(HALFPI);
	}
	else if (vec_aArmPairs[iArm] == EAST && (m_iGridPosition[1] < pPylon->GridPosition()[1])) {
		newLine->RotateX(-HALFPI);
	}

	// move the arms up and down if necessary (so cables won't cross)


	m_zpConnector[vec_aArmPairs[iArm] * 4 + connectedPosition].AddPlacement(newLine);

	return true;
}

map<VModelPowerLine::DIRECTION, vector<VModelPowerLine *>> * VModelPowerLine::Connections() {
	return &m_connections;
}

USHORT VModelPowerLine::AddConnection(VModelPowerLine * pPylon, DIRECTION eConnectorPosition) {
	// see whether connector capacity is reached
	if ((m_connections[eConnectorPosition].size() >= m_iConnectorPerArm) || ((*pPylon->Connections())[eConnectorPosition].size() >= m_iConnectorPerArm)) {
		return -1;
	}

	m_connections[eConnectorPosition].push_back(pPylon);
	(*pPylon->Connections())[eConnectorPosition].push_back(this);

	return m_connections[eConnectorPosition].size() - 1;
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
