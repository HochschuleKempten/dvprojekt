#include "VDialog.h"
#include "VTextfield.h"
NAMESPACE_VIEW_B

VDialog::VDialog()
{
}

VDialog::VDialog(CFloatRect floatRect, CViewport* viewport, CMaterial* materialBackground)
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
	/*CFloatRect rectRelative;
	rectRelative = CFloatRect(m_rect.GetXPos() + (m_rect.GetXSize() * rect.GetXPos()), m_rect.GetYPos() + (m_rect.GetYSize() * rect.GetYPos()),m_rect.GetXSize()*rect.GetXSize(), m_rect.GetYSize()*rect.GetYSize());
*/
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

	void VDialog::onNotify(IViewUIObserver::Event events)
{
	OutputDebugString("Nachricht bei Group-Observer angekommen\n");
	switch (events)
	{
	default:
		OutputDebugString("Group keine Lösung. Benachrichtigt alle Beobachter\n");
		notify(events);

	}

}

list<IViewGUIObject*> VDialog::getGuiObjectList()
{
	return m_guiObjects;
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
		//(*lIterGUIObjects)->switchOff();
		(*lIterGUIObjects)->switchOff();
		
	}
	m_background->SwitchOff();
	m_bOn = false;
}
NAMESPACE_VIEW_E