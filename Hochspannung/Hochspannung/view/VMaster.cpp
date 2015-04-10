#include "VMaster.h"
#include "../logic/LMaster.h"
#include "VFactory.h"
#include "VPlayingField.h"
#include "VUI.h"
#include "IViewObject.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


VMaster::VMaster()
	: factory(this)
{
	VMaterialLoader::init();
}

void VMaster::setLMaster(LMaster* lMaster)
{
	this->lMaster = lMaster;
}

void VMaster::setVUI(VUI* vUi)
{
	this->vUi = vUi;
}

void VMaster::initScene(HWND hwnd, CSplash* psplash)
{
	m_zr.Init(psplash);
	m_zf.Init(hwnd);
	m_zr.AddFrameHere(&m_zf);
	

	vUi->initUI();
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
	return dynamic_cast<VPlayingField*>(views[getClassName(VPlayingField)]);
}

void VMaster::addScenegraph(const std::string &name, IViewObject* view)
{
	views[name] = view;
	vUi->m_zs.AddPlacement(view->getPlacement());
}

void VMaster::resize(int width, int heigth)
{
	m_zf.ReSize(width, heigth);
}


NAMESPACE_VIEW_E
