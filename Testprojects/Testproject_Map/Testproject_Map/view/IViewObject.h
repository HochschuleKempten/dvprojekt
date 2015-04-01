#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class VMaster;

class IViewObject
{
protected:
	CPlacement m_zp;
	CMaterial m_zm;
	VMaster* vMaster;

public:
	IViewObject(VMaster* vMaster)
		: vMaster(vMaster)
	{}
	virtual ~IViewObject()
	{}

	CPlacement* getPlacement()
	{
		return &m_zp;
	}
};


NAMESPACE_VIEW_E
