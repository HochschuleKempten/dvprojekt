#pragma once

#include "IViewObject.h"

NAMESPACE_VIEW_B


class IViewBuilding : public IViewObject
{
public:
	IViewBuilding(VMaster* vMaster)
		: IViewObject(vMaster)
	{}
	virtual ~IViewBuilding()
	{}
};


NAMESPACE_VIEW_E
