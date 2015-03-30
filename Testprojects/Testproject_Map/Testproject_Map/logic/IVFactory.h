#pragma once

class IVPlayingField;
class LPlayingField;
class IVPowerPlant;
class ILPowerPlant;

class IVFactory
{
public:
	IVFactory()
	{}
	virtual ~IVFactory(){};
	virtual IVPlayingField* createPlayingField(LPlayingField* field) = 0;
	virtual IVPowerPlant* createPowerPlant(ILPowerPlant* powerPlant) = 0;
};

