#pragma once
#include <list>
#include "IVTickObserver.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

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

NAMESPACE_LOGIC_E