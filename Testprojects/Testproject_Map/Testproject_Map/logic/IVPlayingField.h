#pragma once

#include "IView.h"

class LPlayingField;

class IVPlayingField : public IView
{
protected:
	LPlayingField* field;

public:
	IVPlayingField(LPlayingField* playingField)
		: field(playingField)
	{}
	virtual ~IVPlayingField()
	{}

	virtual void initPlayingField() = 0;
};
