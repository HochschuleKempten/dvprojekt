#include "VButton.h"
NAMESPACE_VIEW_B

VButton::VButton() :
m_bHasHover(false)
{

}
VButton::VButton(CViewport* viewport, CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewUIObserver::Event clickAction) :
m_bHasHover(false),
action(IViewUIObserver::NOTHING)
{
	m_zoNormal = new COverlay();
	m_zoNormal->Init(MaterialNormal, rect);

	m_zoHover = new COverlay();
	m_zoHover->Init(MaterialHover, rect);
	m_bHasHover = true;
	m_zfrRect = rect;
	action = clickAction;

	viewport->AddOverlay(getNormalOverlay());



	viewport->AddOverlay(getHoverOverlay());


}
VButton::~VButton()
{
	delete m_zoNormal;
	delete m_zoHover;
}

//Events
void VButton::onMouseOver(void)
{
	m_zoNormal->SwitchOff();
	m_zoHover->SwitchOn();
}
void VButton::onMouseOut(void)
{
	m_zoHover->SwitchOff();
	m_zoNormal->SwitchOn();
}
void VButton::onMouseClickLeft(void)
{
	notify(action);
	
}
void VButton::onMouseClickRight(void)
{
	//ToDo
}


//Getter 
bool VButton::bGetHasHover()
{
	return this->m_bHasHover;
}

COverlay* VButton::getNormalOverlay()
{
	return m_zoNormal;
}

COverlay* VButton::getHoverOverlay()
{
	return m_zoHover;
}

CFloatRect VButton::getRectangle()
{
	return m_zfrRect;
}

	void VButton::switchOn()
{
	m_zoNormal->SwitchOn();
	m_zoHover->SwitchOff();
}
void VButton::switchOff()
{
	m_zoNormal->SwitchOff();
	m_zoHover->SwitchOff();
}
NAMESPACE_VIEW_E