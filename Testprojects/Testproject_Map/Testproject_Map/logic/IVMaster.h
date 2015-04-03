#pragma once

class IVFactory;

class IVMaster
{
public:
	virtual ~IVMaster()
	{}

	//TODO (V) observer --> call per tick

	virtual IVFactory* getFactory() = 0;
};
