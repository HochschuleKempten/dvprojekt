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
	IVMaster* vMaster = nullptr;
	LPlayingField* lPlayingField = nullptr;
	LPlayer* lPlayer = nullptr;

public:
	LMaster(IVMaster* vMaster);
	~LMaster();

	void startNewGame();
	virtual void tick(const float fTimeDelta);

	LPlayingField* getLPlayingField();
	IVMaster* getVMaster();
	LPlayer* getPlayer();

};

NAMESPACE_LOGIC_E