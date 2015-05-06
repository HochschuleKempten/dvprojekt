#pragma once

#include "LGeneral.h"
#include "LField.h"

NAMESPACE_LOGIC_B


class LPowerLine;
class LWindmillPowerPlant;
class LSolarPowerPlant;
class LHydroelectricPowerPlant;
class LCoalPowerPlant;
class LOilRefinery;
class LNuclearPowerPlant;

class LBalanceLoader
{
private:
	LBalanceLoader() = delete;
	LBalanceLoader(const LBalanceLoader&) = delete;
	LBalanceLoader(const LBalanceLoader&&) = delete;
	LBalanceLoader& operator=(const LBalanceLoader&) = delete;
	LBalanceLoader& operator=(const LBalanceLoader&&) = delete;
	~LBalanceLoader() = delete;

public:
	static void init();

	template<typename T> static int getCost() { return 0; }
	template<> static int getCost<LPowerLine>() { return 100; }
	template<> static int getCost<LWindmillPowerPlant>() { return 500; }
	template<> static int getCost<LSolarPowerPlant>() { return 500; }
	template<> static int getCost<LHydroelectricPowerPlant>() { return 500; }
	template<> static int getCost<LCoalPowerPlant>() { return 500; }
	template<> static int getCost<LOilRefinery>() { return 500; }
	template<> static int getCost<LNuclearPowerPlant>() { return 500; }

	static int getFieldStorage(const LField::FieldType fieldType);

	static double getMoneyPerWatt();
};


NAMESPACE_LOGIC_E
