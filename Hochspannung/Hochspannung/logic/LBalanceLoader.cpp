#include "LBalanceLoader.h"
#include <boost\property_tree\ini_parser.hpp>
#include "LUtility.h"

NAMESPACE_LOGIC_B

boost::property_tree::ptree LBalanceLoader::propertyTree;
DEBUG_EXPRESSION(bool LBalanceLoader::initDone = false);
DEBUG_EXPRESSION(static const char* const msgAssert = "LBalanceLoader is not initialized");

void LBalanceLoader::init()
{
	try
	{
		boost::property_tree::read_ini("logic\\Balancing.ini", propertyTree);
	}
	catch (boost::property_tree::ptree_error error)
	{
		ASSERT("Can't read ini file" << error.what())
	}

	DEBUG_EXPRESSION(initDone = true);
}

int LBalanceLoader::getProducedEnergy(const LIdentifier::LIdentifier identifier)
{
	ASSERT(initDone, msgAssert);

	switch (identifier)
	{
		case LIdentifier::LCoalPowerPlant:
			return propertyTree.get<int>("ProducedEnergy.CoalPowerPlant", 0);
		case LIdentifier::LHydroelectricPowerPlant:
			return propertyTree.get<int>("ProducedEnergy.HydroelectricPowerPlant", 0);
		case LIdentifier::LNuclearPowerPlant:
			return propertyTree.get<int>("ProducedEnergy.NuclearPowerPlant", 0);
		case LIdentifier::LOilRefinery:
			return propertyTree.get<int>("ProducedEnergy.OilRefinery", 0);
		case LIdentifier::LSolarPowerPlant:
			return propertyTree.get<int>("ProducedEnergy.SolarPowerPlant", 0);
		case LIdentifier::LWindmillPowerPlant:
			return propertyTree.get<int>("ProducedEnergy.WindmillPowerPlant", 0);
		default:
			//Every other building produces no energy
			return 0;
	}
}

int LBalanceLoader::getFieldStorage(const LField::FieldType fieldType)
{
	ASSERT(initDone, msgAssert);

	switch (fieldType)
	{
		case LField::COAL:
			return propertyTree.get<int>("FieldStorage.Coal", 0);
		case LField::OIL:
			return propertyTree.get<int>("FieldStorage.Oil", 0);
		case LField::NUCLEAR:
			return propertyTree.get<int>("FieldStorage.Nuclear", 0);
		default:
			//Every other field has no resources
			return 0;
	}
}

int LBalanceLoader::getConsumedResources(const LField::FieldType fieldType)
{
	ASSERT(initDone, msgAssert);

	switch (fieldType)
	{
		case LField::COAL:
			return propertyTree.get<int>("ConsumedResources.Coal", 0);
		case LField::OIL:
			return propertyTree.get<int>("ConsumedResources.Oil", 0);
		case LField::NUCLEAR:
			return propertyTree.get<int>("ConsumedResources.Nuclear", 0);
		default:
			ASSERT("Requested fossil field type is not available");
			return 0;
	}
}

std::unordered_map<LField::FieldType, double> LBalanceLoader::getFieldTypeRatio()
{
	ASSERT(initDone, msgAssert);
	std::unordered_map<LField::FieldType, double> fieldTypes;

	fieldTypes[LField::SOLAR] = propertyTree.get<double>("FieldTypeRatio.Solar", 0.0);
	fieldTypes[LField::AIR] = propertyTree.get<double>("FieldTypeRatio.Air", 0.0);
	fieldTypes[LField::WATER] = propertyTree.get<double>("FieldTypeRatio.Water", 0.0);
	fieldTypes[LField::COAL] = propertyTree.get<double>("FieldTypeRatio.Coal", 0.0);
	fieldTypes[LField::NUCLEAR] = propertyTree.get<double>("FieldTypeRatio.Nuclear", 0.0);
	fieldTypes[LField::OIL] = propertyTree.get<double>("FieldTypeRatio.Oil", 0.0);
	fieldTypes[LField::MOUNTAIN] = propertyTree.get<double>("FieldTypeRatio.Mountain", 0.0);

#ifdef _DEBUG
	double sum = 0.0;
	for (const auto& pair : fieldTypes)
	{
		sum += pair.second;
	}

	ASSERT(almost_equal(sum, 1.0, 2) == true, "Relations between field types are incorrect");
#endif //_DEBUG


	return fieldTypes;
}

std::unordered_map<LField::FieldLevel, double> LBalanceLoader::getFieldLevelFactor()
{
	ASSERT(initDone, msgAssert);
	std::unordered_map<LField::FieldLevel, double> fieldLevels;

	fieldLevels[LField::LEVEL1] = propertyTree.get<double>("FieldLevelFactor.Level1", 0.0);
	fieldLevels[LField::LEVEL2] = propertyTree.get<double>("FieldLevelFactor.Level2", 0.0);
	fieldLevels[LField::LEVEL3] = propertyTree.get<double>("FieldLevelFactor.Level3", 0.0);

	return fieldLevels;
}

double LBalanceLoader::getMoneyPerWatt()
{
	ASSERT(initDone, msgAssert);
	return propertyTree.get<double>("DifficultyScale.MoneyPerWatt", 0.0);
}

double LBalanceLoader::getSellRevenueConnected()
{
	ASSERT(initDone, msgAssert);
	return propertyTree.get<double>("DifficultyScale.SellRevenueConnected", 0.0);
}

double LBalanceLoader::getSellRevenueDisconnected()
{
	ASSERT(initDone, msgAssert);
	return propertyTree.get<double>("DifficultyScale.SellRevenueDisconnected", 0.0);
}

int LBalanceLoader::getDefaultMoney()
{
	ASSERT(initDone, msgAssert);
	return propertyTree.get<int>("DifficultyScale.DefaultMoney", 0);
}

int LBalanceLoader::getFieldLength()
{
	ASSERT(initDone, msgAssert);
	return propertyTree.get<int>("DifficultyScale.FieldLength", 0);
}

int LBalanceLoader::getStartPopulation()
{
	ASSERT(initDone, msgAssert);
	return propertyTree.get<int>("CityProperties.StartPopulation", 0);
}

int LBalanceLoader::getPopulationGrowth()
{
	ASSERT(initDone, msgAssert);
	return propertyTree.get<int>("CityProperties.PopulationGrowth", 0);
}

double LBalanceLoader::getConsumptionPerCitizen()
{
	ASSERT(initDone, msgAssert);
	return propertyTree.get<double>("CityProperties.ConsumptionPerCitizen", 0.0);
}

int LBalanceLoader::getMaxPopulation()
{
	ASSERT(initDone, msgAssert);
	return propertyTree.get<int>("CityProperties.MaxPopulation", 0);
}

int LBalanceLoader::getMapOffset()
{
	ASSERT(initDone, msgAssert);
	return propertyTree.get<int>("CityProperties.MapOffset", 0);
}

int LBalanceLoader::getSurplusWarningThreshold()
{
	ASSERT(initDone, msgAssert);
	return propertyTree.get<int>("CityProperties.SurplusWarningThreshold", 0);
}

int LBalanceLoader::getSabotageCost(const LSabotage::LSabotage sabotage)
{
	ASSERT(initDone, msgAssert);

	switch (sabotage)
	{
		case LSabotage::Deactivate: return propertyTree.get<int>("SabotageValues.CostDeactivate", 0);
		case LSabotage::Resource: return propertyTree.get<int>("SabotageValues.CostResource", 0);
		case LSabotage::Remove: return propertyTree.get<int>("SabotageValues.CostRemove", 0);
		default:
			ASSERT("Requested sabotage is not available");
			return 0;
	}
}

int LBalanceLoader::getSabotageCooldown(const LSabotage::LSabotage sabotage)
{
	ASSERT(initDone, msgAssert);

	switch (sabotage)
	{
		case LSabotage::Deactivate: return propertyTree.get<int>("SabotageValues.CooldownTimeToNextDeactivate", 0);
		case LSabotage::Resource: return propertyTree.get<int>("SabotageValues.CooldownTimeToNextResource", 0);
		case LSabotage::Remove: return propertyTree.get<int>("SabotageValues.CooldownTimeToNextRemove", 0);
		default:
			ASSERT("Requested sabotage is not available");
			return 0;
	}
}

int LBalanceLoader::getCooldownTimeReactivationPowerPlant()
{
	ASSERT(initDone, msgAssert);
	return propertyTree.get<int>("SabotageValues.CooldownTimeReactivationPowerPlant", 0);
}

float LBalanceLoader::getFactorSabotageResource()
{
	ASSERT(initDone, msgAssert);
	return propertyTree.get<float>("SabotageValues.FactorSabotageResource", 0);
}

int LBalanceLoader::getSabotageActs()
{
	ASSERT(initDone, msgAssert);
	CATCH(return propertyTree.get<int>("SabotageValues.SabotageActs"), boost::property_tree::ptree_error, ASSERT(e.what()));
}

std::string LBalanceLoader::getLocalIpAddress()
{
	ASSERT(initDone, msgAssert);
	return propertyTree.get<std::string>("GeneralSettings.LocalIpAddress", "0.0.0.0");
}

NAMESPACE_LOGIC_E
