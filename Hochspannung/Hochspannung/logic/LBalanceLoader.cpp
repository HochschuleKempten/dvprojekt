#include "LBalanceLoader.h"
#include <fstream>

NAMESPACE_LOGIC_B

DEBUG_EXPRESSION(bool LBalanceLoader::initDone = false);
boost::property_tree::ptree LBalanceLoader::propertyTree;

void LBalanceLoader::init()
{
	DEBUG_EXPRESSION(initDone = true);
	try {
		boost::property_tree::read_ini("logic\\Balancing.ini", propertyTree);
	} catch (boost::property_tree::ptree_error error) {
		DEBUG_OUTPUT(error.what())
	}

}

int LBalanceLoader::getFieldStorage(const LField::FieldType fieldType)
{
	ASSERT(initDone, "LBalanceLoader is not initialized");

	switch (fieldType) {
		case LField::COAL:
			return propertyTree.get<int>("FieldStorage.Coal", 0);
		case LField::OIL:
			return propertyTree.get<int>("FieldStorage.Oil", 0);
		case LField::NUCLEAR:
			return propertyTree.get<int>("FieldStorage.Nuclear", 0);
		default:
			return 0;
	}
}

double LBalanceLoader::getMoneyPerWatt()
{
	ASSERT(initDone, "LBalanceLoader is not initialized");
	return propertyTree.get<double>("DifficultyScale.MoneyPerWatt", 0.0);
}

double LBalanceLoader::getSellRevenue()
{
	ASSERT(initDone, "LBalanceLoader is not initialized");
	return propertyTree.get<double>("DifficultyScale.SellRevenue", 0.0);
}

std::unordered_map<LField::FieldType, double> LBalanceLoader::getFieldTypeRatio()
{
	ASSERT(initDone, "LBalanceLoader is not initialized");
	std::unordered_map<LField::FieldType, double> fieldTypes;

	fieldTypes[LField::SOLAR]    = propertyTree.get<double>("FieldTypeRatio.Solar", 0.0);
	fieldTypes[LField::AIR]      = propertyTree.get<double>("FieldTypeRatio.Air", 0.0);
	fieldTypes[LField::WATER]    = propertyTree.get<double>("FieldTypeRatio.Water", 0.0);
	fieldTypes[LField::COAL]     = propertyTree.get<double>("FieldTypeRatio.Coal", 0.0);
	fieldTypes[LField::NUCLEAR]  = propertyTree.get<double>("FieldTypeRatio.Nuclear", 0.0);
	fieldTypes[LField::OIL]      = propertyTree.get<double>("FieldTypeRatio.Oil", 0.0);
	fieldTypes[LField::MOUNTAIN] = propertyTree.get<double>("FieldTypeRatio.Mountain", 0.0);

#ifdef _DEBUG
	double sum = 0.0;
	for (const auto& pair : fieldTypes) {
		sum += pair.second;
	}

	ASSERT(sum == 1.0, "Relations between field types are incorrect");
#endif //_DEBUG

	return fieldTypes;
}

std::unordered_map<LField::FieldLevel, double> LBalanceLoader::getFieldLevelFactor()
{
	ASSERT(initDone, "LBalanceLoader is not initialized");
	std::unordered_map<LField::FieldLevel, double> fieldLevels;

	fieldLevels[LField::LEVEL1] = propertyTree.get<double>("FieldLevelFactor.Level1", 0.0);
	fieldLevels[LField::LEVEL2] = propertyTree.get<double>("FieldLevelFactor.Level2", 0.0);
	fieldLevels[LField::LEVEL3] = propertyTree.get<double>("FieldLevelFactor.Level3", 0.0);

	return fieldLevels;
}

int LBalanceLoader::getPopulationGrowth()
{
	ASSERT(initDone, "LBalanceLoader is not initialized");
	return propertyTree.get<int>("CityProperties.PopulationGrowth", 0);
}

double LBalanceLoader::getConsumptionPerCitizen()
{
	ASSERT(initDone, "LBalanceLoader is not initialized");
	return propertyTree.get<double>("CityProperties.ConsumptionPerCitizen", 0.0);
}

int LBalanceLoader::getStartPopulation()
{
	ASSERT(initDone, "LBalanceLoader is not initialized");
	return propertyTree.get<int>("CityProperties.StartPopulation", 0);
}

NAMESPACE_LOGIC_E
