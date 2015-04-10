#pragma once
#include "VGeneral.h"
#include "IViewGUIContainer.h"
#include "IViewObserver.h"
#include "IViewSubject.h"
#include "VGroup.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B
//---------------------------------------------------
// IScreen Interface
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------



class IViewScreen:public IViewObserver, public IViewSubject
{
public:

	virtual ~IViewScreen() {}

	enum ScreenType
	{
		MainMenue,
		Options,
		Credits,
		Ingame
	};

	inline void switchOn()
	{
		m_viewport.SwitchOn();
		m_isOn = true;
	}
	inline void switchOff()
	{
		m_viewport.SwitchOff();
		m_isOn = false;
	}
	inline void addContainer(const IViewGUIContainer::ContainerType& containerType, const CFloatRect& floatRect, const string& sName)
	{
		switch (containerType)
		{
		case IViewGUIContainer::Group:
			m_Guicontainer[sName] = new VGroup(floatRect, m_viewport);
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
protected:	
	map<string, IViewGUIContainer*> m_Guicontainer;
	map<string, IViewGUIContainer*>::iterator m_IterGuicontainer;
	
	CViewport m_viewport;
	CCamera m_camera;
	ScreenType m_screenType;
	bool m_isOn = false;
};
NAMESPACE_VIEW_E