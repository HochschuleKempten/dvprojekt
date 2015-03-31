#pragma once
#include "LPlayingField.h"

class IVMaster;
class LPlayer;

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
