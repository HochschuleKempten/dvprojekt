#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class VMaster;

class IViewObject
{
protected:
	CPlacement* placementPointer = nullptr;
	VMaster* vMaster;

public:
	inline IViewObject(VMaster* vMaster, CPlacement* placementPointer)
		: vMaster(vMaster), placementPointer(placementPointer)
	{}
	inline virtual ~IViewObject()
	{}

	inline CPlacement* getPlacement()
	{
		ASSERT(placementPointer != nullptr, "The placement is not initialized");

		return placementPointer;
	}
};


NAMESPACE_VIEW_E
