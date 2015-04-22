#pragma once

#include"VButton.h"
#include"IViewUIObserver.h"
#include"IViewSubject.h"
#include "VTextfield.h"
#include "VText.h"


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
	virtual void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction,string sName)
	{
		m_guiObjects[sName] = new VButton(m_viewport, rect, MaterialNormal, MaterialHover, clickAction);

		m_guiObjects[sName]->addObserver(this);

		
	}
	virtual void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder,string sName)
	{
		m_guiObjects[sName] = new VTextfield(m_viewport, rect, MaterialNormal, MaterialHover, MaterialActive, MaxChars, Placeholder);

		m_guiObjects[sName]->addObserver(this);

		
	}
	virtual void addText( CFloatRect rect, CWritingFont* writingFont, string text,string sName)
	{
		m_guiObjects[sName] = new VText(m_viewport, rect, writingFont, text);

		m_guiObjects[sName]->addObserver(this);

	}
	
	virtual void addContainer(const IViewGUIContainer::ContainerType& containerType, const CFloatRect& floatRect, const string& sName)
	{
		
	};
	

	virtual ~IViewGUIContainer(){};

	IViewGUIContainer* getContainer(string sName)
	{
		ASSERT(m_Guicontainer.find(sName) != m_Guicontainer.end(), "GUIContainer not available");
		return m_Guicontainer[sName];
	}
	map<string, IViewGUIContainer*>getGuiContainerMap()
	{
		return m_Guicontainer;
	}

	map<string, IViewGUIObject*> getGuiObjectList()
	{
		return m_guiObjects;
	}
	IViewGUIObject* getGuiObject(string sName)
	{
		return m_guiObjects[sName];
	}
protected:

	bool m_bOn = true;
	CViewport* m_viewport;
	map<string,IViewGUIObject*> m_guiObjects;
	map<string,IViewGUIObject*>::iterator lIterGUIObjects;
	
	map<string, IViewGUIContainer*> m_Guicontainer;
	map<string, IViewGUIContainer*>::iterator m_IterGuicontainer;

	virtual CFloatRect createRelativeRectangle(CFloatRect* RelativeToRect, CFloatRect* RelativeRect)
	{
		 
		return CFloatRect(RelativeToRect->GetXPos() + (RelativeToRect->GetXSize() * RelativeRect->GetXPos()), RelativeToRect->GetYPos() + (RelativeToRect->GetYSize() * RelativeRect->GetYPos()),
			RelativeToRect->GetXSize()*RelativeRect->GetXSize(), RelativeToRect->GetYSize()*RelativeRect->GetYSize());
	}
};

NAMESPACE_VIEW_E
