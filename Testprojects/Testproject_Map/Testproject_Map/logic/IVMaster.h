#pragma once

#include "IVFactory.h"
class IView;

class IVMaster
{
public:
	virtual ~IVMaster()
	{}

	virtual IVFactory* getFactory() = 0;

	virtual void addScenegraph(IView* view) = 0;
	virtual void removeScenegraph(IView* view) = 0;
};
