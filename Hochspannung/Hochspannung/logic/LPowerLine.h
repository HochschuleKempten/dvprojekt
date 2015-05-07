#pragma once
#include "LGeneral.h"
#include "ILBuilding.h"
#include "LIdentifier.h"

NAMESPACE_LOGIC_B

class IVPowerLine;

class LPowerLine : public ILBuilding
{
private:
	std::shared_ptr<IVPowerLine> vPowerLine;

public:
	// set orientation of the powerline with the bitwise operator (|) (example: PowerLineOrientation::NORTH|PowerLineOrientation::EAST)
	LPowerLine(LField* lField, const int x, const int y, const int orientation, const int playerId);
	virtual ~LPowerLine() override;

	void updatedOrientation(const int additionalOrientation);

	virtual LIdentifier::LIdentifier getIdentifier() override
	{
		return LIdentifier::LPowerLine;
	}

	virtual int getOrientation() const override
	{
		return orientation;
	}
};

NAMESPACE_LOGIC_E