#pragma once

#include "IViewObject.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


class ILBuilding;

class IViewBuilding : public IViewObject
{
public:
	enum action
	{
		Undefined,
		switchOn,
		switchOff,
		sell,
		upgrade,
		sabotageDeactivate,
		sabotageRemove,
		sabotageResource
	};

public:
	inline IViewBuilding(VMaster* vMaster, CPlacement* m_zp)
		: IViewObject(vMaster, m_zp)
	{}
	inline virtual ~IViewBuilding()
	{}

	virtual CPlacement* getPlacementSecond() const
	{
		return nullptr;
	}

	virtual ILBuilding* getLBuilding() = 0;

	virtual bool clicked(action action) = 0;

	static bool isSabotageAction(const action a)
	{
		return a == sabotageDeactivate || a == sabotageRemove || a == sabotageResource;
	}
	
};


NAMESPACE_VIEW_E
