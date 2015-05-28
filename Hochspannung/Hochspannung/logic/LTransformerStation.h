#pragma once

#include "ILBuilding.h"
#include "IVTickObserver.h"

NAMESPACE_LOGIC_B


class IVTransformerStation;

class LTransformerStation : public ILBuilding, public IVTickObserver
{
private:
	
	std::shared_ptr<IVTransformerStation> vTransformerSation;
	bool hasConnection;

public:
	LTransformerStation(LField* lField, const int x, const int y, const int playerId);
	~LTransformerStation();

	virtual void tick(const float fTimeDelta) override;

	void performDisposal();

	virtual LIdentifier::LIdentifier getIdentifier() const override
	{
		return LIdentifier::LTransformerStation;
	}
};

NAMESPACE_LOGIC_E
