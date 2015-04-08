#pragma once

class ILBuilding;
class LPlayingField;

class LField
{
private:
	ILBuilding* lBuilding;
	LPlayingField* lPlayingField;
	bool placingAllowed;

public:
	// initializes this field with isPlacingAllowed = true!
	LField(LPlayingField* lPlayingField);
	~LField();

	template <typename T>
	bool setBuilding(const int x, const int y)
	{
		if (placingAllowed)
		{
			lBuilding = new T(100, 20, this, x, y); //TODO (IP) where should cost and energy values come from? 
			return true;
		}

		return false;
	}

	bool removeBuilding();
	ILBuilding * getBuilding();
	void setIsPlacingAllowed(bool allowed);
	bool isPlacingAllowed();
	LPlayingField* getLPlayingField();
};
