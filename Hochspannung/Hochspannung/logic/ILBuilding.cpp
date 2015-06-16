#include "ILBuilding.h"
#include "LField.h"
#include "LPlayingField.h"


void HighVoltage::ILBuilding::sabotageRemove()
{
	LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_DESTROY);
	if (!lField->getLPlayingField()->isLocalOperation())
	{
		std::pair<int, int> coordinates = lField->getCoordinates();
		lField->getLPlayingField()->getLMaster()->sendSabotage(LSabotage::LSabotage::Remove, coordinates.first, coordinates.second);
	}
}