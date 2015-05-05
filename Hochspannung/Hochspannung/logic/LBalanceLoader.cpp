#include "LBalanceLoader.h"

NAMESPACE_LOGIC_B


void LBalanceLoader::init()
{}

int LBalanceLoader::getFieldStorage(const LField::FieldType fieldType)
{
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
	return 0.1;
}

NAMESPACE_LOGIC_E
