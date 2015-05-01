#pragma once

#include "IViewObject.h"

NAMESPACE_VIEW_B


class ILBuilding;

class IViewBuilding : public IViewObject
{
public:
	inline IViewBuilding(VMaster* vMaster, CPlacement* m_zp)
		: IViewObject(vMaster, m_zp)
	{}
	inline virtual ~IViewBuilding()
	{}

	virtual ILBuilding* getLBuilding() = 0;
};

#define SET_NAME_AND_COORDINATES(id) { std::stringstream stream; \
								       stream << id << ";" << x << ";" << y;	\
								       viewModel.getMainPlacement()->SetName(stream.str().c_str()); }


NAMESPACE_VIEW_E
