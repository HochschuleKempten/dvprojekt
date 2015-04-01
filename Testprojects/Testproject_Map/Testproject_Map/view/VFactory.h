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

	//Argument from type ILPowerPlant so we just need one create method
	//(in definition: check for concrete type and create the counterpart)
	virtual IVPowerPlant* createCoalPowerPlant(LCoalPowerPlant* powerPlant);
};


NAMESPACE_VIEW_E
