#pragma once

#include "LGeneral.h"
#include "LUtility.h"
#include "LIdentifier.h"
#include "LMessageLoader.h"

NAMESPACE_LOGIC_B

class ILBuilding;
class LPlayingField;
class LCity;
class LTransformerStation;
class LPowerLine;
class LWindmillPowerPlant;
class LSolarPowerPlant;
class LHydroelectricPowerPlant;
class LCoalPowerPlant;
class LOilRefinery;
class LNuclearPowerPlant;

class LField
{
	NON_COPYABLE(LField);

public:
	enum FieldType 
	{
		CITY     = 0,
		WATER    = 1,
		AIR      = 2,
		SOLAR    = 3,
		GRASS    = 4,
		MOUNTAIN = 5,
		COAL     = 6,
		OIL      = 7,
		NUCLEAR  = 8
	};

	enum FieldLevel
	{
		LEVEL1 = 20,
		LEVEL2 = 21,
		LEVEL3 = 22
	};

private:
	ILBuilding* lBuilding = nullptr;
	LPlayingField* lPlayingField = nullptr;
	bool buildingPlaced = false;
	FieldType fieldType = GRASS;
	FieldLevel fieldLevel = LEVEL1;
	int resourceStock = 0;
	int resourceLeft = 0;
	int x = -1;
	int y = -1;

private:
	template<typename T> bool checkBuildingType()
	{
		ASSERT("Unknown field type");
		return false;
	}
	template<> bool checkBuildingType<LOilRefinery>()             { return fieldType == OIL; }
	template<> bool checkBuildingType<LHydroelectricPowerPlant>() {	return fieldType == WATER; }
	template<> bool checkBuildingType<LCoalPowerPlant>()          { return fieldType == COAL; }
	template<> bool checkBuildingType<LNuclearPowerPlant>()	      { return fieldType == NUCLEAR; }
	template<> bool checkBuildingType<LWindmillPowerPlant>()      { return fieldType == AIR; }
	template<> bool checkBuildingType<LSolarPowerPlant>()         { return fieldType == SOLAR; }
	template<> bool checkBuildingType<LCity>()                    { return fieldType == CITY; }
	template<> bool checkBuildingType<LPowerLine>()               { return fieldType == GRASS; }
	template<> bool checkBuildingType<LTransformerStation>()      { return fieldType == GRASS; }

public:
	LField();
	~LField();
	
	void init(const FieldType fieldType, const FieldLevel fieldLevel);

	template <typename T, typename... Args>
	bool setBuilding(const Args... arguments)
	{
		if (buildingPlaced) {
			LMessageLoader::emitMessage(LMessageLoader::BUILD_FIELD_OCCUPIED, { LMessageLoader::getNameForType<T>(), std::to_string(fieldType) });
			return false;
		}
		if (!checkBuildingType<T>()) {
			LMessageLoader::emitMessage(LMessageLoader::BUILD_FIELD_WRONG_TYPE, { LMessageLoader::getNameForType<T>(), std::to_string(fieldType) });
			return false;
		}

		lBuilding = new T(this, x, y, arguments...);
		buildingPlaced = true;
		return true;
	}

	// this must be called after construction of this object
	void setInitialValues(LPlayingField* lPlayingField, const int x, const int y);
	FieldType getFieldType() const;
	FieldLevel getFieldLevel() const;
	int getBuildingId() const;
	bool removeBuilding(const std::function<void(const ILBuilding* const)>& fnBeforeDelete = nullptr);
	ILBuilding * getBuilding();
	void setIsPlacingAllowed(const bool allowed);
	bool isPlacingAllowed();
	LPlayingField* getLPlayingField();
	int getResources() const;
	int deductResources();
	int reduceResources(const int amount);

	int getX() const
	{
		return x;
	}
	int getY() const
	{
		return y;
	}
	std::pair<int, int> getCoordinates() const
	{
		return std::make_pair(x, y);
	}
};

NAMESPACE_LOGIC_E
