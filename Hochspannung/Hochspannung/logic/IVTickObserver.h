#pragma once
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class IVTickObserver
{
public:
	virtual ~IVTickObserver()
	{}

	virtual void tick(const float fTimeDelta) = 0;
};

NAMESPACE_LOGIC_E