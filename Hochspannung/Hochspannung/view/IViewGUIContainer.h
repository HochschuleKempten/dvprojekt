#pragma once

#include"VButton.h"
#include"IViewObserver.h"
#include"IViewSubject.h"

NAMESPACE_VIEW_B

//---------------------------------------------------
// Interface:IGUIContainer
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------

class IViewGUIContainer:public IViewObserver,public IViewSubject
{
public:
	enum ContainerType
	{
		Group,

	};

	virtual void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewObserver::Event clickAction) = 0;
	virtual list<IViewGUIObject*> getGuiObjectList()=0;
	virtual ~IViewGUIContainer(){};
private:
	list<VButton> cgButtons;
};

NAMESPACE_VIEW_E