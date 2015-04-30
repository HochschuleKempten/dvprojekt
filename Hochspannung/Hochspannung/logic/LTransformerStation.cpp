#include "LTransformerSation.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVTransformerStation.h"


NAMESPACE_LOGIC_B


LTransformerStation::LTransformerStation(LField* lField, const int x, const int y)
: ILBuilding(lField), vTransformerSation(lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createTransformerStation(this))
{
	vTransformerSation->initTransformerStation(vTransformerSation, x, y);
	lField->getLPlayingField()->getLMaster()->getVMaster()->registerObserver(this);
}

LTransformerStation::~LTransformerStation()
{
}

void LTransformerStation::tick(const float fTimeDelta)
{	
	static float timeLastCheck = 0;
	
	//Handle Disposal
	if (timeLastCheck > 1) {
		int seconds = CASTS<int>(timeLastCheck);
		ASSERT(seconds >= 1, "The number of seconds is invalid.");

		if (lField->getLPlayingField()->isTransformstationConnected())
		{
			performDisposal();
		}
		timeLastCheck = 0;
	}

	timeLastCheck += fTimeDelta;
}

void LTransformerStation::performDisposal()
{
	int superplus = lField->getLPlayingField()->getLocalCity()->getEnergySurplus();
	if (superplus > 0)
	{
		//TODO (L) how to get the Player ID dynamicly?
		lField->getLPlayingField()->getLMaster()->getPlayer(1)->addMoney(CASTS<int>(superplus * moneyPerWatt));
	}
}



NAMESPACE_LOGIC_E
