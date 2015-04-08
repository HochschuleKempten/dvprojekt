#pragma once

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
};
