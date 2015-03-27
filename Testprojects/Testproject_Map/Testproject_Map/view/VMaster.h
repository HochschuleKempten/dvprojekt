#pragma once

#include "../logic/IVMaster.h"

class VMaster : public IVMaster
{
public:
	void tick(float fTime, float fTimeDelta);
};
