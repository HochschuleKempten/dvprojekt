#pragma once

#include "LGeneral.h"
#include "LUtility.h"

NAMESPACE_LOGIC_B


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

	class HighVoltage::LCoalPowerPlant;
	class HighVoltage::LHydroelectricPowerPlant;
	class HighVoltage::LNuclearPowerPlant;
	class HighVoltage::LOilRefinery;
	class HighVoltage::LSolarPowerPlant;
	class HighVoltage::LWindmillPowerPlant;
	class HighVoltage::LCity;
	class HighVoltage::LPowerLine;
	class HighVoltage::LTransformerStation;

	template<typename T>
	LIdentifier getIdentifierForType()
	{
		ASSERT("Unknown type");
		return CASTS<LIdentifier>(-1);
	}
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LCoalPowerPlant>() { return LCoalPowerPlant; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LHydroelectricPowerPlant>() { return LHydroelectricPowerPlant; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LNuclearPowerPlant>() { return LNuclearPowerPlant; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LOilRefinery>() { return LOilRefinery; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LSolarPowerPlant>() { return LSolarPowerPlant; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LWindmillPowerPlant>() { return LWindmillPowerPlant; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LCity>() { return LCity; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LPowerLine>() { return LPowerLine; }
	template<> inline LIdentifier getIdentifierForType<HighVoltage::LTransformerStation>() { return LTransformerStation; }
}

NAMESPACE_LOGIC_E
