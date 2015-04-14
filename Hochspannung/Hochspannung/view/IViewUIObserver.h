#pragma once
#include "VGeneral.h"

NAMESPACE_VIEW_B
//---------------------------------------------------
// IViewUIObserver Interface
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------



class IViewUIObserver
{
public:
	enum Event
	{
		START_GAME,
		STOP_GAME,
		QUIT_GAME,
		MainOptions,
		SWITCH_TO_SPIELMODUS,
		SWITCH_TO_MAINMENUE,
		NOTHING
	};

	virtual ~IViewUIObserver() {}

	virtual void onNotify(Event evente) = 0;

};
NAMESPACE_VIEW_E