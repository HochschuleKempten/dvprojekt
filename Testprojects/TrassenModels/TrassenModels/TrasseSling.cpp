#include "TrasseSling.h"
#include "Helper.h"

CTrasseSling::CTrasseSling()
{
	m_fPoleHeight = 1.0f;
	m_fPoleRadius = 0.2f;
	m_fWingHeight = 1.0f;

}


CTrasseSling::~CTrasseSling()
{

}

void CTrasseSling::Init(CScene * pScene)
{
	//m_zmWing.MakeTextureDiffuse("textures\\white_image.jpg");
	m_zmBasePole.MakeTextureBump("textures\\concrete.png");

	// initialize base pole
	m_zgBasePole.Init(m_fPoleRadius, m_fPoleRadius, m_fPoleHeight, &m_zmBasePole);

	// initialize wing
	m_zgWing.Init(m_fWingHeight, m_fWingHeight, 0, PI, &m_zmBasePole);
	CTriangleList * triangles = m_zgWing.CopyToTriangleList();
	triangles->SubdivideZ(2.0f);
	triangles->TaperZ(1.0f);

	// add wings to left/right placement
	m_zpWingLeft.AddGeo(triangles);
	m_zpWingRight.AddGeo(&m_zgWing);
	
	// move wings on top of base pole
	m_zpWingLeft.TranslateY(m_fPoleHeight);
	m_zpWingRight.TranslateY(m_fPoleHeight);

	// add wing placements to pole placement
	m_zpBasePole.AddGeo(&m_zgBasePole);

	m_zpBasePole.AddPlacement(&m_zpWingLeft);
	m_zpBasePole.AddPlacement(&m_zpWingRight);

	//m_zpBasePole.Translate(CHVector(0, 0, -6.0f));
	//m_zpBasePole.TranslateXDelta(-6.0f);
	
	// add main placement to scene
	pScene->AddPlacement(&m_zpBasePole);
}
