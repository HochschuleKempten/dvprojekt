#pragma once
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
	inline virtual ~IVMaster()
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
	virtual void gameOver() = 0;
	virtual void updateMoney(const int money) = 0;
	//todo (V) implement
	/*virtual void pauseGame() = 0;
	virtual void continueGame() = 0;*/
};

NAMESPACE_LOGIC_E