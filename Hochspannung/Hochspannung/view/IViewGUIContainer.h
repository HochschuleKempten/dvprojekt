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
	virtual void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewUIObserver::Event clickAction)
	{
		auto* vButton = new VButton(m_viewport, rect, MaterialNormal, MaterialHover, clickAction);

		vButton->addObserver(this);

		m_guiObjects.push_back(vButton);
		
	}
	virtual void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder)
	{
		auto* textfield = new VTextfield(m_viewport, rect, MaterialNormal, MaterialHover, MaterialActive, MaxChars, Placeholder);

		textfield->addObserver(this);

		m_guiObjects.push_back(textfield);
	}
	virtual void addText( CFloatRect rect, CWritingFont* writingFont, string text)
	{
		auto* texti = new VText(m_viewport, rect, writingFont, text);

		texti->addObserver(this);

		m_guiObjects.push_back(texti);
	}
	
	virtual ~IViewGUIContainer(){};

	vector<IViewGUIObject*> getGuiObjectList()
	{
		return m_guiObjects;
	}
protected:
	bool m_bOn = true;
	CViewport* m_viewport;
	vector<IViewGUIObject*> m_guiObjects;
	vector<IViewGUIObject*>::iterator lIterGUIObjects;
	
	virtual CFloatRect createRelativeRectangle(CFloatRect* RelativeToRect, CFloatRect* RelativeRect)
	{
		 
		return CFloatRect(RelativeToRect->GetXPos() + (RelativeToRect->GetXSize() * RelativeRect->GetXPos()), RelativeToRect->GetYPos() + (RelativeToRect->GetYSize() * RelativeRect->GetYPos()),
			RelativeToRect->GetXSize()*RelativeRect->GetXSize(), RelativeToRect->GetYSize()*RelativeRect->GetYSize());
	}
};

NAMESPACE_VIEW_E
