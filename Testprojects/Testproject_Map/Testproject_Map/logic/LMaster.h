#pragma once
#include "IVMaster.h"
#include "LPlayer.h"

class LPlayingField;

class LMaster
{

private:
	IVMaster* vMaster;
	LPlayingField* playingField;
	LPlayer* lPlayer;

public:
	LMaster(IVMaster* vMaster);
	~LMaster();

	IVMaster* getVMaster();
	LPlayingField * getLPlayingField();
	void startNewGame();
	LPlayer* getPlayer();

};
