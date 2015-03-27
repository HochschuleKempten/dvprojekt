#pragma once
#include "IVMaster.h"
#define SIZE 1000

class LPlayingField;

class LMaster
{

private: 
	LPlayingField* playingField;
	IVMaster* master;

public:
	LMaster(IVMaster* master);
	~LMaster();

	IVMaster* getMaster()
	{
		return master;
	}
};

