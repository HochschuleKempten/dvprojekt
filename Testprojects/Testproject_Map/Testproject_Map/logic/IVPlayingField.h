#pragma once

#include "IView.h"

class LPlayingField;

class IVPlayingField : public IView
{
protected:
	LPlayingField* lPlayingField;

public:
	IVPlayingField(LPlayingField* lPlayingField)
		: lPlayingField(lPlayingField)
	{}
	virtual ~IVPlayingField()
	{}

	virtual void initPlayingField() = 0;
};
