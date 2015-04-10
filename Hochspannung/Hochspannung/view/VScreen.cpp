#include "VScreen.h"
#include "VGroup.h"
#include "../logic/LUtility.h"

NAMESPACE_VIEW_B
VScreen::VScreen()
{
}
VScreen::VScreen(VScreen::ScreenType screentype,CFrame* frame) :m_isOn(true)
{
	m_screenType = screentype;
	m_camera.Init(120);
	m_camera.SetOrthoOn();
	m_viewport.InitFull(&m_camera);
	frame->AddViewport(&m_viewport);

}

VScreen::~VScreen()
{
	for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer)
	{
		delete m_IterGuicontainer->second;
	}
	m_Guicontainer.clear();
}

void VScreen::switchOn()
{
	m_viewport.SwitchOn();
	m_isOn = true;
}
void VScreen::switchOff()
{
	m_viewport.SwitchOff();
	m_isOn = false;
}

void VScreen::addContainer(IViewGUIContainer::ContainerType containerType, CFloatRect floatRect,string sName)
{
	
	switch (containerType)
	{
	case IViewGUIContainer::Group:
		m_Guicontainer[sName] = new VGroup(floatRect, m_viewport);
		m_Guicontainer[sName]->addObserver(this);
		break;
	}
	
}

void VScreen::onNotify(IViewObserver::Event events)
{
	OutputDebugString("Nachricht bei Screen-Observer angekommen\n");
	switch (events)
	{
	default:
		OutputDebugString("Screen keine Lösung. Benachrichtigt alle Beobachter\n");
		notify(events);
		
		break;
	}
}

IViewGUIContainer* VScreen::getContainer(string sName)
{
	ASSERT(m_Guicontainer.find(sName) != m_Guicontainer.end(),"GUIContainer not available");
		return m_Guicontainer[sName];
}


map<string, IViewGUIContainer*>VScreen::getGuiContainerMap()
{
	return m_Guicontainer;
}

bool VScreen::isOn()
{
	return m_isOn;
}

NAMESPACE_VIEW_E