#include "VModelMountains.h"

NAMESPACE_VIEW_B


VModelMountains::VModelMountains()
{}

VModelMountains::~VModelMountains()
{}

void VModelMountains::init()
{
	m_zpLOD[0].AddPlacement(&m_zpBerg);
	m_zpLOD[1].AddPlacement(&m_zpBerg);
	m_zpLOD[2].AddPlacement(&m_zpBerg);


	//Gebirge
	m_zgBerg.Init(2.0f, 3.0f, VMaterialLoader::getMaterialModel(VMaterialLoader::COAL_MOUNTAIN, switchedState), 16);


	//Placements

	m_zpBerg.AddPlacement(&m_zpGebirge1);
	m_zpBerg.AddPlacement(&m_zpGebirge2);
	m_zpBerg.AddPlacement(&m_zpGebirge3);

	m_zpGebirge1.AddPlacement(&m_zpGebirge);
	m_zpGebirge2.AddPlacement(&m_zpGebirge);
	m_zpGebirge3.AddPlacement(&m_zpGebirge);

	m_zpGebirge.AddPlacement(&m_zpBerg1);
	m_zpGebirge.AddPlacement(&m_zpBerg2);
	m_zpGebirge.AddPlacement(&m_zpBerg3);
	m_zpGebirge.AddPlacement(&m_zpBerg4);
	m_zpGebirge.AddPlacement(&m_zpBerg5);
	m_zpGebirge.AddPlacement(&m_zpBerg6);
	m_zpGebirge.AddPlacement(&m_zpBerg7);
	m_zpGebirge.AddPlacement(&m_zpBerg8);


	//Adding

	m_zpBerg1.AddGeo(&m_zgBerg);

	m_zpBerg2.Scale(0.9f);
	m_zpBerg2.TranslateDelta(CHVector(0.5f, 0.0f, 0.0f));
	m_zpBerg2.AddGeo(&m_zgBerg);

	m_zpBerg3.Scale(0.8f);
	m_zpBerg3.TranslateDelta(CHVector(-1.0f, 0.0f, 0.5f));
	m_zpBerg3.AddGeo(&m_zgBerg);

	m_zpBerg4.Scale(0.6f);
	m_zpBerg4.TranslateDelta(CHVector(1.5f, 0.0f, 0.5f));
	m_zpBerg4.AddGeo(&m_zgBerg);

	m_zpBerg5.Scale(0.9f);
	m_zpBerg5.TranslateDelta(CHVector(2.0f, 0.0f, -0.5f));
	m_zpBerg5.AddGeo(&m_zgBerg);

	m_zpBerg6.Scale(0.85f);
	m_zpBerg6.TranslateDelta(CHVector(-2.0f, 0.0f, -0.5f));
	m_zpBerg6.AddGeo(&m_zgBerg);

	m_zpBerg7.Scale(0.7f);
	m_zpBerg7.TranslateDelta(CHVector(-2.0f, 0.0f, 0.5f));
	m_zpBerg7.AddGeo(&m_zgBerg);

	m_zpBerg8.Scale(0.7f);
	m_zpBerg8.TranslateDelta(CHVector(2.5f, 0.0f, 0.6f));
	m_zpBerg8.AddGeo(&m_zgBerg);

	m_zpGebirge.Scale(1.2f);
	m_zpGebirge.ScaleXDelta(1.1f);
	m_zpGebirge1.Translate(CHVector(-0.2f, 0.2f, -2.3f));
	//m_zpGebirge2.Translate(CHVector(0.0f, 0.0f, 0.0f));
	m_zpGebirge3.Translate(CHVector(-0.2f, 0.2f, 2.3f));
	
}

NAMESPACE_VIEW_E
