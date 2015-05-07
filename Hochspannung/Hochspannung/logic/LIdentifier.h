#pragma once

#include "LGeneral.h"
#include "LUtility.h"

NAMESPACE_LOGIC_B

class LCity;
class LTransformerStation;
class LPowerLine;
class LWindmillPowerPlant;
class LSolarPowerPlant;
class LHydroelectricPowerPlant;
class LCoalPowerPlant;
class LOilRefinery;
class LNuclearPowerPlant;

namespace LIdentifier
{
	enum LIdentifier
	{
		LCoalPowerPlant = 100,
		LHydroelectricPowerPlant = 101,
		LNuclearPowerPlant = 102,
		LOilRefinery = 103,
		LSolarPowerPlant = 104,
		LWindmillPowerPlant = 105,
		LCity = 106,
		LPowerLine = 107,
		LTransformerStation = 108
	};

	template<typename T>
	LIdentifier getIdentifierForType()
	{
		ASSERT("Unknown type");
		return CASTS<LIdentifier>(-1);
	}
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LCity>() { return LCity; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LTransformerStation>() { return LTransformerStation; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LPowerLine>() { return LPowerLine; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LWindmillPowerPlant>() { return LWindmillPowerPlant; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LSolarPowerPlant>() { return LSolarPowerPlant; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LHydroelectricPowerPlant>() { return LHydroelectricPowerPlant; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LCoalPowerPlant>() { return LCoalPowerPlant; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LOilRefinery>() { return LOilRefinery; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LNuclearPowerPlant>() { return LNuclearPowerPlant; }
}

NAMESPACE_LOGIC_E
