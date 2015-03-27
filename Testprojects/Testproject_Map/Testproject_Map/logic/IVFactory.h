#pragma once

class IVPlayingField;
class IVMaster;
class LPlayingField;

class IVFactory
{
public:
	virtual ~IVFactory(){};
	virtual IVPlayingField* createPlayingField(IVMaster* master, LPlayingField* field) = 0;
};

