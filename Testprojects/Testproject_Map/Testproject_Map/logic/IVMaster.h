#pragma once

#include "IVFactory.h"
class IView;

class IVMaster
{
public:
	virtual ~IVMaster()
	{}

	virtual IVFactory* getFactory() = 0;
};
