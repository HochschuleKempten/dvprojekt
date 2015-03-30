#pragma once

#include "IView.h"

class LPlayingField;

class IVPlayingField : public IView
{
protected:
	LPlayingField* field;

public:
	IVPlayingField(LPlayingField* field)
		: field(field)
	{}
	virtual ~IVPlayingField()
	{}
};
