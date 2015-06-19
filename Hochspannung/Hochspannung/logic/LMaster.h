#pragma once

#include "IVTickObserver.h"
#include "LGeneral.h"
#include "../network/NetworkService.h"
#include "LSabotage.h"
#include "LPlayer.h"

NAMESPACE_LOGIC_B


class IVMaster;
class LPlayingField;
class LPlayer;

class LMaster : public IVTickObserver
{
	NON_COPYABLE(LMaster);

private:
	IVMaster& vMaster;
	LPlayingField* lPlayingField = nullptr;
	bool gamePaused = false;
	bool singlePlayer = false;
	std::unordered_map<LPlayer::PlayerId, LPlayer> lPlayers;
	Network::CNetworkService& networkService;

private:
	void placeBuilding(const int buildingId, const int x, const int y, const int playerId);
	//networking
	void host(std::string gameName);
	void connect(const std::string& ip);

public:
	explicit LMaster(IVMaster& vMaster);
	~LMaster();

	void hostGame(const std::string & gameName);
	void startSinglePlayerGame();
	void joinGame(const std::string& ipAddress);

	void gameOver();
	void gameWon();
	virtual void tick(const float fTimeDelta) override;
	void sendDefaultIPs() const;

	//networking
	void sendSetObject(const int objectId, const int x, const int y, const std::string& value);
	void sendSetMapRow(const int row, std::vector<Network::FieldTransfer> rowData);
	void sendDeleteObject(const int x, const int y);
	void sendSabotage(const LSabotage::LSabotage sabotageId, const int x, const int y);
	void sendPowerPlantSabotageEnd(const int x, const int y);
	void sendPowerPlantSwitchState(const int x, const int y, const bool state);
	void sendRegenerativeRatio(const float ratio);
	void sendCityPopulation(const int population);
	const std::unordered_map<std::string, Network::CGameObject>& getGameList(bool* updated = nullptr);
	void searchGames();

	LPlayingField* getLPlayingField();
	IVMaster* getVMaster();
	LPlayer* getPlayer(const int playerId);
	bool isGamePaused() const
	{
		return gamePaused;
	}

	bool isSinglePlayer() const
	{
		return singlePlayer;
	}
};


NAMESPACE_LOGIC_E
