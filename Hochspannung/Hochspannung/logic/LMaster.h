#pragma once

#include "IVTickObserver.h"
#include "LUI.h"

class IVMaster;
class LPlayingField;
class LPlayer;

class LMaster : public IVTickObserver
{

private:
	IVMaster* vMaster;
	LPlayingField* lPlayingField = nullptr;
	LPlayer* lPlayer;
	LUI lUi;

public:
	LMaster(IVMaster* vMaster);
	~LMaster();

	void startNewGame();
	virtual void tick(const float fTimeDelta);

	LPlayingField* getLPlayingField();
	IVMaster* getVMaster();
	LPlayer* getPlayer();

};
