#pragma once

#include "IVMaster.h"

class IView
{
protected:
	IVMaster* master;

public:
	IView(IVMaster* master)
		: master(master)
	{}
	virtual ~IView()
	{}

	virtual void init() = 0;

};
