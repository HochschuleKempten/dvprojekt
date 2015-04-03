#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class VMaster;

class IViewObject
{
protected:
	CPlacement m_zp;//TODO (V) redesign with first real building
	CMaterial m_zm;//TODO (V) this may will be unecessary, delete it
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
