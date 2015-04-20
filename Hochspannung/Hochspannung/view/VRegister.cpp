#include "VRegister.h"

NAMESPACE_VIEW_B
VRegister::VRegister()
{
}

	VRegister::VRegister(CFloatRect floatRect, CViewport* viewport, CMaterial* MaterialNormal)
	{
	}

	VRegister::~VRegister()
{
}

	void VRegister::addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewUIObserver::Event clickAction)
	{
		VButton* vButton = new VButton(m_viewport, createRelativeRectangle(&m_rect, &rect), MaterialNormal, MaterialHover, clickAction);

		vButton->addObserver(this);

		m_guiObjects.push_back(vButton);
	}

	void VRegister::addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder)
	{
		auto* textfield = new VTextfield(m_viewport, createRelativeRectangle(&m_rect, &rect), MaterialNormal, MaterialHover, MaterialActive, MaxChars, Placeholder);

		textfield->addObserver(this);

		m_guiObjects.push_back(textfield);
	}

	void VRegister::addText(CFloatRect rect, CWritingFont* writingFont, string text)
	{
		auto* texti = new VText(m_viewport, createRelativeRectangle(&m_rect, &rect), writingFont, text);

		texti->addObserver(this);

		m_guiObjects.push_back(texti);
	}

	void VRegister::onNotify(Event events)
	{
		switch (events)
		{
		default:
				notify(events);

		}
	}


	void VRegister::switchOn()
	{
		for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
		{
			(*lIterGUIObjects)->switchOn();

		}
		m_background->SwitchOn();

		m_bOn = true;
	}


	void VRegister::switchOff()
	{
		for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
		{
			
			(*lIterGUIObjects)->switchOff();

		}
		m_background->SwitchOff();
		m_bOn = false;
	}

	NAMESPACE_VIEW_E