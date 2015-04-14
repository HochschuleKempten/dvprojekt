#pragma once

#include "IViewObserver.h"

NAMESPACE_VIEW_B

//---------------------------------------------------
// IGUIObjekt Interface
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------

class IViewSubject
{
public:
	virtual ~IViewSubject(){};
public:
	void addObserver(IViewObserver* observer)
	{
		observers_.push_back(observer);
	}

	void removeObserver(IViewObserver* observer)
	{
		// Remove from array...
	}

protected:
	void notify(IViewObserver::Event evente)
	{
		for (lIterObservers = observers_.begin(); lIterObservers != observers_.end(); lIterObservers++)
		{

			if (evente == IViewObserver::QUIT_GAME)
			{
				(*lIterObservers)->onNotify(evente);
				break;
			}
			else
			{
				(*lIterObservers)->onNotify(evente);
			}
		}
	}
private:
	list<IViewObserver*> observers_;
	list<IViewObserver*>::iterator lIterObservers;
};
NAMESPACE_VIEW_E