#pragma once

#include "LGeneral.h"
#include "LField.h"
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\ini_parser.hpp>

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

	static boost::property_tree::ptree propertyTree;

public:
	static void init();

	template<typename T> static int getCost() { return 0; }
	template<> static int getCost<LPowerLine>() { return propertyTree.get<int>("Cost.PowerLine", 0); }
	template<> static int getCost<LSolarPowerPlant>() { return propertyTree.get<int>("Cost.SolarPowerPlant", 0); }
	template<> static int getCost<LHydroelectricPowerPlant>() { return propertyTree.get<int>("Cost.HydroelectricPowerPlant", 0); }
	template<> static int getCost<LCoalPowerPlant>() { return propertyTree.get<int>("Cost.CoalPowerPlant", 0); }
	template<> static int getCost<LOilRefinery>() { return propertyTree.get<int>("Cost.OilRefinery", 0); }
	template<> static int getCost<LNuclearPowerPlant>() { return propertyTree.get<int>("Cost.NuclearPowerPlant", 0);}

	static int getFieldStorage(const LField::FieldType fieldType);

	static double getMoneyPerWatt();

};


NAMESPACE_LOGIC_E
