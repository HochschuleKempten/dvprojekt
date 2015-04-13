#pragma once

class ILBuilding;
class LPlayingField;

class LField
{
public:
	enum FieldType
	{
		CITY     = 0,
		WATER    = -1,
		GRASS    = -1,
		MOUNTAIN = 0,
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
	ILBuilding* lBuilding;
	LPlayingField* lPlayingField;
	bool placingAllowed;
	FieldType fieldType;
	FieldLevel fieldLevel;
	int energyStock;
	int energyLeft;

public:

	// initializes this field with isPlacingAllowed = true!
	LField();
	~LField();
	
	void init(const FieldType fieldType, const FieldLevel fieldLevel);

	template <typename T, typename... Args>
	bool setBuilding(const int x, const int y, const Args... arguments)
	{
		if (placingAllowed)
		{
			lBuilding = new T(100, 20, this, x, y, arguments...); //TODO (IP) where should cost and energy values come from? -> IP: will be saved as static const values in the classes
			placingAllowed = false;
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
