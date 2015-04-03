#include "VMaster.h"
#include "../logic/IView.h"
#include "../logic/LMaster.h"
#include "../logic/LUtility.h"
#include "VFactory.h"
#include "VPlayingField.h"
#include "VUI.h"
#include "IViewObject.h"

NAMESPACE_VIEW_B


VMaster::VMaster()
	: factory(this)
{
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
	m_zc.Init();
	m_zv.InitFull(&m_zc);
	m_zr.AddFrameHere(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zr.AddScene(&m_zs);

	m_zb.InitFull("textures/red_image.jpg");
	m_zv.AddBackground(&m_zb);

	m_zs.AddPlacement(&m_zpCamera);
	m_zpCamera.AddCamera(&m_zc);
	
	m_zpCamera.TranslateZ(50.0);
	m_zpCamera.RotateXDelta(0.3 * PI);

	m_zs.AddParallelLight(&m_zl);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f),
			  CColor(1.0f, 1.0f, 1.0f));
}

void VMaster::tick(float fTime, float fTimeDelta)
{
	//PERFORMANCE make as much functions inline as possible

	vUi->handleInput(fTimeDelta);
	lMaster->tick(fTime, fTimeDelta);
	m_zr.Tick(fTimeDelta);
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
	m_zs.AddPlacement(view->getPlacement());
}

void VMaster::resize(int width, int heigth)
{
	m_zf.ReSize(width, heigth);
}


NAMESPACE_VIEW_E
