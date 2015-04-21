#pragma once
#include "LGeneral.h"

NAMESPACE_LOGIC_B


class LField;

class ILBuilding
{
	//todo (L) Später max. Ausbaustufe und aktuelle, Spielerzuweisung
protected:
	LField* lField;
	LPlayer::PlayerNumber playerNumber;

public:
	ILBuilding(LField* lField)
		: lField(lField)
	{}

	virtual ~ILBuilding()
	{}

	//todo (L) implement this in the buildings that can be upgraded
	virtual void upgrade() 
	{}

	static const int cost = 10;

	void setPlayerNumber(const LPlayer::PlayerNumber playerNumber)
	{
		this->playerNumber = playerNumber;
	}

	LPlayer::PlayerNumber getPlayerNumber() const //todo (L) const everywhere where needed
	{
		return playerNumber;
	}
};


NAMESPACE_LOGIC_E
