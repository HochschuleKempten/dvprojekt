# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LWindmillPowerPlant.h"
#include "../logic/IVTickObserver.h"
#include "IViewBuilding.h"
#include "VModelWindmillPowerPlant.h"

NAMESPACE_VIEW_B


class VWindmillPowerPlant : public IVPowerPlant, public IViewBuilding, public IVTickObserver
{
private:
	VModelWindmillPowerPlant m_zp;

public:
	VWindmillPowerPlant(VMaster *vMaster, LWindmillPowerPlant* lPlant);
    virtual ~VWindmillPowerPlant()
	{}

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y);
     
	inline virtual void tick(const float fTimeDelta)
	{
		const double sec = 2.0;	//Number of seconds per rotation
		m_zp.rotate(static_cast<float>((2.0 * M_PI / sec) * fTimeDelta));
	}
};


NAMESPACE_VIEW_E
