#pragma once
#include "LGeneral.h"
#include "ILBuilding.h"
#include "LIdentifier.h"

NAMESPACE_LOGIC_B

class IVPowerLine;
class LRemoteOperation;

class LPowerLine : public ILBuilding
{
	friend class LRemoteOperation;
	friend class LMaster;

private:
	std::shared_ptr<IVPowerLine> vPowerLine;

public:
	// set orientation of the powerline with the bitwise operator (|) (example: PowerLineOrientation::NORTH|PowerLineOrientation::EAST)
	LPowerLine(LField* lField, const int x, const int y, const int orientation, const int playerId);
	virtual ~LPowerLine() override;

	void addDirection(const int direction);
	void removeDirection(const int direction);

	virtual bool checkSell() const override;
	virtual LIdentifier::LIdentifier getIdentifier() const override
	{
		return LIdentifier::LPowerLine;
	}

	virtual void setConnected(bool connected) override;
};

NAMESPACE_LOGIC_E
