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
	catch (const boost::property_tree::ptree_error& error)
	{
		ASSERT("Can't read ini file" << error.what())
	}

	DEBUG_EXPRESSION(initDone = true);
}

int LBalanceLoader::getProducedEnergy(const LIdentifier::LIdentifier identifier)
{
	ASSERT(initDone, msgAssert);
	CATCH
	(
		switch (identifier)
		{
			case LIdentifier::LCoalPowerPlant:
				return propertyTree.get<int>("ProducedEnergy.CoalPowerPlant");
			case LIdentifier::LHydroelectricPowerPlant:
				return propertyTree.get<int>("ProducedEnergy.HydroelectricPowerPlant");
			case LIdentifier::LNuclearPowerPlant:
				return propertyTree.get<int>("ProducedEnergy.NuclearPowerPlant");
			case LIdentifier::LOilRefinery:
				return propertyTree.get<int>("ProducedEnergy.OilRefinery");
			case LIdentifier::LSolarPowerPlant:
				return propertyTree.get<int>("ProducedEnergy.SolarPowerPlant");
			case LIdentifier::LWindmillPowerPlant:
				return propertyTree.get<int>("ProducedEnergy.WindmillPowerPlant");
			default:
				//Every other building produces no energy
				return 0;
		}, boost::property_tree::ptree_error, ASSERT(e.what())
	);
}

int LBalanceLoader::getFieldStorage(const LField::FieldType fieldType)
{
	ASSERT(initDone, msgAssert);
	CATCH
	(
		switch (fieldType)
		{
			case LField::COAL:
				return propertyTree.get<int>("FieldStorage.Coal");
			case LField::OIL:
				return propertyTree.get<int>("FieldStorage.Oil");
			case LField::NUCLEAR:
				return propertyTree.get<int>("FieldStorage.Nuclear");
			default:
				//Every other field has no resources
				return 0;
		}, boost::property_tree::ptree_error, ASSERT(e.what())
	);
}

int LBalanceLoader::getConsumedResources(const LField::FieldType fieldType)
{
	ASSERT(initDone, msgAssert);
	CATCH
	(
		switch (fieldType)
		{
			case LField::COAL:
				return propertyTree.get<int>("ConsumedResources.Coal");
			case LField::OIL:
				return propertyTree.get<int>("ConsumedResources.Oil");
			case LField::NUCLEAR:
				return propertyTree.get<int>("ConsumedResources.Nuclear");
			default:
				ASSERT("Requested fossil field type is not available");
				return 0;
		}, boost::property_tree::ptree_error, ASSERT(e.what())
	);
}

std::unordered_map<LField::FieldType, double> LBalanceLoader::getFieldTypeRatio()
{
	ASSERT(initDone, msgAssert);
	std::unordered_map<LField::FieldType, double> fieldTypes;
	CATCH
	(
		fieldTypes[LField::SOLAR] = propertyTree.get<double>("FieldTypeRatio.Solar");
		fieldTypes[LField::AIR] = propertyTree.get<double>("FieldTypeRatio.Air");
		fieldTypes[LField::WATER] = propertyTree.get<double>("FieldTypeRatio.Water");
		fieldTypes[LField::COAL] = propertyTree.get<double>("FieldTypeRatio.Coal");
		fieldTypes[LField::NUCLEAR] = propertyTree.get<double>("FieldTypeRatio.Nuclear");
		fieldTypes[LField::OIL] = propertyTree.get<double>("FieldTypeRatio.Oil");
		fieldTypes[LField::MOUNTAIN] = propertyTree.get<double>("FieldTypeRatio.Mountain");
		, boost::property_tree::ptree_error, ASSERT(e.what())
	);

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
	CATCH
	(
		fieldLevels[LField::LEVEL1] = propertyTree.get<double>("FieldLevelFactor.Level1");
		fieldLevels[LField::LEVEL2] = propertyTree.get<double>("FieldLevelFactor.Level2");
		fieldLevels[LField::LEVEL3] = propertyTree.get<double>("FieldLevelFactor.Level3");
		, boost::property_tree::ptree_error, ASSERT(e.what())
	);

	return fieldLevels;
}

double LBalanceLoader::getMoneyPerWatt()
{
	ASSERT(initDone, msgAssert);
	CATCH(return propertyTree.get<double>("DifficultyScale.MoneyPerWatt"), boost::property_tree::ptree_error, ASSERT(e.what()));
}

double LBalanceLoader::getSellRevenueConnected()
{
	ASSERT(initDone, msgAssert);
	CATCH(return propertyTree.get<double>("DifficultyScale.SellRevenueConnected"), boost::property_tree::ptree_error, ASSERT(e.what()));
}

double LBalanceLoader::getSellRevenueDisconnected()
{
	ASSERT(initDone, msgAssert);
	CATCH(return propertyTree.get<double>("DifficultyScale.SellRevenueDisconnected"), boost::property_tree::ptree_error, ASSERT(e.what()));
}

int LBalanceLoader::getDefaultMoney()
{
	ASSERT(initDone, msgAssert);
	CATCH(return propertyTree.get<int>("DifficultyScale.DefaultMoney"), boost::property_tree::ptree_error, ASSERT(e.what()));
}

int LBalanceLoader::getFieldLength()
{
	ASSERT(initDone, msgAssert);
	CATCH(return propertyTree.get<int>("DifficultyScale.FieldLength"), boost::property_tree::ptree_error, ASSERT(e.what()));
}

double LBalanceLoader::getSabotageDiscountDisconnected()
{
	ASSERT(initDone, msgAssert);
	CATCH(return propertyTree.get<double>("CityProperties.SabotageDiscountDisconnected"), boost::property_tree::ptree_error, ASSERT(e.what()));
}

int LBalanceLoader::getStartPopulation()
{
	ASSERT(initDone, msgAssert);
	CATCH(return propertyTree.get<int>("CityProperties.StartPopulation"), boost::property_tree::ptree_error, ASSERT(e.what()));
}

int LBalanceLoader::getPopulationGrowth()
{
	ASSERT(initDone, msgAssert);
	CATCH(return propertyTree.get<int>("CityProperties.PopulationGrowth"), boost::property_tree::ptree_error, ASSERT(e.what()));
}

double LBalanceLoader::getConsumptionPerCitizen()
{
	ASSERT(initDone, msgAssert);
	CATCH(return propertyTree.get<double>("CityProperties.ConsumptionPerCitizen"), boost::property_tree::ptree_error, ASSERT(e.what()));
}

int LBalanceLoader::getMaxPopulation()
{
	ASSERT(initDone, msgAssert);
	CATCH(return propertyTree.get<int>("CityProperties.MaxPopulation"), boost::property_tree::ptree_error, ASSERT(e.what()));
}

int LBalanceLoader::getMapOffset()
{
	ASSERT(initDone, msgAssert);
	CATCH(return propertyTree.get<int>("CityProperties.MapOffset"), boost::property_tree::ptree_error, ASSERT(e.what()));
}

int LBalanceLoader::getSurplusWarningThreshold()
{
	ASSERT(initDone, msgAssert);
	CATCH(return propertyTree.get<int>("CityProperties.SurplusWarningThreshold"), boost::property_tree::ptree_error, ASSERT(e.what()));
}

int LBalanceLoader::getSabotageCost(const LSabotage::LSabotage sabotage)
{
	ASSERT(initDone, msgAssert);
	CATCH(
		switch (sabotage)
		{
			case LSabotage::Deactivate: return propertyTree.get<int>("SabotageValues.CostDeactivate");
			case LSabotage::Resource: return propertyTree.get<int>("SabotageValues.CostResource");
			case LSabotage::Remove: return propertyTree.get<int>("SabotageValues.CostRemove");
			default:
				ASSERT("Requested sabotage is not available");
				return 0;
		}, boost::property_tree::ptree_error, ASSERT(e.what());
	)
}

int LBalanceLoader::getSabotageCooldown(const LSabotage::LSabotage sabotage)
{
	ASSERT(initDone, msgAssert);
	CATCH(
		switch (sabotage)
		{
			case LSabotage::Deactivate: return propertyTree.get<int>("SabotageValues.CooldownTimeToNextDeactivate");
			case LSabotage::Resource: return propertyTree.get<int>("SabotageValues.CooldownTimeToNextResource");
			case LSabotage::Remove: return propertyTree.get<int>("SabotageValues.CooldownTimeToNextRemove");
			default:
				ASSERT("Requested sabotage is not available");
				return 0;
		}, boost::property_tree::ptree_error, ASSERT(e.what());
	)
}

float LBalanceLoader::getFactorSabotageResource()
{
	ASSERT(initDone, msgAssert);
	CATCH(return propertyTree.get<float>("SabotageValues.FactorSabotageResource"), boost::property_tree::ptree_error, ASSERT(e.what()));
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

std::vector<std::string> LBalanceLoader::getDefaultRemoteAddresses()
{
	ASSERT(initDone, msgAssert);

	std::string addresses = propertyTree.get<std::string>("GeneralSettings.DefaultRemoteAddresses", "");
	return split(addresses, ';');
}

NAMESPACE_LOGIC_E
