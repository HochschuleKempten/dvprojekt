#pragma once

class IVPlayingField;
class LPlayingField;
class IVPowerPlant;
class LCoalPowerPlant;
class LHydroelectricPowerPlant;
class LNuclearPowerPlant;
class LOilRefinery;
class LSolarPowerPlant;
class LWindmillPowerPlant;
class IVUI;
class LUI;

class IVFactory
{
public:
	IVFactory()
	{}
	virtual ~IVFactory(){};
	virtual IVPlayingField* createPlayingField(LPlayingField* field) = 0;
	virtual IVPowerPlant* createCoalPowerPlant(LCoalPowerPlant* powerPlant) = 0;
	virtual IVPowerPlant* createHydroelectricPowerPlant(LHydroelectricPowerPlant* powerPlant) = 0;
	virtual IVPowerPlant* createNuclearPowerPlant(LNuclearPowerPlant* powerPlant) = 0;
	virtual IVPowerPlant* createOilRefinery(LOilRefinery* powerPlant) = 0;
	virtual IVPowerPlant* createSolarPowerPlant(LSolarPowerPlant* powerPlant) = 0;
	virtual IVPowerPlant* createWindmillPowerPlant(LWindmillPowerPlant* powerPlant) = 0; 
	virtual IVUI* createUi(LUI* lUi) = 0;
};

