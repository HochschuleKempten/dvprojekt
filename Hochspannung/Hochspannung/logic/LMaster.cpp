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
#include "LPowerLine.h"
#include <boost\lexical_cast.hpp>

NAMESPACE_LOGIC_B

LMaster::LMaster(IVMaster& vMaster)
	: vMaster(vMaster), lPlayers(new LPlayer[2]{ this, this }),
		networkService(Network::CNetworkService::instance())
{
	vMaster.registerObserver(this);
	LBalanceLoader::init();
	searchGames(); //start searching
}

LMaster::~LMaster()
{
	delete lPlayingField;
	networkService.close();
}

void LMaster::startNewGame(const std::string& ipAddress)
{
	if (ipAddress.empty())
	{
		host();
		while (networkService.getConnectionState() != Network::CONNECTED);
	}
	else if (ipAddress == "SINGLE_PLAYER")
	{
		lPlayingField = new LPlayingField(this);
		lPlayingField->createFields();
		lPlayingField->showPlayingField();

		return;
	}
	else
	{
		connect(ipAddress);
	}

	if (lPlayingField == nullptr)
	{
		lPlayingField = new LPlayingField(this);
	}

	if (networkService.getType() != Network::Type::CLIENT)
	{
		lPlayingField->createFields();
		lPlayingField->showPlayingField();
	}
}

void LMaster::gameOver()
{
	vMaster.gameOver();

	if (networkService.getConnectionState() == Network::CONNECTED)
	{
		networkService.close();
	}
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

	static float timeLastCheck = 0;

	////Just for testing
	//try
	//{
	//	static bool gameListUpdatedFirst = false;
	//	static bool gameListUpdatedSecond = TRUE;
	//	if (!gameListUpdatedFirst && timeLastCheck > 5.0f)
	//	{
	//		vMaster.updateGameList({
	//			CGameObject(ip::address::from_string("172.16.16.71"), 1000, "Test1"),
	//			CGameObject(ip::address::from_string("222.9.2.171"), 500, "Test2")
	//		});

	//		gameListUpdatedFirst = true;
	//		gameListUpdatedSecond = false;
	//	}
	//	if (!gameListUpdatedSecond && timeLastCheck > 8.0f)
	//	{
	//		vMaster.updateGameList({
	//			CGameObject(ip::address::from_string("172.16.16.71"), 1000, "Test1"),
	//			CGameObject(ip::address::from_string("200.111.111.111"), 111, "Test3")
	//		});

	//		gameListUpdatedSecond = true;
	//	}
	//}
	//catch (boost::system::system_error error) {
	//	ASSERT(error.what());
	//}

	if (timeLastCheck > 3.0F && (lPlayingField != nullptr ? !lPlayingField->isInitDone() : true))
	{
		DEBUG_OUTPUT("Updated gamelist.");
		vMaster.updateGameList(getGameList());
	}

	if (timeLastCheck > 0.25F && networkService.getConnectionState() == CONNECTED && networkService.isActionAvailable())
	{
		CTransferObject transferObject = networkService.getNextActionToExecute();
		int objectId = transferObject.getTransObjectID();
		int x = transferObject.getCoordX();
		int y = transferObject.getCoordY();
		

		DEBUG_OUTPUT("objectId=" << objectId << ":x=" << x << ":y=" << y);

		//regarding host
		switch (transferObject.getAction())
		{
		case(SET_OBJECT) :
		{
			int playerId = std::stoi(transferObject.getValue());
			if (playerId == LPlayer::Local)
			{
				playerId = LPlayer::Remote;
			}
			else if (playerId == LPlayer::Remote)
			{
				playerId = LPlayer::Local;
			}

			//buildings
			if (objectId >= 100 && objectId < 109)
			{
				placeBuilding(objectId, x, y, playerId);
			}
			else if (objectId == -666) //= end of fieldcreation
			{
				lPlayingField->showPlayingField();
			}

			break;
		}
		case(DELETE_OBJECT) :

			lPlayingField->removeBuilding(x, y);

			break;

		case(UPGRADE_OBJECT) :

			lPlayingField->upgradeBuilding(x, y);

			break;

		case(END_GAME) : //todo (IP) send 

			gameOver();

			break;

		case(PAUSE_GAME) ://todo (IP) send 

			vMaster.pauseGame();

			gamePaused = true;

			break;

		case(CONTINUE_GAME) ://todo (IP) send 

			vMaster.continueGame();

			gamePaused = false;

			break;

		case(SET_MAPROW) :
		{
			std::vector<FieldTransfer> row = transferObject.getValueAsVector();
			int rowNumber = x;

			for (int column = 0; column < CASTS<int>(row.size()); column++)
			{
				lPlayingField->initField(rowNumber, column, static_cast<LField::FieldType>(row[column].iFieldType), static_cast<LField::FieldLevel>(row[column].iFieldLevel));

				if (row[column].iObjectID != -1)
				{
					int plId = row[column].iPlayerID;
					if (plId == LPlayer::Local)
					{
						plId = LPlayer::Remote;
					}
					else if (plId == LPlayer::Remote)
					{
						plId = LPlayer::Local;
					}

					placeBuilding(row[column].iObjectID, rowNumber, column, plId);
				}
			}

			break;
		}

		case(SEND_SABOTAGE) :
		{
			LSabotage::LSabotage objectToSabotage = static_cast<LSabotage::LSabotage>(objectId);

			switch (objectToSabotage)
			{
			case(LSabotage::LSabotage::PowerLine) :
			{
				LPowerLine* powerLine = dynamic_cast<LPowerLine*>(lPlayingField->getField(x, y)->getBuilding());
				if (powerLine != nullptr)
				{
					powerLine->sabotage();
				}
				break;
			}

			case(LSabotage::LSabotage::PowerPlant) :
			{
				ILPowerPlant* powerPlant = dynamic_cast<ILPowerPlant*>(lPlayingField->getField(x, y)->getBuilding());
				if (powerPlant != nullptr)
				{
					powerPlant->sabotage();
				}

				break;
			}

			case(LSabotage::LSabotage::Resource) :
			{
				ILPowerPlant* powerPlant = dynamic_cast<ILPowerPlant*>(lPlayingField->getField(x, y)->getBuilding());
				if (powerPlant != nullptr)
				{
					powerPlant->sabotageResource();
				}

				break;
			}

			default:
				break;
			}

			break;
		}

		case(SEND_SWITCH_STATE) :
		{
			ILPowerPlant* powerPlant = dynamic_cast<ILPowerPlant*>(lPlayingField->getField(x, y)->getBuilding());
			if (powerPlant != nullptr)
			{
				bool isActivated = boost::lexical_cast<bool>(transferObject.getValue());
				if (isActivated)
				{
					powerPlant->switchOn();
				}
				else
				{
					powerPlant->switchOff();
				}
			}

			break;
		}

		default:
			break;
		}

		timeLastCheck = 0;
	}

	timeLastCheck += fTimeDelta;
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

void LMaster::connect(const std::string& ip)
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
		DEBUG_OUTPUT("----SENDSETOBJECT: Objectid: " + std::to_string(objectId) + ", x: " +std::to_string(x) + ", y:" + std::to_string(y) + ", value: " + value);
	}
}

void LMaster::sendSetMapRow(const int row, std::vector<Network::FieldTransfer> rowData)
{
	if (networkService.getConnectionState() == Network::State::CONNECTED)
	{
		bool b = networkService.sendSetMapRow(row, rowData);
		ASSERT(b == true, "Error: sendSetMapRow.");
		DEBUG_OUTPUT("----SENDSETMAPROW: row: " + std::to_string(row)+"-------");
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
		bool b = networkService.sendDeleteObject(x, y);
		ASSERT(b == true, "Error: sendDeleteObject.");
		DEBUG_OUTPUT("----SENDDELETEOBJECT: x: " << x << ", y: " << y);

	}
}

void LMaster::sendSabotage(const LSabotage::LSabotage sabotageId, const int x, const int y)
{
	if (networkService.getConnectionState() == Network::State::CONNECTED)
	{
		networkService.sendSabotage(sabotageId, x, y);
	}
}

void LMaster::sendPowerPlantSwitchState(const int x, const int y, const bool state)
{
	if (networkService.getConnectionState() == Network::State::CONNECTED)
	{
		networkService.sendSwitchState(x, y, state);
	}
}

std::vector<Network::CGameObject> LMaster::getGameList()
{
	return networkService.getGameList();
}

void LMaster::searchGames()
{
	networkService.searchGames();
	DEBUG_OUTPUT("Started searching for games...");
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
