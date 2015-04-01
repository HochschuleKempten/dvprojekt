#pragma once

class IVPlayingField;
class LPlayingField;
class IVPowerPlant;
class LCoalPowerPlant;

class IVFactory
{
public:
	IVFactory()
	{}
	virtual ~IVFactory(){};
	virtual IVPlayingField* createPlayingField(LPlayingField* field) = 0;
	virtual IVPowerPlant* createCoalPowerPlant(LCoalPowerPlant* powerPlant) = 0;
};

