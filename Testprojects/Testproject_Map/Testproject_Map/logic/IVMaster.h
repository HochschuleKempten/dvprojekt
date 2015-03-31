#pragma once

class IVFactory;

class IVMaster
{
public:
	virtual ~IVMaster()
	{}

	virtual IVFactory* getFactory() = 0;
};
