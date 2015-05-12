#pragma once

#include "LGeneral.h"
#include "LField.h"
#include "LUtility.h"
#include "LIdentifier.h"
#include <unordered_map>
#include <boost\property_tree\ptree.hpp>

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

private:
	static boost::property_tree::ptree propertyTree;
	DEBUG_EXPRESSION(static bool initDone);

public:
	static void init();

	template<typename T> static int getCost() { return 0; }
	template<> static int getCost<LPowerLine>() { return propertyTree.get<int>("Cost.PowerLine", 0); }
	template<> static int getCost<LWindmillPowerPlant>() { return propertyTree.get<int>("Cost.WindmillPowerPlant", 0); }
	template<> static int getCost<LSolarPowerPlant>() { return propertyTree.get<int>("Cost.SolarPowerPlant", 0); }
	template<> static int getCost<LHydroelectricPowerPlant>() { return propertyTree.get<int>("Cost.HydroelectricPowerPlant", 0); }
	template<> static int getCost<LCoalPowerPlant>() { return propertyTree.get<int>("Cost.CoalPowerPlant", 0); }
	template<> static int getCost<LOilRefinery>() { return propertyTree.get<int>("Cost.OilRefinery", 0); }
	template<> static int getCost<LNuclearPowerPlant>() { return propertyTree.get<int>("Cost.NuclearPowerPlant", 0); }

	static int getFieldStorage(const LField::FieldType fieldType);
	static int getConsumedResources(const LField::FieldType fieldType);
	static int getProducedEnergy(const LIdentifier::LIdentifier identifier);

	static double getMoneyPerWatt();
	/**
	 * @brief Specifies the factor of money returned when selling buildings.
	 */
	static double getSellRevenue();
	static std::unordered_map<LField::FieldType, double> getFieldTypeRatio();
	static std::unordered_map<LField::FieldLevel, double> getFieldLevelFactor();

	//-----City properties----
	/**
	 * @brief Growth rate of the city in number of peoples per second.
	 */
	static int getPopulationGrowth();
	/**
	 * @brief Energy consumption of the city in watt per citizen.
	 */
	static double getConsumptionPerCitizen();
	/**
	 * @brief Default population of the city.
	 */
	static int getStartPopulation();
	/**
	 * @brief Maximum number of citizen in the city.
	 */
	static int getMaxPopulation();
	/**
	 * @brief Offset for placing the city on the map (relative from the top left corner for the first and bottom right corner for the second player).
	 */
	static int getMapOffset();
};


NAMESPACE_LOGIC_E
