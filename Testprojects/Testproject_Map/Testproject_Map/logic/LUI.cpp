#include "LUI.h"
#include "IVUI.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"

LUI::LUI(LMaster* lMaster)
	: lMaster(lMaster), vUi(this->lMaster->getVMaster()->getFactory()->createUi(this))
{}


LUI::~LUI()
{
	delete vUi;
}

void LUI::initVUi()
{
	vUi->initUI();
}
