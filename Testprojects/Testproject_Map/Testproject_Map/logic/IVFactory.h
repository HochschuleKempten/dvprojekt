#pragma once
#include "IVPlayingField.h"

class IVFactory
{
public:
	virtual ~IVFactory(){};
	virtual IVPlayingField* createPlayingField() = 0;
};

