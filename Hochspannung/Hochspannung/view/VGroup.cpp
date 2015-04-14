#include "VGroup.h"
#include "VButton.h"
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
	VButton* vButton = new VButton(m_viewport,rect, MaterialNormal, MaterialHover, clickAction);
	
	vButton->addObserver(this);
	
	m_guiObjects.push_back(vButton);
}

void VGroup::onNotify(IViewUIObserver::Event events)
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

void VGroup::switchOn()
{

}

void VGroup::switchOff()
{
	for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
	{
		(*lIterGUIObjects)->switchOff();
	}
}
NAMESPACE_VIEW_E