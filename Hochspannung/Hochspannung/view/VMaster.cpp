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
	vUi.initUI(hwnd, psplash);
}

void VMaster::tick(float fTime, float fTimeDelta)
{
	updateTick(fTimeDelta);
}

IVFactory* VMaster::getFactory()
{
	return &factory;
}

void VMaster::gameOver()
{
	static bool informed = false;
	if (!informed) {
		DEBUG_OUTPUT("Game is over");
		informed = true;
	}
	//TODO (V) do something useful here when UI is ready
}

VPlayingField* VMaster::getPlayingField()
{
	ASSERT(vPlayingField != nullptr, "VPlayingField is not initialized");

	return vPlayingField.get();
}

VUI* HighVoltage::VMaster::getVUi()
{
	return &vUi;
}

void VMaster::setVPlayingField(const std::shared_ptr<VPlayingField>& vPlayingField)
{
	this->vPlayingField = vPlayingField;
	vUi.m_zs.AddPlacement(vPlayingField->getPlacement());
}

void VMaster::resize(int width, int height)
{
	vUi.resize(width, height);
}

void VMaster::updateMoney(const int money)
{
	vUi.updateMoney(money);
}


NAMESPACE_VIEW_E
