#pragma once

#include "IView.h"

class IVMaster
{
public:
	virtual void addScenegraph(IView* view) = 0;
	virtual void removeScenegraph(IView* view) = 0;
};
