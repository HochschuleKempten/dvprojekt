#include "Building02.h"
#include "VMaterialLoader.h"
NAMESPACE_VIEW_B

Building02::Building02()
{
	fresize = 1.F;
	InitWindows();
	AddWindows();
	InitWalls();
	AddPlacements();
	TranslateAll();
	scaleforLoDs();
}

Building02::Building02(float fResize)
{
	fresize = fResize;

	if (fresize == 1)
	{
		InitWindows();
		AddWindows();
	}
	InitWalls();
	AddPlacements();
	TranslateAll();
	scaleforLoDs();
}


Building02::~Building02()
{
	//TODO (JS) remove or fix
	//removeMaterial(&m_zmWallNorth);
	//removeMaterial(&m_zmDach);
	//removeMaterial(&m_zmWallFrame);
}

void Building02::InitWindows()
{
	m_zgWallFrame.Init(1.F, 1.F, 0.5F, &m_zmWallNorth);
	m_zgWindow.InitRect(CFloatRect(0.2F, 0.9F, 0.2F, 0.1F), false);
	m_zgWindow.AddGeoWall(&m_zgWallFrame);
}

void Building02::AddWindows()
{
	m_zWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0.F, 0.1F, 1.F, 0.8F), 4, 5);
}

void Building02::InitWalls()
{
	m_zWallNorth.Init(fstandardwidthwall / fresize, fstandardheightwall / fresize, fstandarddepthwall / fresize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_WALLFRAME, switchedState));
	m_zgDach.Init(CHVector(fstandardwidthroof / fresize, fstandardheightroof / fresize, fstandarddepthroof / fresize, 0.F), &m_zmDach);
}

void Building02::AddPlacements()
{
	m_zpbuilding02.AddPlacement(&m_zpWallNorth);
	m_zpbuilding02.AddPlacement(&m_zpWallWest);
	m_zpbuilding02.AddPlacement(&m_zpWallEast);
	m_zpbuilding02.AddPlacement(&m_zpWallSouth);
	m_zpbuilding02.AddPlacement(&m_zpDach);

	AddPlacement(&m_zpbuilding02);


	m_zpWallNorth.AddGeo(&m_zWallNorth);
	m_zpWallWest.AddGeo(&m_zWallNorth);
	m_zpWallEast.AddGeo(&m_zWallNorth);
	m_zpWallSouth.AddGeo(&m_zWallNorth);
	m_zpDach.AddGeo(&m_zgDach);
}

void Building02::TranslateAll()
{
	m_zpWallNorth.Translate(0.F, 0.F, 0.F);

	m_zpWallWest.RotateY(PI / 2.F);
	m_zpWallWest.TranslateDelta((fstandardwidthwall / fresize), 0.F, 0.F);

	m_zpWallEast.RotateY(PI / 2.F);
	//m_zpWallEast.Translate((fstandardwidthwall / fresize) / -2, (fstandardwidthwall / fresize) / -2, 0.F);
	//m_zpWallSouth.RotateY(PI);
	m_zpWallSouth.TranslateDelta(0.F, 0.F, fstandardwidthwall / -fresize);

	m_zpDach.Translate((fstandardwidthwall / fresize) / 2, fstandardheightwall / fresize, (fstandardwidthwall / -fresize) / 2);
}

void Building02::scaleforLoDs()
{
	m_zpbuilding02.Scale(fresize);
}

void Building02::switchOn()
{
}

void Building02::switchOff()
{
}

NAMESPACE_VIEW_E
