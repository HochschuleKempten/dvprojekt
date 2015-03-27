#pragma once
#include "../logic/IVFactory.h"
#include "VMaster.h"

NAMESPACE_VIEW_B

class VFactory:
	public IVFactory
{
public:
	virtual IVPlayingField* createPlayingField(IVMaster* master, LPlayingField* field);
};

NAMESPACE_VIEW_E