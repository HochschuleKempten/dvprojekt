#pragma once
#include "../logic/IVFactory.h"
#include "VGeneral.h"

NAMESPACE_VIEW_B


class VMaster;

class VFactory : public IVFactory
{
private:
	VMaster* vMaster;

public:
	VFactory(VMaster* vMaster)
		: vMaster(vMaster)
	{}
	virtual ~VFactory()
	{}
	virtual IVPlayingField* createPlayingField(LPlayingField* field);
};


NAMESPACE_VIEW_E
