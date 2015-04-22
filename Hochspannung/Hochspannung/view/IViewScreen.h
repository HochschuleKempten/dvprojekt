#pragma once
#include "VGeneral.h"
#include "IViewGUIContainer.h"
#include "IViewUIObserver.h"
#include "IViewSubject.h"
#include "VGroup.h"
#include "VMaterialLoader.h"
#include "VDialog.h"

NAMESPACE_VIEW_B
//---------------------------------------------------
// IScreen Interface
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------



class IViewScreen:public IViewUIObserver, public IViewSubject
{
public:

	virtual ~IViewScreen() {}

	enum ScreenType
	{
		MainMenue,
		Options,
		Credits,
		Ingame,
		Spielmoduswahl,
		Lobby
	};

	virtual void switchOn()
	{
		m_viewport->SwitchOn();
		m_isOn = true;
	}
	virtual void switchOff()
	{
		m_viewport->SwitchOff();
		m_isOn = false;
	}
	inline void addContainer(CViewport* viewport,const IViewGUIContainer::ContainerType& containerType, const CFloatRect& floatRect, const string& sName)
	{
		m_viewport = viewport;
		switch (containerType)
		{
		case IViewGUIContainer::Group:
			m_Guicontainer[sName] = new VGroup(m_viewport,floatRect);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::Dialog:
			m_Guicontainer[sName] = new VDialog(m_viewport,floatRect,&VMaterialLoader::materialDialogBackground);
			m_Guicontainer[sName]->addObserver(this);
			break;
		}
	}
	IViewGUIContainer* getContainer(string sName)
	{
		ASSERT(m_Guicontainer.find(sName) != m_Guicontainer.end(), "GUIContainer not available");
		return m_Guicontainer[sName];
	}
	map<string, IViewGUIContainer*>getGuiContainerMap()
	{
		return m_Guicontainer;
	}
	bool isOn()
	{
		return m_isOn;
	}
	virtual void checkShortcut(CDeviceKeyboard* keyboard)=0;
	//virtual void resize(int width, int height);
protected:	
	map<string, IViewGUIContainer*> m_Guicontainer;
	map<string, IViewGUIContainer*>::iterator m_IterGuicontainer;
	
	CViewport* m_viewport;
	CCamera m_camera;
	ScreenType m_screenType;
	bool m_isOn = false;
};

	

	NAMESPACE_VIEW_E