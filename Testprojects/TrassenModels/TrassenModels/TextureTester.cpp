#include "StdAfx.h"
#include "TextureTester.h"

CTextureTester::CTextureTester(void)
{
}

CTextureTester::~CTextureTester(void)
{
}

void CTextureTester::Init(CScene *m_pScene)
{
	m_zmWall.MakeTextureDiffuse("textures\\grey_image.jpg");
	m_zmWall.SetTextureSpecularWhite();

	m_zgWall1.Init(2.0f, 2.0f, 0.2f, &m_zmWall);
	m_zgWall2.Init(2.0f, 2.0f, 0.2f, &m_zmWall);
	m_zgWall3.Init(2.0f, 2.0f, 0.2f, &m_zmWall);
	m_zgWall4.Init(2.0f, 2.0f, 0.2f, &m_zmWall);

	m_zpWall1.RotateX(-HALFPI);

	m_zpWall1.Translate(CHVector(0, 2.0f, -3.0f));
	m_zpWall2.Translate(CHVector(0, 3.0f, -6.0f));
	m_zpWall3.Translate(CHVector(0, 4.0f, -9.0f));
	m_zpWall4.Translate(CHVector(0, 5.0f, -12.0f));

	m_zpWall1.AddGeo(&m_zgWall1);
	m_zpWall2.AddGeo(&m_zgWall2);
	m_zpWall3.AddGeo(&m_zgWall3);
	m_zpWall4.AddGeo(&m_zgWall4);

	m_pScene->AddPlacement(&m_zpWall1);
	m_pScene->AddPlacement(&m_zpWall2);
	m_pScene->AddPlacement(&m_zpWall3);
	m_pScene->AddPlacement(&m_zpWall4);
}