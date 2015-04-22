#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class IViewModel : public CPlacement
{
public:
	inline IViewModel()
	{}
	inline virtual ~IViewModel()
	{}

	virtual float getHeight() = 0;
	virtual float getWidth() = 0;
};


NAMESPACE_VIEW_E
