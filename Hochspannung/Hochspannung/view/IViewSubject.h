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
		void notify(const IViewUIObserver::Event& evente)
		{
			for (IViewUIObserver* obs : observers_)
			{
				if (evente == IViewUIObserver::QUIT_GAME)
				{
					obs->onNotify(evente);
					break;
				}
				else
				{
					obs->onNotify(evente);
				}
			}
		}

		void notifyExt(const IViewUIObserver::Event& evente, const std::string& sName)
		{
			for (IViewUIObserver* obsExt : observersExt_)
			{
				
					obsExt->onNotifyExt(evente,sName);
				
			}
		}

	private:
		std::list<IViewUIObserver*> observers_;
		std::list<IViewUIObserver*> observersExt_;
		
	};

	NAMESPACE_VIEW_E
