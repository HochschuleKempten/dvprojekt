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

	//todo (L) Später max. Ausbaustufe und aktuelle, Spielerzuweisung
protected:
	LField* lField;
	LPlayer::PlayerId playerId = LPlayer::PlayerId::Local;
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

	static const int cost = 10;

	void setPlayerId(const LPlayer::PlayerId playerId)
	{
		this->playerId = playerId;
	}

	LPlayer::PlayerId getPlayerId() const
	{
		return playerId;
	}
};


NAMESPACE_LOGIC_E
