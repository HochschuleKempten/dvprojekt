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
		delete(*lIterGUIObjects);
	}
	delete m_background;
}

void VDialog::addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewUIObserver::Event clickAction)
{
	VButton* vButton = new VButton(m_viewport, createRelativeRectangle(&m_rect,&rect), MaterialNormal, MaterialHover, clickAction);

	vButton->addObserver(this);

	m_guiObjects.push_back(vButton);
}

void VDialog::addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder)
	{
		auto* textfield = new VTextfield(m_viewport, createRelativeRectangle(&m_rect, &rect), MaterialNormal, MaterialHover, MaterialActive, MaxChars, Placeholder);

		textfield->addObserver(this);

		m_guiObjects.push_back(textfield);
	}

	void VDialog::addText(CFloatRect rect, CWritingFont* writingFont, string text)
	{
		auto* texti = new VText(m_viewport, createRelativeRectangle(&m_rect, &rect), writingFont, text);

		texti->addObserver(this);

		m_guiObjects.push_back(texti);
	}

	void VDialog::onNotify(IViewUIObserver::Event events)
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
		(*lIterGUIObjects)->switchOn();
		
	}
	m_background->SwitchOn();

	m_bOn = true;

}

void VDialog::switchOff()
{
	for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
	{
		
		(*lIterGUIObjects)->switchOff();
		
	}
	m_background->SwitchOff();
	m_bOn = false;
}
NAMESPACE_VIEW_E