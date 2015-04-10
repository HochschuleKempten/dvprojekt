#pragma once
#include "VGeneral.h"

NAMESPACE_VIEW_B
//---------------------------------------------------
// IObserver Interface
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------



class IViewObserver
{
public:
enum Event
{
	START_GAME,
	STOP_GAME,
	QUIT_GAME,
	MainOptions,
	NOTHING
};

	virtual ~IViewObserver() {}
	
	virtual void onNotify(Event evente)=0;
	
};
NAMESPACE_VIEW_E