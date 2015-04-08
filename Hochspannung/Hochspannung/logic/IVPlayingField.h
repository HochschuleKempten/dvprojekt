#pragma once

#include "IView.h"
#include <memory>

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

	virtual void removeObject(const int x, const int y) = 0;
};
