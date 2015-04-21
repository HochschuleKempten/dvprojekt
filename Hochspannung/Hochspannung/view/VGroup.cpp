#include "VGroup.h"
#include "VButton.h"
#include "VTextfield.h"
#include "VText.h"
NAMESPACE_VIEW_B

VGroup::VGroup()
{
}

VGroup::VGroup(CViewport* viewport, CFloatRect floatRect)
{
	m_viewport = viewport;
	m_rect = floatRect;
}

VGroup::~VGroup()
{
	for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
	{
		delete lIterGUIObjects->second;
	}
	m_guiObjects.clear();
}


	void VGroup::onNotify(Event events)
{
	switch (events)
	{
	default:
		notify(events);		
	}
}


void VGroup::switchOn()
{
	for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
	{
		lIterGUIObjects->second->switchOn();
	}

	m_bOn = true;
}

void VGroup::switchOff()
{
	for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
	{
		lIterGUIObjects->second->switchOff();
	}

	m_bOn = false;
}
NAMESPACE_VIEW_E