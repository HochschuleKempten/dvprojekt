#pragma once

#include "LGeneral.h"
#include "LField.h"
#include "LUtility.h"
#include "LIdentifier.h"
#include "LSabotage.h"
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

	//-----Cost----
	/**
	 * @brief Costs for the different buildings.
	 */
	template<typename T> static int getCost() { return 0; } //Every other building has no costs
	template<> static int getCost<LPowerLine>() { CATCH(return propertyTree.get<int>("Cost.PowerLine"), boost::property_tree::ptree_error, ASSERT(e.what())); }
	template<> static int getCost<LWindmillPowerPlant>() { CATCH(return propertyTree.get<int>("Cost.WindmillPowerPlant"), boost::property_tree::ptree_error, ASSERT(e.what())); }
	template<> static int getCost<LSolarPowerPlant>() { CATCH(return propertyTree.get<int>("Cost.SolarPowerPlant"), boost::property_tree::ptree_error, ASSERT(e.what())); }
	template<> static int getCost<LHydroelectricPowerPlant>() { CATCH(return propertyTree.get<int>("Cost.HydroelectricPowerPlant"), boost::property_tree::ptree_error, ASSERT(e.what())); }
	template<> static int getCost<LCoalPowerPlant>() { CATCH(return propertyTree.get<int>("Cost.CoalPowerPlant"), boost::property_tree::ptree_error, ASSERT(e.what())); }
	template<> static int getCost<LOilRefinery>() { CATCH(return propertyTree.get<int>("Cost.OilRefinery"), boost::property_tree::ptree_error, ASSERT(e.what())); }
	template<> static int getCost<LNuclearPowerPlant>() { CATCH(return propertyTree.get<int>("Cost.NuclearPowerPlant"), boost::property_tree::ptree_error, ASSERT(e.what())); }
	
	//-----ProducedEnergy----
	/**
	 * @brief Produced energy for a power plant per second.
	 */
	static int getProducedEnergy(const LIdentifier::LIdentifier identifier);

	//-----FieldStorage----
	/**
	 * @brief Storage amount of the fossil energy resources.
	 */
	static int getFieldStorage(const LField::FieldType fieldType);

	//-----ConsumedResources----
	/**
	 * @brief Consumed resources for a fossil field type per second.
	 */
	static int getConsumedResources(const LField::FieldType fieldType);

	//-----FieldTypeRatio----
	/**
	* @brief Specifies for every field type the percentage share of its total occurrence.
	*/
	static std::unordered_map<LField::FieldType, double> getFieldTypeRatio();

	//-----FieldLevelFactor----
	/**
	* @brief Specifies for every field level the factor for multiplication with the resource amount.
	*/
	static std::unordered_map<LField::FieldLevel, double> getFieldLevelFactor();

	//-----DifficultyScale----
	/**
	 * @brief Money per watt energy the player gets per second for his surplus.
	 */
	static double getMoneyPerWatt();
	/**
	 * @brief Specifies the factor of money returned when selling buildings, if the player is connected with the transformer station.
	 */
	static double getSellRevenueConnected();
	/**
	 * @brief Specifies the factor of money returned when selling buildings, if the player is not connected with the transformer station.
	 */
	static double getSellRevenueDisconnected();
	/**
	 * @brief Money every player has at beginning.
	 */
	static int getDefaultMoney();
	/**
	 * @brief Number of fields in one row. The number of power plants will be derived from this value (fieldLength*fieldLength / 8).
	 */
	static int getFieldLength();

	//-----CityProperties----
	/**
	 * @brief Default population of the city.
	 */
	static int getStartPopulation();
	/**
	 * @brief Growth rate of the city in number of peoples per second.
	 */
	static int getPopulationGrowth();
	/**
	 * @brief Energy consumption of the city in watt per citizen.
	 */
	static double getConsumptionPerCitizen();
	/**
	 * @brief Maximum number of citizen in the city.
	 */
	static int getMaxPopulation();
	/**
	 * @brief Offset for placing the city on the map (relative from the top left corner for the first and bottom right corner for the second player).
	 */
	static int getMapOffset();
	/**
	 * @brief At this threshold the user gets warned about low energy.
	 */
	static int getSurplusWarningThreshold();

	//-----SabotageValues----
	/**
	 * @brief Costs for the different sabotage acts.
	 */
	static int getSabotageCost(const LSabotage::LSabotage sabotage);
	/**
	 * @brief Cooldown times fot the different sabotage acts.
	 */
	static int getSabotageCooldown(const LSabotage::LSabotage sabotage);
	/**
	 * @brief Cooldown time for a sabotaged power plant (time it is deactivated).
	 */
	static int getCooldownTimeReactivationPowerPlant();
	/**
	 * @brief Factor for resource sabotage.
	 */
	static float getFactorSabotageResource();
	/**
	 * @brief Amount of sabotage acts.
	 */
	static int getSabotageActs();

	//-----GeneralSettings----
	/**
	 * @brief Address of the adapter to use for outgoing connections.
	 */
	static std::string getLocalIpAddress();
};

NAMESPACE_LOGIC_E
