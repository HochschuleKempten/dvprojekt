#include "VGroup.h"
#include "VButton.h"
#include "VTextfield.h"
#include "VText.h"
NAMESPACE_VIEW_B

VGroup::VGroup()
{
}

VGroup::VGroup(CFloatRect floatRect,CViewport* viewport)
{
	m_viewport = viewport;
	m_rect = floatRect;
}

VGroup::~VGroup()
{
	for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
	{
		delete(*lIterGUIObjects);
	}
}

void VGroup::addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewUIObserver::Event clickAction)
{
	auto* vButton = new VButton(m_viewport,rect, MaterialNormal, MaterialHover, clickAction);
	
	vButton->addObserver(this);
	
	m_guiObjects.push_back(vButton);
	
}

void VGroup::addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder)
	{
		auto* textfield = new VTextfield(m_viewport, rect, MaterialNormal, MaterialHover, MaterialActive, MaxChars,Placeholder);
		
		textfield->addObserver(this);

		m_guiObjects.push_back(textfield);
		
	}

	void VGroup::addText(CFloatRect rect, CWritingFont* writingFont, string text)
	{
		auto* texti = new VText(m_viewport, rect,writingFont,text);

		texti->addObserver(this);

		m_guiObjects.push_back(texti);
	}

	void VGroup::onNotify(Event events)
{
	switch (events)
	{
	default:
		notify(events);		
	}
}

	vector<IViewGUIObject*> VGroup::getGuiObjectList()
{
	return m_guiObjects;
}

void VGroup::switchOn()
{
	for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
	{
		(*lIterGUIObjects)->switchOn();
	}

	m_bOn = true;
}

void VGroup::switchOff()
{
	for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
	{
		(*lIterGUIObjects)->switchOff();
	}

	m_bOn = false;
}
NAMESPACE_VIEW_E