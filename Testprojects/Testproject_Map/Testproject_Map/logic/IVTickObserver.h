#pragma once

class IVTickObserver
{
public:
	virtual ~IVTickObserver()
	{}

	virtual void tick(const float fTimeDelta) = 0;
};
