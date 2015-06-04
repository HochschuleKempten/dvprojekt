#include "LMessageLoader.h"
#include "IVMaster.h"

NAMESPACE_LOGIC_B

IVMaster* LMessageLoader::vMaster;
DEBUG_EXPRESSION(bool LMessageLoader::initDone = false);
DEBUG_EXPRESSION(static const char* const msgAssert = "LMessageLoader is not initialized");

void LMessageLoader::init(IVMaster* vMaster)
{
	LMessageLoader::vMaster = vMaster;

	initDone = true;
}

void LMessageLoader::emitMessage(const MessageID messageId, const std::vector<std::string>& param)
{
	ASSERT(initDone, msgAssert);

	std::string text;

	switch (messageId)
	{
		default: break;
		case SABOTAGE_EMITTED:
			text = std::string("Sabotage durchgeführt. Es verbleiben ") + param[0] + std::string(" Sabotageakte.");
			break;
		case SABOTAGE_NO_ACTS_LEFT:
			text = "Keine Sabotageaktionen mehr übrig.";
			break;
		case SABOTAGE_WAIT:
			text = std::string("Es muss noch ") + param[0] + std::string(" Sekunden gewartet werden, bevor die nächste Sabotageaktion durchgeführt werden kann.");
			break;
		case SABOTAGE_NO_MONEY:
			text = "Nicht genügend Geld für die Sabotageaktion vorhanden.";
			break;
		case BUILD_NO_MONEY:
			text = std::string("Kraftwerk ") + param[0] + std::string(" kann nicht gebaut werden, da nur ") +
				   param[1] + std::string(" EUR zur Verfügung stehen, es werden jedoch ") +
				   param[2] + std::string(" benötigt.");
			break;
		case BUILD_FIELD_OCCUPIED:
			text = std::string("Ein ") + param[0] + std::string(" kann hier nicht platziert werden, da auf dem Feld ") + param[1] + std::string(" bereits ein Gebäude steht.");
			break;
		case BUILD_FIELD_WRONG_TYPE:
			text = std::string("Ein ") + param[0] + std::string(" kann nicht auf einem Feld vom Typ ") + param[1] + std::string(" platziert werden.");
			break;
		case NETWORK_CONNECTION_LOST:
			text = "Verbindung verloren.";
			break;
	}

	vMaster->showMessage(text, messageId);
}

NAMESPACE_LOGIC_E
