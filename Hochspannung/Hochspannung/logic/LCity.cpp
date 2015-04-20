#include "LCity.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVCity.h"

NAMESPACE_LOGIC_B


LCity::LCity(LField* lField, const int x, const int y)
	: ILBuilding(lField), vCity(lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createCity(this))
{
	vCity->initCity(vCity, x, y);
}

LCity::~LCity()
{
}

void LCity::setEnergy(const int energy)
{
	this->energy = energy;
}

int LCity::getEnergy()
{
	return energy;
}


NAMESPACE_LOGIC_E
