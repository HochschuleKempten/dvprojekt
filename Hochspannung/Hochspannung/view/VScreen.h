#pragma once

#include "IViewGUIContainer.h"
#include "IViewObserver.h"
#include "IViewSubject.h"


//---------------------------------------------------
// Klasse: VScreen
// Beschreibung:
// Repräsentiert verschiedene Fenster Hauptmenü,Optionen, Credits,Ingame
// Autor: Patrick Benkowitsch
//---------------------------------------------------
NAMESPACE_VIEW_B

class VScreen:public IViewObserver,public IViewSubject
{
public:
	enum ScreenType
	{
		MainMenue,
		Options,
		Credits,
		Ingame
	};

	VScreen();
	VScreen(CViewport* viewport, VScreen::ScreenType screentype, CFrame* frame);
	VScreen(VScreen::ScreenType screentype, CFrame* frame);
	void switchOn();
	void switchOff();
	void addContainer(IViewGUIContainer::ContainerType containerType,CFloatRect floatRect,string Name);
	IViewGUIContainer* getContainer(string sName);
	virtual void onNotify(IViewObserver::Event);
	map<string, IViewGUIContainer*>getGuiContainerMap();
	
	~VScreen();
	bool isOn();
	ScreenType m_screenType;
private:
	bool m_isOn;
	map<string,IViewGUIContainer*> m_Guicontainer;
	map<string, IViewGUIContainer*>::iterator m_IterGuicontainer;
	CViewport m_viewport;
	CCamera m_camera;
	
	
};

NAMESPACE_VIEW_E