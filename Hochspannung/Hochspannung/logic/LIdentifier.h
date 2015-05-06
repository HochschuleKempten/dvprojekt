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

	namespace fwd
	{
		class LCoalPowerPlant;
		class LHydroelectricPowerPlant;
		class LNuclearPowerPlant;
		class LOilRefinery;
		class LSolarPowerPlant;
		class LWindmillPowerPlant;
		class LCity;
		class LPowerLine;
		class LTransformerStation;
	}

	template<typename T>
	LIdentifier getIdentifierForType()
	{
		ASSERT("Unknown type");
		return CASTS<LIdentifier>(-1);
	}
	template<> inline LIdentifier getIdentifierForType<fwd::LCoalPowerPlant>() { return LCoalPowerPlant; }
	template<> inline LIdentifier getIdentifierForType<fwd::LHydroelectricPowerPlant>() { return LHydroelectricPowerPlant; }
	template<> inline LIdentifier getIdentifierForType<fwd::LNuclearPowerPlant>() { return LNuclearPowerPlant; }
	template<> inline LIdentifier getIdentifierForType<fwd::LOilRefinery>() { return LOilRefinery; }
	template<> inline LIdentifier getIdentifierForType<fwd::LSolarPowerPlant>() { return LSolarPowerPlant; }
	template<> inline LIdentifier getIdentifierForType<fwd::LWindmillPowerPlant>() { return LWindmillPowerPlant; }
	template<> inline LIdentifier getIdentifierForType<fwd::LCity>() { return LCity; }
	template<> inline LIdentifier getIdentifierForType<fwd::LPowerLine>() { return LPowerLine; }
	template<> inline LIdentifier getIdentifierForType<fwd::LTransformerStation>() { return LTransformerStation; }
}

NAMESPACE_LOGIC_E
