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
	
	energySurplus = lField->getLPlayingField()->getCity()->getEnergySurplus();

	//Handle Disposal
	if (timeLastCheck > 1) {
		int seconds = CASTS<int>(timeLastCheck);
		ASSERT(seconds >= 1, "The number of seconds is invalid.");

		if (lField->getLPlayingField()->isMarctplaceConnected)
		{
			performDisposal();
		}
		timeLastCheck = 0;
	}

	timeLastCheck += fTimeDelta;


}

void LTransformerStation::performDisposal()
{
	if (energySurplus > 0)
	{
		//TODO (L) how to get the Player ID dynamicly?

		lField->getLPlayingField()->getLMaster()->getPlayer(1)->addMoney(amount);
	}
}



NAMESPACE_LOGIC_E
