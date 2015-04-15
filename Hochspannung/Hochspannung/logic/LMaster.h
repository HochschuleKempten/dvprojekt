#pragma once

#include "IVTickObserver.h"

class IVMaster;
class LPlayingField;
class LPlayer;

class LMaster : public IVTickObserver
{

private:
	IVMaster* vMaster;
	LPlayingField* lPlayingField = nullptr;
	LPlayer* lPlayer;

public:
	LMaster(IVMaster* vMaster);
	~LMaster();

	void startNewGame();
	virtual void tick(const float fTimeDelta);

	LPlayingField* getLPlayingField();
	IVMaster* getVMaster();
	LPlayer* getPlayer();

};
