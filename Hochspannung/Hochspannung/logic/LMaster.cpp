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
	if (lPlayingField == nullptr)
	{
		lPlayingField = new LPlayingField(this);
	}
}

void LMaster::gameOver()
{
	vMaster.gameOver();

	//todo (IP) test
	networkService.close();
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


		//regarding host
		switch (transferObject.getAction())
		{
		case(SET_OBJECT) :

			//prevents placing loop (look at LPlayingField.h)
			lPlayingField->beginLocalOperation();


			if (objectId >= 0 && objectId < 16)//check if building is a powerline (orientation values between 0 and 16)
			{
				lPlayingField->placeBuilding<LPowerLine>(x, y, objectId);
			}
			else
			{
				if (objectId == LIdentifier::LCoalPowerPlant)
				{
					lPlayingField->placeBuilding<LCoalPowerPlant>(x, y);
				}
				else if (objectId == LIdentifier::LHydroelectricPowerPlant)
				{
					lPlayingField->placeBuilding<LHydroelectricPowerPlant>(x, y);
				}
				else if (objectId == LIdentifier::LNuclearPowerPlant)
				{
					lPlayingField->placeBuilding<LNuclearPowerPlant>(x, y);
				}
				else if (objectId == LIdentifier::LOilRefinery)
				{
					lPlayingField->placeBuilding<LOilRefinery>(x, y);
				}
				else if (objectId == LIdentifier::LSolarPowerPlant)
				{
					lPlayingField->placeBuilding<LSolarPowerPlant>(x, y);
				}
				else if (objectId == LIdentifier::LWindmillPowerPlant)
				{
					lPlayingField->placeBuilding<LWindmillPowerPlant>(x, y);
				}
				else if (objectId == LIdentifier::LCity)
				{
					lPlayingField->placeBuilding<LCity>(x, y);
				}
			}

			//assign player id
			lPlayingField->getField(x, y)->getBuilding()->setPlayerId(LPlayer::External);

			lPlayingField->endLocalOperation();

			break;

		case(DELETE_OBJECT) :

			lPlayingField->beginLocalOperation();

			lPlayingField->removeBuilding(x, y);

			lPlayingField->endLocalOperation();

			break;

		case(UPGRADE_OBJECT) :

			lPlayingField->beginLocalOperation();

			lPlayingField->upgradeBuilding(x, y);

			lPlayingField->endLocalOperation();

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

		startNewGame();
	}
	else
	{
		DEBUG_OUTPUT("Connecting to server failed.");
	}
}

void LMaster::sendSetObject(const int objectId, const int x, const int y)
{
	networkService.sendSetObject(objectId, x, y);
}

void LMaster::sendDeleteObject(const int x, const int y)
{
	networkService.sendDeleteObject(-1, x, y); //todo (L) tell network guys to delete the first parameter (needless)
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
