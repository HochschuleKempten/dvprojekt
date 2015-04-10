#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class VMaster;

class IViewObject
{
protected:
	CPlacement* m_zp = nullptr;
	VMaster* vMaster;

public:
	inline IViewObject(VMaster* vMaster, CPlacement* m_zp)
		: vMaster(vMaster), m_zp(m_zp)
	{}
	inline virtual ~IViewObject()
	{}

	inline CPlacement* getPlacement()
	{
		ASSERT(m_zp != nullptr, "The placement is not initialized");

		return m_zp;
	}
};


NAMESPACE_VIEW_E
