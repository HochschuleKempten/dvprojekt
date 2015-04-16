#include "VMaster.h"
#include "../logic/LMaster.h"
#include "VFactory.h"
#include "VPlayingField.h"
#include "VUI.h"
#include "IViewObject.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


VMaster::VMaster()
	: factory(this), vUi(this)
{
	VMaterialLoader::init();
}

VMaster::~VMaster()
{}

void VMaster::setLMaster(LMaster* lMaster)
{
	this->lMaster = lMaster;
}

void VMaster::initScene(HWND hwnd, CSplash* psplash)
{
	m_zr.Init(psplash);
	m_zf.Init(hwnd);
	m_zr.AddFrameHere(&m_zf);
	
	vUi.initUI();
}

void VMaster::tick(float fTime, float fTimeDelta)
{
	//PERFORMANCE make as much functions inline as possible

	m_zr.Tick(fTimeDelta);
	updateTick(fTimeDelta);
}

IVFactory* VMaster::getFactory()
{
	return &factory;
}

VPlayingField* VMaster::getPlayingField()
{
	ASSERT(vPlayingField != nullptr, "VPlayingField is not initialized");

	return vPlayingField.get();
}

void VMaster::setVPlayingField(const std::shared_ptr<VPlayingField>& vPlayingField)
{
	this->vPlayingField = vPlayingField;
	vUi.m_zs.AddPlacement(vPlayingField->getPlacement());
}

void VMaster::resize(int width, int heigth)
{
	m_zf.ReSize(width, heigth);
}


NAMESPACE_VIEW_E
