#pragma once

#include <list>
#include "IVTickObserver.h"

class IVFactory;

class IVMaster
{
protected:
	std::list<IVTickObserver*> observer;

	inline void updateTick(const float fTimeDelta)
	{
		for (IVTickObserver* o : observer) {
			o->tick(fTimeDelta);
		}
	}

public:
	virtual ~IVMaster()
	{}

	inline void registerObserver(IVTickObserver* observer)
	{
		this->observer.push_back(observer);
	}

	inline void unregisterObserver(IVTickObserver* observer)
	{
		this->observer.remove(observer);
	}

	virtual IVFactory* getFactory() = 0;
};
