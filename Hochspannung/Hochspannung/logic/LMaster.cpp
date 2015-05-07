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
#include "LBalanceLoader.h"

NAMESPACE_LOGIC_B

LMaster::LMaster(IVMaster& vMaster)
		: vMaster(vMaster), lPlayers({ this, this }),
		networkService(Network::CNetworkService::instance())
{
	vMaster.registerObserver(this);
	LBalanceLoader::init();
}

LMaster::~LMaster()
{
	delete lPlayingField;
	networkService.close();
}

void LMaster::startNewGame()
{
	//host();
	//while (networkService.getConnectionState() != Network::CONNECTED);

	//DEBUG_OUTPUT("---------------Client connected to server.---------------");

	DEBUG_OUTPUT("---------------Client connected to server.---------------");
	//connect("172.16.39.138");

	if (lPlayingField == nullptr)
	{
		lPlayingField = new LPlayingField(this);
	}

	if (networkService.getType() != Network::Type::CLIENT) //todo (IP)
	{
		lPlayingField->createFields();
		lPlayingField->showPlayingField();
	}
}

void LMaster::gameOver()
{
	vMaster.gameOver();

	//networkService.close();
}

void LMaster::placeBuilding(const int buildingId, const int x, const int y, const int playerId)
{
	if (buildingId == LIdentifier::LCoalPowerPlant)
	{
		lPlayingField->placeBuilding<LCoalPowerPlant>(x, y, playerId);
	}
	else if (buildingId == LIdentifier::LHydroelectricPowerPlant)
	{
		lPlayingField->placeBuilding<LHydroelectricPowerPlant>(x, y, playerId);
	}
	else if (buildingId == LIdentifier::LNuclearPowerPlant)
	{
		lPlayingField->placeBuilding<LNuclearPowerPlant>(x, y, playerId);
	}
	else if (buildingId == LIdentifier::LOilRefinery)
	{
		lPlayingField->placeBuilding<LOilRefinery>(x, y, playerId);
	}
	else if (buildingId == LIdentifier::LSolarPowerPlant)
	{
		lPlayingField->placeBuilding<LSolarPowerPlant>(x, y, playerId);
	}
	else if (buildingId == LIdentifier::LWindmillPowerPlant)
	{
		lPlayingField->placeBuilding<LWindmillPowerPlant>(x, y, playerId);
	}
	else if (buildingId == LIdentifier::LCity)
	{
		lPlayingField->placeBuilding<LCity>(x, y, playerId);
	}
	else if (buildingId == LIdentifier::LPowerLine)
	{
		lPlayingField->placeBuilding<LPowerLine>(x, y, playerId);
	}
	else if (buildingId == LIdentifier::LTransformerStation)
	{
		lPlayingField->placeBuilding<LTransformerStation>(x, y, playerId);
	}
}

void LMaster::tick(const float fTimeDelta)
{
	using namespace Network;

	static int tickCounter = 0;

	//check every fifth tick if there is a new action
	if (tickCounter < 50)
	{
		tickCounter++;
		return;
	}
	tickCounter = 0;

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

		DEBUG_OUTPUT("objectId=" << objectId << ":x=" << x << ":y=" << y << ":playerId=" << playerId);

		//regarding host
		switch (transferObject.getAction())
		{
		case(SET_OBJECT) :

			//buildings
			if (objectId >= 100 && objectId < 109)
			{
				placeBuilding(objectId, x, y, playerId);
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

			if (playerId == -66) //= end of fieldcreation
			{
				lPlayingField->showPlayingField();
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

		case(SET_MAPROW) :
		{
			std::vector<FieldTransfer> row = transferObject.getValueAsVector();
			int rowNumber = x;

			for (int column = 0; column < row.size(); column++)
			{
				lPlayingField->initField(rowNumber, column, static_cast<LField::FieldType>(row[column].iFieldType), static_cast<LField::FieldLevel>(row[column].iFieldLevel));

				if (row[column].iObjectID != -1)
				{
					int plId = row[column].iPlayerID;
					if (plId == LPlayer::Local)
					{
						plId = LPlayer::External;
					}
					else if (plId == LPlayer::External)
					{
						plId = LPlayer::Local;
					}

					placeBuilding(row[column].iObjectID, rowNumber, column, plId);
				}
			}

			break;
		}

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
	if (networkService.getConnectionState() == Network::State::CONNECTED)
	{
		bool b = networkService.sendSetObject(objectId, x, y, value);
		ASSERT(b == true, "Error: sendSetObject.");
		DEBUG_OUTPUT("Sent: Objectid: " + std::to_string(objectId) + ", x: " +std::to_string(x) + ", y:" + std::to_string(y) + ", value: " + value);
	}
}

void LMaster::sendSetMapRow(const int row, std::vector<Network::FieldTransfer> rowData)
{
	if (networkService.getConnectionState() == Network::State::CONNECTED)
	{
		bool b = networkService.sendSetMapRow(row, rowData);
		ASSERT(b == true, "Error: sendSetMapRow.");
		DEBUG_OUTPUT("----Sent: row: " + std::to_string(row)+"-------");
		for (Network::FieldTransfer ft : rowData)
		{
			DEBUG_OUTPUT("ObjectId: " + std::to_string(ft.iObjectID) + ", PlayerId: " + std::to_string(ft.iPlayerID) + ", FieldLevel: " + std::to_string(ft.iFieldLevel) + ", FieldType: " + std::to_string(ft.iFieldType));
		}
		DEBUG_OUTPUT("----------");
	}
}

void LMaster::sendDeleteObject(const int x, const int y)
{
	if (networkService.getConnectionState() == Network::State::CONNECTED)
	{
		bool b= networkService.sendDeleteObject(x, y);
		ASSERT(b == true, "Error: sendDeleteObject.");

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
