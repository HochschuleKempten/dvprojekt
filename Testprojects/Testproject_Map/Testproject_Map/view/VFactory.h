#pragma once
#include "../logic/IVFactory.h"
#include "VMaster.h"

NAMESPACE_VIEW_B

class VFactory:
	public IVFactory
{
public:
	VFactory(IVMaster* vMaster);
	virtual ~VFactory();
	virtual IVPlayingField* createPlayingField(LPlayingField* field);
};

NAMESPACE_VIEW_E