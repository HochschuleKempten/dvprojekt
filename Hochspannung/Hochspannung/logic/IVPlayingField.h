#pragma once

#include <memory>

class LPlayingField;

class IVPlayingField
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

	virtual void objectRemoved(const int x, const int y) = 0;
};
