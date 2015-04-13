#include "VDialog.h"
NAMESPACE_VIEW_B

VDialog::VDialog()
{
}

VDialog::VDialog(CFloatRect floatRect, CViewport& viewport, CMaterial* materialBackground)
{
	
	m_viewport = &viewport;
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
	VButton* vButton = new VButton(m_viewport, rect, MaterialNormal, MaterialHover, clickAction);

	vButton->addObserver(this);

	m_guiObjects.push_back(vButton);
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
NAMESPACE_VIEW_E