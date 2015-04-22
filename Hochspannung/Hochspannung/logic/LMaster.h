#pragma once
#include "IVTickObserver.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B


class IVMaster;
class LPlayingField;
class LPlayer;

class LMaster : public IVTickObserver
{
private:
	IVMaster& vMaster;
	LPlayingField* lPlayingField = nullptr;
	LPlayer* lPlayer = nullptr;

private:
	//TODO (JS) non_copyable objects
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
	virtual void tick(const float fTimeDelta) override;

	LPlayingField* getLPlayingField();
	IVMaster* getVMaster();
	LPlayer* getPlayer(const int idxPlayer);

};


NAMESPACE_LOGIC_E
