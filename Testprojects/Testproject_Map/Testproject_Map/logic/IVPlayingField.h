#pragma once

#include "IView.h"

class LPlayingField;

class IVPlayingField : public IView
{
protected:
	LPlayingField* playingField;

public:
	IVPlayingField(LPlayingField* playingField)
		: playingField(playingField)
	{}
	virtual ~IVPlayingField()
	{}

	virtual void initPlayingField() = 0;
};
