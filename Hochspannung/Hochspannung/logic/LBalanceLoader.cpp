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
		case LField::CITY: break;
		case LField::WATER: break;
		case LField::AIR: break;
		case LField::SOLAR: break;
		case LField::GRASS: break;
		case LField::MOUNTAIN: break;
		case LField::COAL: break;
		case LField::OIL: break;
		case LField::NUCLEAR: break;
		default: break;
	}

	return 0;
}

double LBalanceLoader::getMoneyPerWatt()
{
	ASSERT(initDone, "LBalanceLoader is not initialized");
	return 0.1;
}

double LBalanceLoader::getMoneyBackAmount()
{
	return 0.5;
}

std::unordered_map<LField::FieldType, double> LBalanceLoader::getFieldTypes()
{
	ASSERT(initDone, "LBalanceLoader is not initialized");
	std::unordered_map<LField::FieldType, double> fieldTypes;

	fieldTypes[LField::SOLAR] = 0.1;
	fieldTypes[LField::AIR] = 0.1;
	fieldTypes[LField::WATER] = 0.1;
	fieldTypes[LField::COAL] = 0.1;
	fieldTypes[LField::NUCLEAR] = 0.1;
	fieldTypes[LField::OIL] = 0.1;
	fieldTypes[LField::MOUNTAIN] = 0.4;

#ifdef _DEBUG
	double sum = 0.0;
	for (const auto& pair : fieldTypes) {
		sum += pair.second;
	}

	ASSERT(sum == 1.0, "Relations between field types are incorrect");
#endif //_DEBUG

	return fieldTypes;
}

std::vector<LField::FieldLevel> LBalanceLoader::getFieldLevels()
{
	ASSERT(initDone, "LBalanceLoader is not initialized");
	return {LField::LEVEL1, LField::LEVEL2, LField::LEVEL3};
}

NAMESPACE_LOGIC_E
