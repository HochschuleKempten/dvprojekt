#pragma once

#include "LGeneral.h"
#include "LUtility.h"

NAMESPACE_LOGIC_B

class ILBuilding;
class LPlayingField;
class LPowerLine;
class LCity;
class LCoalPowerPlant;
class LWindmillPowerPlant;
class LSolarPowerPlant;
class LTransformerStation;

class LField
{
	NON_COPYABLE(LField);

public:
	enum FieldType
	{
		CITY     = 0,
		WATER    = -1,
		AIR      = -2,
		SOLAR    = -3,
		GRASS    = -100,
		MOUNTAIN = -101,
		COAL     = 100,
		OIL      = 50
	};

	enum FieldLevel
	{
		LEVEL1 = 1,
		LEVEL2 = 2,
		LEVEL3 = 3
	};

private:
	ILBuilding* lBuilding = nullptr;
	LPlayingField* lPlayingField = nullptr;
	bool buildingPlaced = false;
	FieldType fieldType = GRASS;
	FieldLevel fieldLevel = LEVEL1;
	int energyStock = 0;
	int energyLeft = 0;

private:
	//TODO (All) where can power lines be placed? (grass, solar, ...)
	template<typename T> bool checkBuildingType()
	{
		ASSERT(false, "Unknown field type");
		return false;
	}
	template<> bool checkBuildingType<LCoalPowerPlant>()
	{
		return fieldType == COAL;
	}
	template<> bool checkBuildingType<LWindmillPowerPlant>()
	{
		return fieldType == AIR;
	}
	template<> bool checkBuildingType<LSolarPowerPlant>()
	{
		return fieldType == SOLAR;
	}
	template<> bool checkBuildingType<LCity>()
	{
		return fieldType == CITY;
	}
	template<> bool checkBuildingType<LPowerLine>()
	{
		return fieldType == GRASS;
	}

	template<> bool checkBuildingType<LTransformerStation>()
	{
		return fieldType == GRASS;
	}

public:
	LField();
	~LField();
	
	void init(const FieldType fieldType, const FieldLevel fieldLevel);

	template <typename T, typename... Args>
	bool setBuilding(const int x, const int y, const Args... arguments)
	{
		//TODO (L) introduce building names 
		if (buildingPlaced) {
			lPlayingField->getVPlayingField()->messageBuildingFailed(std::string("Ein ") + getClassName(T) +  std::string(" kann hier nicht platziert werden, da auf dem Feld ") + std::to_string(fieldType) +  std::string(" bereits ein Gebäude steht."));
			return false;
		}
		if (!checkBuildingType<T>()) {
			lPlayingField->getVPlayingField()->messageBuildingFailed(std::string("Ein ") + getClassName(T) + std::string(" kann nicht auf einem Feld vom Typ ") + std::to_string(fieldType) + std::string(" platziert werden"));
			return false;
		}

		lBuilding = new T(this, x, y, arguments...);
		buildingPlaced = true;
		return true;
	}

	// this must be called after construction of this object
	void setLPlayingField(LPlayingField* lPlayingField);
	FieldType getFieldType() const;
	FieldLevel getFieldLevel() const;
	bool removeBuilding();
	ILBuilding * getBuilding();
	void setIsPlacingAllowed(bool allowed);
	bool isPlacingAllowed();
	LPlayingField* getLPlayingField();
};

NAMESPACE_LOGIC_E
