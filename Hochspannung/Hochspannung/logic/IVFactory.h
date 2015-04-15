#pragma once
#include <memory>
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class IVPlayingField;
class IVPowerLine;
class LPlayingField;
class IVPowerPlant;
class LCoalPowerPlant;
class LHydroelectricPowerPlant;
class LNuclearPowerPlant;
class LOilRefinery;
class LSolarPowerPlant;
class LWindmillPowerPlant;
class LPowerLine;
class IVUI;
class LUI;

class IVFactory
{
public:
	IVFactory()
	{}
	virtual ~IVFactory(){};
	virtual IVPlayingField* createPlayingField(LPlayingField* field) = 0;
	virtual std::shared_ptr<IVPowerPlant> createCoalPowerPlant(LCoalPowerPlant* powerPlant) = 0;
	virtual std::shared_ptr<IVPowerPlant> createHydroelectricPowerPlant(LHydroelectricPowerPlant* powerPlant) = 0;
	virtual std::shared_ptr<IVPowerPlant> createNuclearPowerPlant(LNuclearPowerPlant* powerPlant) = 0;
	virtual std::shared_ptr<IVPowerPlant> createOilRefinery(LOilRefinery* powerPlant) = 0;
	virtual std::shared_ptr<IVPowerPlant> createSolarPowerPlant(LSolarPowerPlant* powerPlant) = 0;
	virtual std::shared_ptr<IVPowerPlant> createWindmillPowerPlant(LWindmillPowerPlant* powerPlant) = 0;
	virtual std::shared_ptr<IVPowerLine> createPowerLine(LPowerLine* powerLine) = 0;
};

NAMESPACE_LOGIC_E