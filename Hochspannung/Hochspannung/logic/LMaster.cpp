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
#include "LMessageLoader.h"
#include "LPowerLine.h"
#include <boost\lexical_cast.hpp>

NAMESPACE_LOGIC_B

LMaster::LMaster(IVMaster& vMaster)
	: vMaster(vMaster), networkService(Network::CNetworkService::instance())
{
	LBalanceLoader::init();
	LMessageLoader::init(&vMaster);

	vMaster.registerObserver(this);

	lPlayers.emplace(std::piecewise_construct, std::make_tuple(LPlayer::Local), std::make_tuple(this, LPlayer::Local));
	lPlayers.emplace(std::piecewise_construct, std::make_tuple(LPlayer::Remote), std::make_tuple(this, LPlayer::Remote));

	//Only add default money to the local player
	getPlayer(LPlayer::Local)->addMoney(LBalanceLoader::getDefaultMoney());
}

LMaster::~LMaster()
{
	vMaster.unregisterObserver(this);
	delete lPlayingField;
	networkService.close();
}

void LMaster::startNewGame(const std::string& ipAddress)
{
	if (lPlayingField == nullptr)
	{
		lPlayingField = new LPlayingField(this);
	}

	if (ipAddress.empty())
	{
		host();
		while (networkService.getConnectionState() != Network::CNode::State::CONNECTED);
	}
	else if (ipAddress == "SINGLE_PLAYER")
	{
		lPlayingField->createFields();
		lPlayingField->showPlayingField();

		return;
	}
	else
	{
		connect(ipAddress);
	}

	vMaster.startBuildingPlayingField();

	if (networkService.getType() != Network::CNode::Type::CLIENT)
	{
		lPlayingField->createFields();
	}
}

void LMaster::gameOver()
{
	vMaster.gameOver();

	networkService.sendStopGame();
	networkService.close();
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

	if (timeLastCheck > 3.0F && lPlayingField == nullptr)
	{
		bool updated = false;
		std::vector<CGameObject> gameList = getGameList(&updated);

		if (updated)
		{
			DEBUG_OUTPUT("Updated gamelist.");
			vMaster.updateGameList(gameList);
		}
	}

	static bool firstConnectDone = false;

	if (networkService.getConnectionState() == CNode::State::CONNECTED)
	{

		if (timeLastCheck > 0.25F && networkService.isActionAvailable())
		{
			firstConnectDone = true;

			CTransferObject transferObject = networkService.getNextActionToExecute();
			int objectId = transferObject.getTransObjectID();
			int x = transferObject.getCoordX();
			int y = transferObject.getCoordY();


			DEBUG_OUTPUT("objectId=" << objectId << ":x=" << x << ":y=" << y);

			//regarding host
			switch (transferObject.getAction())
			{
			case(CTransferObject::Action::SET_OBJECT) :
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
					//TODO (L) handle race condition? --> remove building?
					placeBuilding(objectId, x, y, playerId);
				}
				else if (objectId == -666) //= end of fieldcreation
				{
					networkService.sendStartGame(); //notifiy host (client is ready)
					lPlayingField->showPlayingField();
				}

				DEBUG_OUTPUT("Action SET_OBJECT");

				break;
			}
			case(CTransferObject::Action::DELETE_OBJECT) :

				lPlayingField->removeBuilding(x, y);
				DEBUG_OUTPUT("Action DELETE_OBJECT");
				break;

			case(CTransferObject::Action::UPGRADE_OBJECT) :

				lPlayingField->upgradeBuilding(x, y);
				DEBUG_OUTPUT("Action UPGRADE_OBJECT");
				break;

			case(CTransferObject::Action::START_GAME) :

				lPlayingField->showPlayingField();
				DEBUG_OUTPUT("Action START_GAME");
				break;

			case(CTransferObject::Action::END_GAME) :

				//enemy player has lost the game
				vMaster.gameWon();
				DEBUG_OUTPUT("Action END_GAME");
				break;

			case(CTransferObject::Action::PAUSE_GAME) ://todo (IP) send 

				vMaster.pauseGame();

				gamePaused = true;
				DEBUG_OUTPUT("Action PAUSE_GAME");
				break;

			case(CTransferObject::Action::CONTINUE_GAME) ://todo (IP) send 

				vMaster.continueGame();

				gamePaused = false;
				DEBUG_OUTPUT("Action CONTINUE_GAME");
				break;

			case(CTransferObject::Action::SET_MAPROW) :
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

				DEBUG_OUTPUT("Action SET_MAPROW");

				break;
			}

			case(CTransferObject::Action::SEND_SABOTAGE) :
			{
				LSabotage::LSabotage objectToSabotage = static_cast<LSabotage::LSabotage>(objectId);
				DEBUG_OUTPUT("Action SEND_SABOTAGE");
				switch (objectToSabotage)
				{
				case(LSabotage::PowerLine) :
				{
					LPowerLine* powerLine = dynamic_cast<LPowerLine*>(lPlayingField->getField(x, y)->getBuilding());
					if (powerLine != nullptr)
					{
						powerLine->sabotagePowerLine();
					}
					break;
				}

				case(LSabotage::PowerPlant) :
				{
					ILPowerPlant* powerPlant = dynamic_cast<ILPowerPlant*>(lPlayingField->getField(x, y)->getBuilding());
					if (powerPlant != nullptr)
					{
						powerPlant->sabotagePowerPlant();
					}

					break;
				}

				case(LSabotage::Resource) :
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

			case(CTransferObject::Action::SEND_SWITCH_STATE) :
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
				DEBUG_OUTPUT("Action SEND_SWITCH_STATE");
				break;
			}

			default:
				break;
			}

			timeLastCheck = 0;
		}

	}
	else
	{
		if (firstConnectDone)
		{
			LMessageLoader::emitMessage(LMessageLoader::NETWORK_CONNECTION_LOST);
		}
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
	if (networkService.getConnectionState() == Network::CNode::State::CONNECTED)
	{
		bool b = networkService.sendSetObject(objectId, x, y, value);
		ASSERT(b == true, "Error: sendSetObject.");
		DEBUG_OUTPUT("----SENDSETOBJECT: Objectid: " + std::to_string(objectId) + ", x: " +std::to_string(x) + ", y:" + std::to_string(y) + ", value: " + value);
	}
}

void LMaster::sendSetMapRow(const int row, std::vector<Network::FieldTransfer> rowData)
{
	if (networkService.getConnectionState() == Network::CNode::State::CONNECTED)
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
	if (networkService.getConnectionState() == Network::CNode::State::CONNECTED)
	{
		bool b = networkService.sendDeleteObject(x, y);
		ASSERT(b == true, "Error: sendDeleteObject.");
		DEBUG_OUTPUT("----SENDDELETEOBJECT: x: " << x << ", y: " << y);

	}
}

void LMaster::sendSabotage(const LSabotage::LSabotage sabotageId, const int x, const int y)
{
	if (networkService.getConnectionState() == Network::CNode::State::CONNECTED)
	{
		networkService.sendSabotage(sabotageId, x, y);
	}
}

void LMaster::sendPowerPlantSwitchState(const int x, const int y, const bool state)
{
	if (networkService.getConnectionState() == Network::CNode::State::CONNECTED)
	{
		networkService.sendSwitchState(x, y, state);
	}
}

std::vector<Network::CGameObject> LMaster::getGameList(bool* updated)
{
	static std::vector<Network::CGameObject> prevGameList;
	std::vector<Network::CGameObject> newGameList = networkService.getGameList();

	if (newGameList != prevGameList)
	{
		newGameList = prevGameList;

		if (updated != nullptr)
		{
			*updated = true;
		}
	}
	else
	{
		if (updated != nullptr)
		{
			*updated = false;
		}
	}

	return newGameList;
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

LPlayer* LMaster::getPlayer(const int playerId)
{
	ASSERT(lPlayers.count(static_cast<LPlayer::PlayerId>(playerId)) > 0, "Invalid playerId. There is no player with the id " << playerId << " available");
	return &lPlayers[static_cast<LPlayer::PlayerId>(playerId)];
}


NAMESPACE_LOGIC_E
