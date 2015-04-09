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

#define SET_NAME_AND_COORDINATES std::stringstream stream; \
								 stream << getClassName(this) << ";" << x << ";" << y;	\
								 m_zp.SetName(stream.str().c_str());


NAMESPACE_VIEW_E
