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
//template<typename T>
//struct Entity
//{
//	T* instance;
//};
	virtual ~IViewObserver() {}
	
	virtual void onNotify(Event evente)=0;
	//virtual void onNotify(int Instance, Event evente) = 0;
};
NAMESPACE_VIEW_E