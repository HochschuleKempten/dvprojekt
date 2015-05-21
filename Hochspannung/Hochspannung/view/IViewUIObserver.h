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
		SWITCH_TO_SPIELMODUS,
		SWITCH_TO_MAINMENUE,
		SWITCH_TO_CREDITS,
		SWITCH_TO_OPTIONS,
		SWITCH_TO_LOBBY,
		SEARCH_IP,
		SWITCH_TO_REGISTER_BUILDING,
		SWITCH_TO_REGISTER_SABOTAGE,
		SWITCH_TO_REGISTER_STATISTICS,
		SELECT_BUILDING_WINDMILL,
		SELECT_BUILDING_COALPOWERPLANT,
		SELECT_BUILDING_OILPOWERPLANT,
		SELECT_BUILDING_NUCLEARPOWERPLANT,
		SELECT_BUILDING_HYDROPOWERPLANT,
		SELECT_BUILDING_SOLARPOWERPLANT,
		SELECT_BUILDING_POWERLINE,
		LOBBY_HOST_GAME,
		LOBBY_JOIN_GAME,
		LIST_ITEM_SELECTED,
		SELECT_SABOTAGE_POWERLINECUT,
		SELECT_SABOTAGE_STRIKE,
		SELECT_SABOTAGE_BOMB,
		NOTHING
	};

	virtual ~IViewUIObserver() {}

	virtual void onNotify(const Event& evente) = 0;
	virtual void onNotifyExt(const Event& evente, const std::string& sName) 
	{};

};
NAMESPACE_VIEW_E