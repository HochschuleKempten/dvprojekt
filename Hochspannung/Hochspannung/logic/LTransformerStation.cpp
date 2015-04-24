#include "LTransformerSation.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVTransformerStation.h"

NAMESPACE_LOGIC_B


LTransformerStation::LTransformerStation(LField* lField, const int x, const int y)
: ILBuilding(lField), vTransformerSation(lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createTransformerStation(this))
{
	vTransformerSation->initTransformerStation(vTransformerSation, x, y);
	lField->getLPlayingField()->getLMaster()->getVMaster()->registerObserver(this);
}

LTransformerStation::~LTransformerStation()
{
}

void LTransformerStation::tick(const float fTimeDelta)
{	
}



NAMESPACE_LOGIC_E
