#pragma once

class IVPlayingField;
class LPlayingField;

class IVFactory
{
public:
	IVFactory()
	{}
	virtual ~IVFactory(){};
	virtual IVPlayingField* createPlayingField(LPlayingField* field) = 0;
};

