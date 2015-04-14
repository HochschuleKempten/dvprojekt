#pragma once

#include"VButton.h"
#include"IViewUIObserver.h"
#include"IViewSubject.h"

NAMESPACE_VIEW_B

//---------------------------------------------------
// Interface:IGUIContainer
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------

class IViewGUIContainer:public IViewUIObserver,public IViewSubject
{
public:
	enum ContainerType
	{
		Group,
		Dialog

	};

	virtual void switchOn()=0;
	virtual void switchOff() = 0;
	virtual bool isOn()
	{
		return m_bOn;
	}
	virtual void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewUIObserver::Event clickAction) = 0;
	virtual list<IViewGUIObject*> getGuiObjectList()=0;
	virtual ~IViewGUIContainer(){};
protected:
	bool m_bOn = true;
};

NAMESPACE_VIEW_E