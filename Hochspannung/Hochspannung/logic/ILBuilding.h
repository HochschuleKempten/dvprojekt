#pragma once

#include "LGeneral.h"
#include "LPlayer.h"
#include "LIdentifier.h"

NAMESPACE_LOGIC_B

class ILBuilding
{
	NON_COPYABLE(ILBuilding);

public:
	enum Orientation
	{
		NORTH = 0x1,
		EAST = 0x2,
		SOUTH = 0x4,
		WEST = 0x8
	};

	static Orientation getOpppositeOrientation(const Orientation orientation)
	{
		switch (orientation) {
			case NORTH: return SOUTH;
			case EAST: return WEST;
			case SOUTH: return NORTH;
			case WEST: return EAST;
			default:
				ASSERT("Invalid orientation given");
				return CASTS<Orientation>(0);
		}
	}

	static std::string getOrientationName(const int orientation)
	{
		std::string name = "";

		if (orientation & Orientation::NORTH) {
			name += "North ";
		}
		if (orientation & Orientation::EAST) {
			name += "East ";
		}
		if (orientation & Orientation::SOUTH) {
			name += "South ";
		}
		if (orientation & Orientation::WEST) {
			name += "West ";
		}

		return name;
	}

protected:
	LField* lField = nullptr;
	int playerId = LPlayer::PlayerId::Local;
	int orientation = 0;
	/** @brief Stores the total value of the building (initCost + upgradeCost etc) */
	int value = 0;

public:
	ILBuilding(LField* lField, const int playerId)
		: lField(lField), playerId(playerId), orientation(NORTH | EAST | SOUTH | WEST)
	{}
	ILBuilding(LField* lField, const int playerId, const int orientation)
		: lField(lField), playerId(playerId), orientation(orientation)
	{}

	virtual ~ILBuilding()
	{}

	//todo (L) implement this in the buildings that can be upgraded
	virtual void upgrade()
	{}

	int getOrientation() const
	{
		return orientation;
	}

	int getPlayerId() const
	{
		return playerId;
	}

	int getValue() const
	{
		return value;
	}

	void addValue(const int value)
	{
		this->value += value;
	}

	LField* getLField() const
	{
		return lField;
	}

	void sabotageRemove();
		
	virtual LIdentifier::LIdentifier getIdentifier() const = 0;
};


NAMESPACE_LOGIC_E
