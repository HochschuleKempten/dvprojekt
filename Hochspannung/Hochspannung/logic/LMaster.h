#pragma once
#include "IVTickObserver.h"
#include "LGeneral.h"

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

public:
	LMaster(IVMaster& vMaster);
	~LMaster();

	void startNewGame();
	void gameLost();
	virtual void tick(const float fTimeDelta) override;

	LPlayingField* getLPlayingField();
	IVMaster* getVMaster();
	LPlayer* getPlayer(const int idxPlayer);

};


NAMESPACE_LOGIC_E
