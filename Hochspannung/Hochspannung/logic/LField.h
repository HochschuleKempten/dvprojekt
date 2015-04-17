#pragma once

#include "LGeneral.h"
#include "LUtility.h"

NAMESPACE_LOGIC_B

class ILBuilding;
class LPlayingField;
class LPowerLine;
class LCity;
class LCoalPowerPlant;

class LField
{
public:
	enum FieldType
	{
		CITY     = 0,
		WATER    = -1,
		GRASS    = -2,
		MOUNTAIN = -3,
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
	template<typename T>
	bool checkBuildingType()
	{
		ASSERT(false, "Unknown field type");
	}
	template<>
	bool checkBuildingType<LCoalPowerPlant>()
	{
		return fieldType == COAL;
	}
	template<>
	bool checkBuildingType<LCity>()
	{
		return fieldType == CITY;
	}
	template<>
	bool checkBuildingType<LPowerLine>()
	{
		return fieldType == GRASS;
	}

public:

	// initializes this field with isPlacingAllowed = true!
	LField();
	~LField();
	
	void init(const FieldType fieldType, const FieldLevel fieldLevel);

	template <typename T, typename... Args>
	bool setBuilding(const int x, const int y, const Args... arguments)
	{
		//TODO (ALL) How to inform UI that building can not be placed (building exists or building not possible)
		if (!buildingPlaced && checkBuildingType<T>())
		{
			lBuilding = new T(this, x, y, arguments...);
			buildingPlaced = true;
			return true;
		}

		return false;
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
