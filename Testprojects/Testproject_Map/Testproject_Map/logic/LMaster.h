#pragma once
#include "IVMaster.h"

class LPlayingField;

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
};

