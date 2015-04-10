#include "Trasse.h"

NAMESPACE_VIEW_B

#define SIZEOF_ARRAY(array) (sizeof(array) / sizeof(*array))

CTrasse::CTrasse(void)
{
	m_zvFoundation1.InitPoint(0.25f, 0.05f, 0.25f);		
	m_zvFoundation2.InitPoint(0, 0, 0);
	
	//initialize base pole vectors
	m_zgvPoles.InitPoint(0.005f, 1.0435f, 0.005f);
	m_zpvPole1.InitPoint(m_zvFoundation2.GetX() + m_zvFoundation1.GetX() - m_zgvPoles.GetX() - 0.001f, m_zvFoundation2.GetY() * 2 + m_zgvPoles.GetY(), m_zvFoundation2.GetZ() + m_zvFoundation1.GetZ() - m_zgvPoles.GetX() - 0.001f);
	m_zpvPole2.InitPoint(m_zvFoundation2.GetX() - m_zvFoundation1.GetX() + m_zgvPoles.GetX() - 0.001f, m_zvFoundation2.GetY() * 2 + m_zgvPoles.GetY(), m_zvFoundation2.GetZ() + m_zvFoundation1.GetZ() - m_zgvPoles.GetX() - 0.001f);
	m_zpvPole3.InitPoint(m_zvFoundation2.GetX() + m_zvFoundation1.GetX() - m_zgvPoles.GetX() - 0.001f, m_zvFoundation2.GetY() * 2 + m_zgvPoles.GetY(), m_zvFoundation2.GetZ() - m_zvFoundation1.GetZ() + m_zgvPoles.GetX() - 0.001f);
	m_zpvPole4.InitPoint(m_zvFoundation2.GetX() - m_zvFoundation1.GetX() + m_zgvPoles.GetX() - 0.001f, m_zvFoundation2.GetY() * 2 + m_zgvPoles.GetY(), m_zvFoundation2.GetZ() - m_zvFoundation1.GetZ() + m_zgvPoles.GetX() - 0.001f);

	//initialize upper pole vectors
	m_zgvUpperPole1.InitPoint(0.25f - 0.005f * 2.0f, 0.005f, 0.005f);
	m_zgvUpperPole2.InitPoint(0.005f, 0.005f, 0.25f - 0.005f * 2.0f);

	//initialize upper pole placement vectors
	m_zpvUpperPole1.InitPoint(m_zvFoundation2.GetX(), m_zgvPoles.GetY() + m_zgvPoles.GetY() - m_zgvPoles.GetX(), m_zpvPole1.GetZ());
	m_zpvUpperPole2.InitPoint(m_zpvPole1.GetX(), m_zgvPoles.GetY() + m_zgvPoles.GetY() - m_zgvPoles.GetX(), m_zvFoundation2.GetZ());
	m_zpvUpperPole3.InitPoint(m_zvFoundation2.GetX(), m_zgvPoles.GetY() + m_zgvPoles.GetY() - m_zgvPoles.GetX(), m_zpvPole3.GetZ());
	m_zpvUpperPole4.InitPoint(m_zpvPole2.GetX(), m_zgvPoles.GetY() + m_zgvPoles.GetY() - m_zgvPoles.GetX(), m_zvFoundation2.GetZ());

	//initialize front/back/left/right poles
	m_zgvBasisPoles.InitPoint(0.005f, 0.32f, 0.005f);

	//initialize front poles array-data
	m_zgBasisPoles[0] = m_zgBasisPole1;
	m_zgBasisPoles[1] = m_zgBasisPole2;
	m_zgBasisPoles[2] = m_zgBasisPole3;
	m_zgBasisPoles[3] = m_zgBasisPole4;
	m_zgBasisPoles[4] = m_zgBasisPole5; 
	m_zgBasisPoles[5] = m_zgBasisPole6;
	m_zgBasisPoles[6] = m_zgBasisPole7;
	m_zgBasisPoles[7] = m_zgBasisPole8;
	m_zgBasisPoles[8] = m_zgBasisPole9;
	m_zgBasisPoles[9] = m_zgBasisPole10;

	m_zpBasisPoles[0] = m_zpBasisPole1;
	m_zpBasisPoles[1] = m_zpBasisPole2;
	m_zpBasisPoles[2] = m_zpBasisPole3;
	m_zpBasisPoles[3] = m_zpBasisPole4;
	m_zpBasisPoles[4] = m_zpBasisPole5;
	m_zpBasisPoles[5] = m_zpBasisPole6;
	m_zpBasisPoles[6] = m_zpBasisPole7;
	m_zpBasisPoles[7] = m_zpBasisPole8;
	m_zpBasisPoles[8] = m_zpBasisPole9;
	m_zpBasisPoles[9] = m_zpBasisPole10;
}

CTrasse::~CTrasse(void) 
{
}

void CTrasse::Init()
{
	m_zmGrey.MakeTextureDiffuse("textures\\grey_image.jpg");
	m_zmBlack.MakeTextureDiffuse("textures\\black_image.jpg");

	this->placeFoundation();
	this->placeBasis();
	this->placeHead();
	this->placeConduit();

	//this->makeWall();
	//this->AddPlacement(&m_zpBaseWall);

	this->AddPlacement(&m_zpFoundation);
	this->AddPlacement(&m_zpBasis);
	this->AddPlacement(&m_zpHead);
	this->AddPlacement(&m_zpRightConduit);
	//m_pScene->AddPlacement(&m_zpFoundation);
	//m_pScene->AddPlacement(&m_zpBasis);
	//m_pScene->AddPlacement(&m_zpHead);
	//m_pScene->AddPlacement(&m_zpRightConduit);
}

void CTrasse::placeFoundation()
{
	//create foundation
	m_zgFoundation.Init(m_zvFoundation1, &m_zmGrey);
	m_zpFoundation.Translate(m_zvFoundation2);
	m_zpFoundation.AddGeo(&m_zgFoundation);
}

void CTrasse::placeBasis()
{
	//right hand bottom corner
	m_zgPole1.Init(m_zgvPoles, &m_zmBlack);
	m_zpPole1.Translate(m_zpvPole1);

	//left hand bottom corner
	m_zgPole2.Init(m_zgvPoles, &m_zmBlack);
	m_zpPole2.Translate(m_zpvPole2);

	//right hand upper corner
	m_zgPole3.Init(m_zgvPoles, &m_zmBlack);
	m_zpPole3.Translate(m_zpvPole3);

	//left hand upper corner
	m_zgPole4.Init(m_zgvPoles, &m_zmBlack);
	m_zpPole4.Translate(m_zpvPole4);

	m_zpPole1.AddGeo(&m_zgPole1);
	m_zpPole2.AddGeo(&m_zgPole2);
	m_zpPole3.AddGeo(&m_zgPole3);
	m_zpPole4.AddGeo(&m_zgPole4);

	float rotate = m_Helper.AngleToRad(50.0f);

	for (int i = 0; i < SIZEOF_ARRAY(m_zpBasisPoles); i += 2)
	{
		m_zgBasisPoles[i].Init(m_zgvBasisPoles, &m_zmBlack);
		m_zpBasisPoles[i].RotateZDelta(rotate);
		m_zgBasisPoles[i + 1].Init(m_zgvBasisPoles, &m_zmBlack);
		m_zpBasisPoles[i + 1].RotateZDelta(-rotate);

		switch (i)
		{
		case 0:
			m_zpBasisPoles[i].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.25f);
			m_zpBasisPoles[i + 1].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.25f);
			break;
		case 2:
			m_zpBasisPoles[i].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.325f + 0.325f);
			m_zpBasisPoles[i + 1].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.325f + 0.325f);
			break;
		case 4:
			m_zpBasisPoles[i].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.35f + 0.35f + 0.35f);
			m_zpBasisPoles[i + 1].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.35f + 0.35f + 0.35f);
			break;
		case 6:
			m_zpBasisPoles[i].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.365f + 0.365f + 0.365f + 0.365f);
			m_zpBasisPoles[i + 1].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.365f + 0.365f + 0.365f + 0.365f);
			break;
		case 8:
			m_zpBasisPoles[i].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.375f + 0.375f + 0.375f + 0.375f + 0.375f);
			m_zpBasisPoles[i + 1].TranslateYDelta(m_zvFoundation2.GetY() * 2 + 0.375f + 0.375f + 0.375f + 0.375f + 0.375f);
			break;
		}
	}

	//place front/back/right/left poles and add them to basis placement
	for (int i = 0; i < SIZEOF_ARRAY(m_zpBasisPoles); i++)
	{
		m_zpBasisPoles[i].AddGeo(&m_zgBasisPoles[i]);

		m_zpFrontPoles.AddPlacement(&m_zpBasisPoles[i]);
		m_zpBackPoles.AddPlacement(&m_zpBasisPoles[i]);
		m_zpRightPoles.AddPlacement(&m_zpBasisPoles[i]);
		m_zpLeftPoles.AddPlacement(&m_zpBasisPoles[i]);
	}

	m_zpFrontPoles.TranslateDelta(CHVector(m_zvFoundation2.GetX(), m_zvFoundation2.GetY(), m_zpvPole2.GetZ()));

	m_zpBackPoles.TranslateDelta(CHVector(m_zvFoundation2.GetX(), m_zvFoundation2.GetY(), m_zpvPole4.GetZ()));

	m_zpRightPoles.RotateYDelta(m_Helper.AngleToRad(90.0f));
	m_zpRightPoles.TranslateDelta(CHVector(m_zpvPole4.GetX(), m_zvFoundation2.GetY(), m_zvFoundation2.GetZ()));

	m_zpLeftPoles.RotateYDelta(m_Helper.AngleToRad(90.0f));
	m_zpLeftPoles.TranslateDelta(CHVector(m_zpvPole3.GetX(), m_zvFoundation2.GetY(), m_zvFoundation2.GetZ()));

	//place base poles
	m_zpBasis.AddPlacement(&m_zpPole1);
	m_zpBasis.AddPlacement(&m_zpPole2);
	m_zpBasis.AddPlacement(&m_zpPole3);
	m_zpBasis.AddPlacement(&m_zpPole4);

	m_zpBasis.AddPlacement(&m_zpFrontPoles);
	m_zpBasis.AddPlacement(&m_zpBackPoles);
	m_zpBasis.AddPlacement(&m_zpRightPoles);
	m_zpBasis.AddPlacement(&m_zpLeftPoles);
}

void CTrasse::placeHead()
{
	//upper front
	m_zgUpperPole1.Init(m_zgvUpperPole1, &m_zmBlack);
	m_zpUpperPole1.Translate(m_zpvUpperPole1);

	//upper right
	m_zgUpperPole2.Init(m_zgvUpperPole2, &m_zmBlack);
	m_zpUpperPole2.Translate(m_zpvUpperPole2);

	//upper back
	m_zgUpperPole3.Init(m_zgvUpperPole1, &m_zmBlack);
	m_zpUpperPole3.Translate(m_zpvUpperPole3);

	//upper left
	m_zgUpperPole4.Init(m_zgvUpperPole2, &m_zmBlack);
	m_zpUpperPole4.Translate(m_zpvUpperPole4);

	m_zgRoofPole1.Init(CHVector(0.005f, 0.23f, 0.005f), &m_zmBlack);
	m_zpRoofPole1.RotateXDelta(m_Helper.AngleToRad(-45.0f));
	m_zpRoofPole1.RotateYDelta(m_Helper.AngleToRad(45.0f));
	m_zpRoofPole1.TranslateDelta(CHVector(m_zvFoundation2.GetX() + 0.115f, m_zgvPoles.GetY() * 2.0f + 0.165f, m_zvFoundation2.GetZ() + 0.1175f));

	m_zgRoofPole2.Init(CHVector(0.005f, 0.23f, 0.005f), &m_zmBlack);
	m_zpRoofPole2.RotateXDelta(m_Helper.AngleToRad(-135.0f));
	m_zpRoofPole2.RotateYDelta(m_Helper.AngleToRad(135.0f));
	m_zpRoofPole2.TranslateDelta(CHVector(m_zvFoundation2.GetX() - 0.115f, m_zgvPoles.GetY() * 2.0f + 0.165f, m_zvFoundation2.GetZ() + 0.1175f));

	m_zgRoofPole3.Init(CHVector(0.005f, 0.23f, 0.005f), &m_zmBlack);
	m_zpRoofPole3.RotateXDelta(m_Helper.AngleToRad(-225.0f));
	m_zpRoofPole3.RotateYDelta(m_Helper.AngleToRad(225.0f));
	m_zpRoofPole3.TranslateDelta(CHVector(m_zvFoundation2.GetX() - 0.115f, m_zgvPoles.GetY() * 2.0f + 0.165f, m_zvFoundation2.GetZ() - 0.1175f));

	m_zgRoofPole4.Init(CHVector(0.005f, 0.23f, 0.005f), &m_zmBlack);
	m_zpRoofPole4.RotateXDelta(m_Helper.AngleToRad(-315.0f));
	m_zpRoofPole4.RotateYDelta(m_Helper.AngleToRad(315.0f));
	m_zpRoofPole4.TranslateDelta(CHVector(m_zvFoundation2.GetX() + 0.115f, m_zgvPoles.GetY() * 2.0f + 0.165f, m_zvFoundation2.GetZ() - 0.1175f));

	m_zpUpperPole1.AddGeo(&m_zgUpperPole1);
	m_zpUpperPole2.AddGeo(&m_zgUpperPole2);
	m_zpUpperPole3.AddGeo(&m_zgUpperPole3);
	m_zpUpperPole4.AddGeo(&m_zgUpperPole4);

	m_zpRoofPole1.AddGeo(&m_zgRoofPole1);
	m_zpRoofPole2.AddGeo(&m_zgRoofPole2);
	m_zpRoofPole3.AddGeo(&m_zgRoofPole3);
	m_zpRoofPole4.AddGeo(&m_zgRoofPole4);

	//place upper poles
	m_zpHead.AddPlacement(&m_zpUpperPole1);
	m_zpHead.AddPlacement(&m_zpUpperPole2);
	m_zpHead.AddPlacement(&m_zpUpperPole3);
	m_zpHead.AddPlacement(&m_zpUpperPole4);
	m_zpHead.AddPlacement(&m_zpRoofPole1);
	m_zpHead.AddPlacement(&m_zpRoofPole2);
	m_zpHead.AddPlacement(&m_zpRoofPole3);
	m_zpHead.AddPlacement(&m_zpRoofPole4);
}

void CTrasse::placeConduit(void)
{
	m_zgRightConduit1.Init(CHVector(0.49f, 0.005f, 0.005f), &m_zmBlack);
	m_zgRightConduit2.Init(CHVector(0.49f, 0.005f, 0.005f), &m_zmBlack);
	m_zgRightConduit3.Init(CHVector(0.55f, 0.005f, 0.005f), &m_zmGrey);
	m_zgRightConduit4.Init(CHVector(0.55f, 0.005f, 0.005f), &m_zmGrey);

	m_zpRightConduit1.RotateYDelta(m_Helper.AngleToRad(14.5f));
	m_zpRightConduit1.TranslateDelta(CHVector(m_zpvPole1.GetX() + 0.465f, m_zvFoundation2.GetY() * 2 + 0.375f + 0.375f + 0.375f + 0.375f + 0.17f, m_zpvPole1.GetZ() - 0.12f));

	m_zpRightConduit2.RotateYDelta(m_Helper.AngleToRad(-14.5f));
	m_zpRightConduit2.TranslateDelta(CHVector(m_zpvPole1.GetX() + 0.465f, m_zvFoundation2.GetY() * 2 + 0.375f + 0.375f + 0.375f + 0.375f + 0.17f, m_zpvPole3.GetZ() + 0.12f));

	m_zpRightConduit3.RotateYDelta(m_Helper.AngleToRad(15.0f));
	m_zpRightConduit3.RotateXDelta(m_Helper.AngleToRad(-65.0f));
	m_zpRightConduit3.TranslateDelta(CHVector(m_zpvPole1.GetX() + 0.55f, m_zvFoundation2.GetY() * 2 + 0.375f + 0.375f + 0.375f + 0.375f + 0.375f + 0.095f, m_zpvPole1.GetZ() - 0.1f));

	m_zpRightConduit4.RotateYDelta(m_Helper.AngleToRad(-15.0f));
	m_zpRightConduit4.RotateXDelta(m_Helper.AngleToRad(-65.0f));
	m_zpRightConduit4.TranslateDelta(CHVector(m_zpvPole1.GetX() + 0.475f, m_zvFoundation2.GetY() * 2 + 0.375f + 0.375f + 0.375f + 0.375f + 0.375f, m_zpvPole3.GetZ() + 0.1f));

	m_zpRightConduit1.AddGeo(&m_zgRightConduit1);
	m_zpRightConduit2.AddGeo(&m_zgRightConduit2);
	m_zpRightConduit3.AddGeo(&m_zgRightConduit3);
	m_zpRightConduit4.AddGeo(&m_zgRightConduit4);

	m_zpRightConduit.AddPlacement(&m_zpRightConduit1);
	m_zpRightConduit.AddPlacement(&m_zpRightConduit2);
	m_zpRightConduit.AddPlacement(&m_zpRightConduit3);
	m_zpRightConduit.AddPlacement(&m_zpRightConduit4);
}

void CTrasse::makeWall(void)
{

}

NAMESPACE_VIEW_E
