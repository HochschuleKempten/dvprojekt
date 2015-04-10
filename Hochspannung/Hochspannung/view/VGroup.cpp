#include "VGroup.h"

NAMESPACE_VIEW_B

VGroup::VGroup()
{
}

VGroup::VGroup(CFloatRect floatRect,CViewport& viewport)
{
	m_viewport = &viewport;
	m_rect = floatRect;
}

VGroup::~VGroup()
{
	for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
	{
		delete(*lIterGUIObjects);
	}
}

void VGroup::addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewObserver::Event clickAction)
{
	VButton* VButton = new VButton(m_viewport,rect, MaterialNormal, MaterialHover, clickAction);

	VButton->addObserver(this);
	
	m_guiObjects.push_back(VButton);
}

void VGroup::onNotify(IViewObserver::Event events)
{
	OutputDebugString("Nachricht bei Group-Observer angekommen\n");
	switch (events)
	{
	default:
		OutputDebugString("Group keine Lösung. Benachrichtigt alle Beobachter\n");
		notify(events);
		
	}

}

list<IViewGUIObject*> VGroup::getGuiObjectList()
{
	return m_guiObjects;
}

NAMESPACE_VIEW_E