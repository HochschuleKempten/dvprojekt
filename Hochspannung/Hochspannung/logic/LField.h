#pragma once

#include "LGeneral.h"
#include "LUtility.h"

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
	int energyStock = 0;
	int energyLeft = 0;

private:
	//TODO (All) where can power lines be placed? (grass, solar, ...)
	template<typename T> bool checkBuildingType()
	{
		ASSERT("Unknown field type");
		return false;
	}
	template<> bool checkBuildingType<LOilRefinery>()
	{
		return fieldType == OIL;
	}
	template<> bool checkBuildingType<LHydroelectricPowerPlant>()
	{
		return fieldType == WATER;
	}
	template<> bool checkBuildingType<LCoalPowerPlant>()
	{
		return fieldType == COAL;
	}
	template<> bool checkBuildingType<LNuclearPowerPlant>()
	{
		return fieldType == NUCLEAR;
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
	void setFieldType(FieldType fieldType);
	FieldLevel getFieldLevel() const;
	void setFieldLevel(FieldLevel fieldLevel);
	bool removeBuilding();
	ILBuilding * getBuilding();
	void setIsPlacingAllowed(bool allowed);
	bool isPlacingAllowed();
	LPlayingField* getLPlayingField();
};

NAMESPACE_LOGIC_E
