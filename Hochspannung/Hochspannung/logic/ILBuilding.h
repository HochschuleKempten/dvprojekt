#pragma once
#include "LGeneral.h"
#include "LPlayer.h"

NAMESPACE_LOGIC_B


class LField;

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

	static Orientation getOpppositeOrienttion(const Orientation orientation)
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

	//todo (L) Später max. Ausbaustufe und aktuelle, Spielerzuweisung
protected:
	LField* lField;
	int playerId = LPlayer::PlayerId::Local;
	int orientation;

public:
	explicit ILBuilding(LField* lField)
		: lField(lField)
	{}

	virtual ~ILBuilding()
	{}

	//todo (L) implement this in the buildings that can be upgraded
	virtual void upgrade() 
	{}

	virtual int getOrientation() const
	{
		return NORTH | EAST | SOUTH | WEST;
	}

	void setPlayerId(const int playerId)
	{
		this->playerId = playerId;
	}

	int getPlayerId() const
	{
		return playerId;
	}
};


NAMESPACE_LOGIC_E
