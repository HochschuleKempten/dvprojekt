#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class IViewModel
{
	NON_COPYABLE(IViewModel);
	
protected:
	CPlacement m_zpMain;

public:
	inline IViewModel()
	{}
	virtual inline ~IViewModel()
	{}

	virtual float getHeight() = 0;
	virtual float getWidth() = 0;

	inline CPlacement* getMainPlacement()
	{
		return &m_zpMain;
	}
};


NAMESPACE_VIEW_E
