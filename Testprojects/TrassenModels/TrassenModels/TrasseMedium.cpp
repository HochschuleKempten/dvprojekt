#include "TrasseMedium.h"


CTrasseMedium::CTrasseMedium()
{
}


CTrasseMedium::~CTrasseMedium()
{

}

void CTrasseMedium::Init(CScene * pScene)
{
	m_zmCube.MakeTextureDiffuse("textures\\concrete.png");
	m_zgCube.Init(1.0f, 1.0f, 3.0f, &m_zmCube);
	
	CTriangleList * triangles = m_zgCube.CopyToTriangleList();
	triangles->SubdivideY(0.1f);
	triangles->TwistY(20.0f);

	m_zpCube.AddGeo(triangles);
	
	m_zpCube.Translate(CHVector(0, 0, -3.0f)); 
	pScene->AddPlacement(&m_zpCube);
}
