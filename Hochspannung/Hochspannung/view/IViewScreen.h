#pragma once
#include "VGeneral.h"
#include "IViewGUIContainer.h"
#include "IViewUIObserver.h"
#include "IViewSubject.h"
#include "VGroup.h"
#include "VMaterialLoader.h"
#include "VDialog.h"
#include "VRegister.h"
#include "VGUIArea.h"

NAMESPACE_VIEW_B


//---------------------------------------------------
// IScreen Interface
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------

class VUI;


class IViewScreen:public IViewUIObserver, public IViewSubject
{
public:
	explicit IViewScreen(VUI* vUi)
		: vUi(vUi) {}
	virtual ~IViewScreen() {}

	enum ScreenType
	{
		MainMenue,
		Options,
		Credits,
		Ingame,
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

	inline void addContainer(CViewport* viewport, const IViewGUIContainer::ContainerType& containerType, const CFloatRect& floatRect, const string& sName)
	{
		m_viewport = viewport;
		switch (containerType)
		{
		case IViewGUIContainer::Group:
			m_Guicontainer[sName] = new VGroup(m_viewport, floatRect);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::Dialog:
			m_Guicontainer[sName] = new VDialog(m_viewport, floatRect);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::Register:
			m_Guicontainer[sName] = new VRegister(floatRect, m_viewport);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::GUIArea:
			m_Guicontainer[sName] = new VGUIArea(m_viewport, floatRect);
			m_Guicontainer[sName]->addObserver(this);
			break;
		}
	}
	inline void addContainer(CViewport* viewport,const IViewGUIContainer::ContainerType& containerType, const CFloatRect& floatRect,CMaterial* materialBackground, const string& sName)
	{
		m_viewport = viewport;
		switch (containerType)
		{
		case IViewGUIContainer::Group:
			m_Guicontainer[sName] = new VGroup(m_viewport, floatRect, materialBackground);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::Dialog:
			m_Guicontainer[sName] = new VDialog(m_viewport, floatRect,materialBackground);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::Register:
			m_Guicontainer[sName] = new VRegister(floatRect, m_viewport, materialBackground);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::GUIArea:
			m_Guicontainer[sName] = new VGUIArea(m_viewport, floatRect, materialBackground);
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
	virtual void checkSpecialEvent(CDeviceCursor* cursor) = 0;
	virtual void tick() = 0;
	virtual void resize(int width, int height) = 0;
	virtual void startAnimation()
	{}
	virtual void StartEvent()
	{}
	virtual void EndEvent()
	{}
protected:	
	map<string, IViewGUIContainer*> m_Guicontainer;
	map<string, IViewGUIContainer*>::iterator m_IterGuicontainer;
	
	VUI* vUi;
	CViewport* m_viewport;
	CCamera m_camera;
	ScreenType m_screenType;
	bool m_isOn = false;
};

	

	NAMESPACE_VIEW_E