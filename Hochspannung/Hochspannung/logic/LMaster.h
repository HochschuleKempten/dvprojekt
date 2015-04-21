#pragma once
#include "IVTickObserver.h"
#include "LGeneral.h"
#include "LPlayer.h"

NAMESPACE_LOGIC_B


class IVMaster;
class LPlayingField;

class LMaster : public IVTickObserver
{
private:
	IVMaster& vMaster;
	LPlayingField* lPlayingField = nullptr;
	LPlayer lPlayer[2];

private:
	//Objects of this class should not be copied
	//LMaster(const LMaster&) = delete;
	//LMaster(const LMaster&&) = delete;
	//LMaster& operator=(const LMaster&) = delete;
	//LMaster& operator=(const LMaster&&) = delete;

public:
	LMaster(IVMaster& vMaster);
	~LMaster();

	void startNewGame();
	void gameLost();
	virtual void tick(const float fTimeDelta);

	LPlayingField* getLPlayingField();
	IVMaster* getVMaster();
	LPlayer* getPlayers();

};


NAMESPACE_LOGIC_E
