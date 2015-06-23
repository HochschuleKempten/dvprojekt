#pragma once

#include "VGeneral.h"
#include "../logic/IVFactory.h"

NAMESPACE_VIEW_B


class VMaster;

class VFactory : public IVFactory
{
	NON_COPYABLE(VFactory);

private:
	VMaster* vMaster;

public:
	explicit VFactory(VMaster* vMaster);
	virtual ~VFactory();

	virtual std::shared_ptr<IVPlayingField> createPlayingField(LPlayingField* field) override;

	virtual std::shared_ptr<IVPowerPlant> createCoalPowerPlant(LCoalPowerPlant* powerPlant) override;

	virtual std::shared_ptr<IVPowerPlant> createHydroelectricPowerPlant(LHydroelectricPowerPlant* powerPlant) override;
			
	virtual std::shared_ptr<IVPowerPlant> createNuclearPowerPlant(LNuclearPowerPlant* powerPlant) override;
			
	virtual std::shared_ptr<IVPowerPlant> createOilRefinery(LOilRefinery* powerplant) override;
			
	virtual std::shared_ptr<IVPowerPlant> createSolarPowerPlant(LSolarPowerPlant* powerPlant) override;
			
	virtual std::shared_ptr<IVPowerPlant> createWindmillPowerPlant(LWindmillPowerPlant* powerPlant) override;

	virtual std::shared_ptr<IVPowerLine> createPowerLine(LPowerLine* powerLine) override;

	virtual std::shared_ptr<IVCity> createCity(LCity* city) override;

	virtual std::shared_ptr<IVTransformerStation> createTransformerStation(LTransformerStation* transformerStation) override;
};


NAMESPACE_VIEW_E
