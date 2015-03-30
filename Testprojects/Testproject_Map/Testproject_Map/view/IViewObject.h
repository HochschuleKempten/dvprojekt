#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class VMaster;

class IViewObject
{
protected:
	CGeo* m_zg = nullptr;
	CPlacement m_zp;
	CMaterial m_zm;
	VMaster* vMaster;

public:
	IViewObject(VMaster* vMaster)
		: vMaster(vMaster)
	{}
	IViewObject(VMaster* vMaster, CGeo* geo)
		: vMaster(vMaster), m_zg(geo)
	{}
	virtual ~IViewObject()
	{
		if (m_zg != nullptr) {
			delete m_zg;
		}
	}

	CPlacement* getPlacement()
	{
		return &m_zp;
	}
};


NAMESPACE_VIEW_E
