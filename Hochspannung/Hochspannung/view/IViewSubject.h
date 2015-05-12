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
		virtual ~IViewSubject()
		{
		};

	public:
		void addObserver(IViewUIObserver* observer)
		{
			observers_.push_back(observer);
		}

		void removeObserver(IViewUIObserver* observer)
		{
			observers_.remove(observer);
		}

		void addObserverExt(IViewUIObserver* observer)
		{
			observersExt_.push_back(observer);
		}

		void removeObserverExt(IViewUIObserver* observer)
		{
			observersExt_.remove(observer);
		}

	protected:
		void notify(IViewUIObserver::Event evente)
		{
			for (lIterObservers = observers_.begin(); lIterObservers != observers_.end(); ++lIterObservers)
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

		void notifyExt(IViewUIObserver::Event evente, string sName)
		{
			for (lIterObserversExt = observersExt_.begin(); lIterObserversExt != observersExt_.end(); ++lIterObserversExt)
			{
				
					(*lIterObserversExt)->onNotifyExt(evente,sName);
				
			}
		}

	private:
		list<IViewUIObserver*> observers_;
		list<IViewUIObserver*>::iterator lIterObservers;

		list<IViewUIObserver*> observersExt_;
		list<IViewUIObserver*>::iterator lIterObserversExt;
	};

	NAMESPACE_VIEW_E
