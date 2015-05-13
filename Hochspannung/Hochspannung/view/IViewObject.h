#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class VMaster;

class IViewObject
{
	NON_COPYABLE(IViewObject);

public:
	enum action
	{
		switchOnOff,
		upgrade,
		remove
	};

protected:
	VMaster* vMaster;
	CPlacement* placementPointer;

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
	VMaster* getVMaster() const
	{
		return vMaster;
	}
};


NAMESPACE_VIEW_E
