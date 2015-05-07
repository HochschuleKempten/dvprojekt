#pragma once
#include "IVTickObserver.h"
#include "LGeneral.h"
#include "../network/NetworkService.h"

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
	std::vector<LPlayer> lPlayers;
	Network::CNetworkService& networkService;
	void placeBuilding(const int buildingId, const int x, const int y, const int playerId);

public:
	explicit LMaster(IVMaster& vMaster);
	~LMaster();

	void startNewGame();
	void gameOver();
	virtual void tick(const float fTimeDelta) override;
	bool gamePaused = false;

	//networking
	void host();
	void connect(std::string ip);
	void sendSetObject(const int objectId, const int x, const int y, const std::string& value);
	void sendSetMapRow(const int row, std::vector<Network::FieldTransfer> rowData);
	void sendDeleteObject(const int x, const int y);

	LPlayingField* getLPlayingField();
	IVMaster* getVMaster();
	LPlayer* getPlayer(const int idxPlayer);
};


NAMESPACE_LOGIC_E
