#include "LMaster.h"
#include "LPlayingField.h"
#include "IVMaster.h"
#include "LIdentifier.h"
#include "LHydroelectricPowerPlant.h"
#include "LNuclearPowerPlant.h"
#include "LOilRefinery.h"
#include "LCoalPowerPlant.h"
#include "LSolarPowerPlant.h"
#include "LWindmillPowerPlant.h"
#include "LCity.h"
#include "LTransformerStation.h"

NAMESPACE_LOGIC_B


LMaster::LMaster(IVMaster& vMaster)
		: vMaster(vMaster), lPlayers({ this, this }),
		networkService(Network::CNetworkService::instance())
{
	vMaster.registerObserver(this);
}

LMaster::~LMaster()
{
	delete lPlayingField;
}

void LMaster::startNewGame()
{
	//host();
	//while (networkService.getConnectionState() != Network::CONNECTED);

	//DEBUG_OUTPUT("---------------Client connected to server.---------------");

	if (lPlayingField == nullptr)
	{
		lPlayingField = new LPlayingField(this);
	}

	lPlayingField->createFields();
	lPlayingField->showPlayingField();
}

void LMaster::gameOver()
{
	vMaster.gameOver();

	//todo (IP) test
	//networkService.close();
}

void LMaster::tick(const float fTimeDelta)
{
	using namespace Network;

	static float timeLastCheck = 0;

	//check every second
	if (timeLastCheck <= 1)
	{
		timeLastCheck += fTimeDelta;
		return;
	}

	timeLastCheck = 0;


	if (networkService.getConnectionState() == CONNECTED && networkService.isActionAvailable())
	{
		CTransferObject transferObject = networkService.getNextActionToExecute();
		int objectId = transferObject.getTransObjectID();
		int x = transferObject.getCoordX();
		int y = transferObject.getCoordY();

		int playerId = std::stoi(transferObject.getValue());
		if (playerId == LPlayer::Local)
		{
			playerId = LPlayer::External;
		}
		else if (playerId == LPlayer::External)
		{
			playerId = LPlayer::Local;
		}


		//regarding host
		switch (transferObject.getAction())
		{
		case(SET_OBJECT) :

			//buildings
				if (objectId == LIdentifier::LCoalPowerPlant)
				{
					lPlayingField->placeBuilding<LCoalPowerPlant>(x, y, playerId);
				}
				else if (objectId == LIdentifier::LHydroelectricPowerPlant)
				{
					lPlayingField->placeBuilding<LHydroelectricPowerPlant>(x, y, playerId);
				}
				else if (objectId == LIdentifier::LNuclearPowerPlant)
				{
					lPlayingField->placeBuilding<LNuclearPowerPlant>(x, y, playerId);
				}
				else if (objectId == LIdentifier::LOilRefinery)
				{
					lPlayingField->placeBuilding<LOilRefinery>(x, y, playerId);
				}
				else if (objectId == LIdentifier::LSolarPowerPlant)
				{
					lPlayingField->placeBuilding<LSolarPowerPlant>(x, y, playerId);
				}
				else if (objectId == LIdentifier::LWindmillPowerPlant)
				{
					lPlayingField->placeBuilding<LWindmillPowerPlant>(x, y, playerId);
				}
				else if (objectId == LIdentifier::LCity)
				{
					lPlayingField->placeBuilding<LCity>(x, y, playerId);
				}
				else if (objectId == LIdentifier::LPowerLine)
				{
					lPlayingField->placeBuilding<LPowerLine>(x, y, playerId);
				}
				else if (objectId == LIdentifier::LTransformerStation)
				{
					lPlayingField->placeBuilding<LTransformerStation>(x, y, playerId);
				}

			//fieldtypes
				if (objectId >= 0 && objectId < 9)
				{
					lPlayingField->getField(x, y)->setFieldType(static_cast<LField::FieldType>(objectId));
				}

			//fieldlevels
				if (objectId >= 20 && objectId < 23)
				{
					lPlayingField->getField(x, y)->setFieldLevel(static_cast<LField::FieldLevel>(objectId));
				}

			break;

		case(DELETE_OBJECT) :

			lPlayingField->removeBuilding(x, y);

			break;

		case(UPGRADE_OBJECT) :

			lPlayingField->upgradeBuilding(x, y);

			break;

		case(START_GAME) :

			//do nothing

			break;

		case(END_GAME) :

			gameOver();

			break;

		case(PAUSE_GAME) :

			vMaster.pauseGame();

			gamePaused = true;

			break;

		case(CONTINUE_GAME) :

			vMaster.continueGame();

			gamePaused = false;

			break;

		case(SET_MAPSIZE) :

			//do nothing

			break;

		default:
			break;
		}
	}
}

void LMaster::host()
{
	int reconnectCounter = 0;
	bool connected = false;

	while (reconnectCounter < 10 && !(connected = networkService.host()))
	{
		reconnectCounter++;
	}

	if (connected)
	{
		DEBUG_OUTPUT("Server started.");
	}
	else
	{
		DEBUG_OUTPUT("Server start failed.");
	}
}

void LMaster::connect(std::string ip)
{
	int reconnectCounter = 0;
	bool connected = false;

	while (reconnectCounter < 10 && !(connected = networkService.connect(ip)))
	{
		reconnectCounter++;
	}

	if (connected)
	{
		DEBUG_OUTPUT("Connected to server.");
	}
	else
	{
		DEBUG_OUTPUT("Connecting to server failed.");
	}
}

void LMaster::sendSetObject(const int objectId, const int x, const int y, const std::string& value)
{
	if (networkService.getConnectionState() == Network::State::CONNECTED) //todo (IP) return false if not connected?
	{
		networkService.sendSetObject(objectId, x, y, value);
	}
}

void LMaster::sendDeleteObject(const int x, const int y)
{
	if (networkService.getConnectionState() == Network::State::CONNECTED)
	{
		networkService.sendDeleteObject(-1, x, y); //todo (L) tell network guys to delete the first parameter
	}
}

LPlayingField* LMaster::getLPlayingField()
{
	return lPlayingField;
}

IVMaster* LMaster::getVMaster()
{
	return &vMaster;
}

LPlayer* LMaster::getPlayer(const int idxPlayer)
{
	ASSERT(idxPlayer >= 0 && idxPlayer <= 1, "Wrong idx for player");
	return &lPlayers[idxPlayer];
}


NAMESPACE_LOGIC_E
