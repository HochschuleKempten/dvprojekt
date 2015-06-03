#pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LCoalPowerPlant.h"
#include "../logic/IVTickObserver.h"
#include "VMaster.h"
#include "IViewPowerPlant.h"
#include "VModelCoalPowerPlant.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


class VCoalPowerPlant : public IViewPowerPlant, public IVTickObserver
{
private:
	VModelCoalPowerPlant viewModel;
	float timeLastCheck = 0;

public:
	VCoalPowerPlant(VMaster* vMaster, LCoalPowerPlant* lPlant);
	virtual ~VCoalPowerPlant();

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;
	inline virtual void tick(const float fTimeDelta) override
	{
		if (timeLastCheck > 0.05f && isOn)
		{
			viewModel.moveLore(VMaterialLoader::getRotationPerTick(VIdentifier::VCoalPowerPlant, fTimeDelta), 0.0f);
			timeLastCheck = 0.0f;
		}

		timeLastCheck += fTimeDelta;
		
		//viewModel.moveLore(0, timeLastCheck);

		//if (isOn)
		//{
		//	viewModel.rotate(VMaterialLoader::getRotationPerTick(VIdentifier::VCoalPowerPlant, fTimeDelta));
		//}
	}
};


NAMESPACE_VIEW_E
