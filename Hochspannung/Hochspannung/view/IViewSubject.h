#pragma once

#include "IViewUIObserver.h"

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
	void addObserver(IViewUIObserver* observer)
	{
		observers_.push_back(observer);
	}

	void removeObserver(IViewUIObserver* observer)
	{
		// Remove from array...
	}

protected:
	void notify(IViewUIObserver::Event evente)
	{
		for (lIterObservers = observers_.begin(); lIterObservers != observers_.end(); lIterObservers++)
		{

			if (evente == IViewUIObserver::QUIT_GAME)
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
	list<IViewUIObserver*> observers_;
	list<IViewUIObserver*>::iterator lIterObservers;
};
NAMESPACE_VIEW_E