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
	LField();
	~LField();

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
	bool removeBuilding();
	ILBuilding * getBuilding();
	void setIsPlacingAllowed(bool allowed);
	bool isPlacingAllowed();
	LPlayingField* getLPlayingField();
};
