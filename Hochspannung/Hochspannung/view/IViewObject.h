#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class VMaster;

class IViewObject
{
	NON_COPYABLE(IViewObject);

protected:
	VMaster* vMaster;
	CPlacement* ptrPlacement;

public:
	inline IViewObject(VMaster* vMaster, CPlacement* placementPointer)
		: vMaster(vMaster), ptrPlacement(placementPointer)
	{}
	inline virtual ~IViewObject()
	{}

	inline CPlacement* getPlacement()
	{
		ASSERT(ptrPlacement != nullptr, "The placement is not initialized");

		return ptrPlacement;
	}
	VMaster* getVMaster() const
	{
		return vMaster;
	}
};


NAMESPACE_VIEW_E
