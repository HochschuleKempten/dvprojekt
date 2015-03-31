#pragma once
#include "LPlayingField.h"

class IVMaster;

class LMaster
{

private:
	IVMaster* vMaster;
	LPlayingField* playingField;

public:
	LMaster(IVMaster* vMaster);
	~LMaster();

	IVMaster* getVMaster()
	{
		return vMaster;
	}

	LPlayingField * getLPlayingField()
	{
		return playingField;
	}

	void startNewGame();
};
