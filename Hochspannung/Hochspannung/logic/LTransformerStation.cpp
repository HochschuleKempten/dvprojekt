#include "LTransformerStation.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVTransformerStation.h"
#include "LBalanceLoader.h"

NAMESPACE_LOGIC_B


LTransformerStation::LTransformerStation(LField* lField, const int x, const int y, const int playerId)
	: ILBuilding(lField, playerId), vTransformerSation(lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createTransformerStation(this))
{
	vTransformerSation->initTransformerStation(vTransformerSation, x, y);
	lField->getLPlayingField()->getLMaster()->getVMaster()->registerObserver(this);
}

LTransformerStation::~LTransformerStation()
{
	lField->getLPlayingField()->getLMaster()->getVMaster()->unregisterObserver(this);
}

void LTransformerStation::tick(const float fTimeDelta)
{	
	if (lField->getLPlayingField()->isInitDone()) {
		//Handle Disposal
		if (timeLastCheck > 1) {

			if (lField->getLPlayingField()->isTransformstationConnected())
			{
				performDisposal();
			}
			timeLastCheck = 0;
		}

		timeLastCheck += fTimeDelta;
	}
}

void LTransformerStation::performDisposal()
{
	int surplus = lField->getLPlayingField()->getLMaster()->getPlayer(LPlayer::Local)->getCity()->getEnergySurplus();
	if (surplus > 0)
	{
		lField->getLPlayingField()->getLMaster()->getPlayer(LPlayer::Local)->addMoney(CASTS<int>(surplus * LBalanceLoader::getMoneyPerWatt()));
	}
}



NAMESPACE_LOGIC_E
