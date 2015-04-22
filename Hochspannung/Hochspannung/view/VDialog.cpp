#include "VDialog.h"
#include "VTextfield.h"
#include "VText.h"
NAMESPACE_VIEW_B

VDialog::VDialog()
{
}

VDialog::VDialog(CViewport* viewport, CFloatRect floatRect, CMaterial* materialBackground)
{
	
	m_viewport = viewport;
	m_rect = floatRect;
	m_background = new COverlay();
	m_background->SetLayer(0.9);
	m_background->Init(materialBackground, m_rect);
	m_viewport->AddOverlay(m_background);
}

VDialog::~VDialog()
{
	for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
	{
		delete lIterGUIObjects->second;
	}
	m_guiObjects.clear();
	delete m_background;
}

void VDialog::addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction,string sName)
{
	m_guiObjects[sName] = new VButton(m_viewport, createRelativeRectangle(&m_rect, &rect), MaterialNormal, MaterialHover, clickAction);

	m_guiObjects[sName]->addObserver(this);

	
}

void VDialog::addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder, string sName)
	{
		m_guiObjects[sName] = new VTextfield(m_viewport, createRelativeRectangle(&m_rect, &rect), MaterialNormal, MaterialHover, MaterialActive, MaxChars, Placeholder);

		m_guiObjects[sName]->addObserver(this);

		
	}

void VDialog::addText(CFloatRect rect, CWritingFont* writingFont, string text, string sName)
	{
		m_guiObjects[sName] = new VText(m_viewport, createRelativeRectangle(&m_rect, &rect), writingFont, text);

		m_guiObjects[sName]->addObserver(this);

	
	}

	void VDialog::onNotify(Event events)
{
	switch (events)
	{
	default:
			notify(events);

	}

}


void VDialog::switchOn()
{
	for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
	{
		lIterGUIObjects->second->switchOn();
		
	}
	m_background->SwitchOn();

	m_bOn = true;

}

void VDialog::switchOff()
{
	for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
	{
		
		lIterGUIObjects->second->switchOff();
		
	}
	m_background->SwitchOff();
	m_bOn = false;
}
NAMESPACE_VIEW_E