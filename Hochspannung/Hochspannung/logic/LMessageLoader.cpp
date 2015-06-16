#include "LMessageLoader.h"
#include "IVMaster.h"
#include "LField.h"

NAMESPACE_LOGIC_B

IVMaster* LMessageLoader::vMaster;
DEBUG_EXPRESSION(bool LMessageLoader::initDone = false);
DEBUG_EXPRESSION(static const char* const msgAssert = "LMessageLoader is not initialized");

void LMessageLoader::init(IVMaster* vMaster)
{
	LMessageLoader::vMaster = vMaster;

	DEBUG_EXPRESSION(initDone = true);
}

void LMessageLoader::emitMessage(const MessageID messageId, const std::vector<std::string>& param)
{
	ASSERT(initDone, msgAssert);

	std::string text;

	switch (messageId)
	{
		case SABOTAGE_EMITTED:
			text = std::string("Sabotage durchgefuehrt. Es verbleiben ") + param[0] + std::string(" Sabotageakte.");
			break;
		case SABOTAGE_NO_ACTS_LEFT:
			text = "Keine Sabotageaktionen mehr uebrig.";
			break;
		case SABOTAGE_WAIT:
			text = std::string("Es muss noch ") + param[0] + std::string(" Sekunden gewartet werden, bevor die naechste Sabotageaktion durchgefuehrt werden kann.");
			break;
		case SABOTAGE_NO_MONEY:
			text = "Nicht genuegend Geld für die Sabotageaktion vorhanden.";
			break;
		case BUILD_NO_MONEY:
			text = std::string("Kraftwerk ") + param[0] + std::string(" kann nicht gebaut werden, da nur ") +
				   param[1] + std::string(" EUR zur Verfuegung stehen, es werden jedoch ") +
				   param[2] + std::string(" benoetigt.");
			break;
		case BUILD_FIELD_OCCUPIED:
			text = std::string("Ein ") + param[0] + std::string(" kann hier nicht platziert werden, da auf dem ") + param[1] + std::string("-Feld bereits ein Gebaeude steht.");
			break;
		case BUILD_FIELD_WRONG_TYPE:
			text = std::string("Ein ") + param[0] + std::string(" kann nicht auf einem ") + param[1] + std::string("-Feld platziert werden.");
			break;
		case NETWORK_CONNECTION_LOST:
			text = "Verbindung verloren.";
			break;
		case SURPLUS_LOW:
			text = "Achtung! Der aktuelle Energieueberschuss ist sehr gering. Wenn die Bevoelkerung nicht mit Energie versorgt werden kann, ist das Spiel verloren.";
			break;
		default: break;
	}

	vMaster->showMessage(text, messageId);
}

std::string LMessageLoader::getNameForFieldType(const int fieldType)
{
	switch (fieldType)
	{
		case LField::CITY: return "Stadt";
		case LField::WATER: return "Wasser";
		case LField::AIR: return "Luft";
		case LField::SOLAR: return "Solar";
		case LField::GRASS: return "Gras";
		case LField::MOUNTAIN: return "Berg";
		case LField::COAL: return "Kohle";
		case LField::OIL: return "Oel";
		case LField::NUCLEAR: return "Atom";
		default:
			ASSERT("Wrong Field type");
			return "";
	}
}

NAMESPACE_LOGIC_E
