#pragma once

#include "../logic/IVTransformerStation.h"
#include "IViewBuilding.h"

NAMESPACE_VIEW_B


class LTransformerStation;

class VTransformerStation : public IVTransformerStation, public IViewBuilding
{
private:
	CPlacement m_zp;
	CGeoCube m_zg;

public:
	VTransformerStation(VMaster *vMaster, LTransformerStation* lTransformerStation);
	virtual ~VTransformerStation() override;

	virtual void initTransformerStation(const std::shared_ptr<IVTransformerStation>& objPtr, const int x, const int y) override;
	virtual ILBuilding* getLBuilding() override;

};


NAMESPACE_VIEW_E
