#pragma once
#include "ILBuilding.h"
#include "IVTickObserver.h"

NAMESPACE_LOGIC_B


class IVTransformerStation;

class LTransformerStation : public ILBuilding, public IVTickObserver
	{
private:
	// TODO(MBR) what private members are needed?
	std::shared_ptr<IVTransformerStation> vTransformerSation;
	bool hasConnection;

public:
	LTransformerStation(LField* lField, const int x, const int y);
	~LTransformerStation();

	virtual void tick(const float fTimeDelta) override;
	// TODO(MBR) what methods are needed (also see IVTransformerStation)?

	void performDisposal();
 };
};
