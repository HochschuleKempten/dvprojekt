#pragma once
#include "../logic/IVFactory.h"
#include "VGeneral.h"

NAMESPACE_VIEW_B


class VMaster;

class VFactory : public IVFactory
{
private:
	VMaster* vMaster;

public:
	VFactory(VMaster* vMaster)
		: vMaster(vMaster)
	{}
	virtual ~VFactory()
	{}

	virtual IVPlayingField* createPlayingField(LPlayingField* field);

	virtual IVPowerPlant* createCoalPowerPlant(LCoalPowerPlant* powerPlant);

	virtual IVPowerPlant* createHydroelectricPowerPlant(LHydroelectricPowerPlant* powerPlant);

	virtual IVPowerPlant* createNuclearPowerPlant(LNuclearPowerPlant* powerPlant);

	virtual IVPowerPlant* createOilRefinery(LOilRefinery* powerplant);

	virtual IVPowerPlant* createSolarPowerPlant(LSolarPowerPlant* powerPlant);

	virtual IVPowerPlant* createWindmillPowerPlant(LWindmillPowerPlant* powerPlant);

	virtual IVPowerLine* createPowerLine(LPowerLine* powerLine);

	virtual IVUI* createUi(LUI* lUi);
};


NAMESPACE_VIEW_E
