#pragma once

#include "IViewObject.h"

NAMESPACE_VIEW_B


class IViewBuilding : public IViewObject
{
public:
	inline IViewBuilding(VMaster* vMaster, CPlacement* m_zp)
		: IViewObject(vMaster, m_zp)
	{}
	inline virtual ~IViewBuilding()
	{}
};


NAMESPACE_VIEW_E
