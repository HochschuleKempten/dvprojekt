#include "VButton.h"
NAMESPACE_VIEW_B

VButton::VButton() :
	m_bHasHover(false)
{
}

VButton::VButton(CViewport* viewport, CFloatRect& rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewUIObserver::Event clickAction, const float layer) :
	m_bHasHover(false),
	action(IViewUIObserver::NOTHING)

{
	m_ObjectType = BUTTON;
	m_zfrRect = rect;
	m_zoNormal = new COverlay();
	m_zoNormal->Init(MaterialNormal, m_zfrRect);

	m_zoHover = new COverlay();
	m_zoHover->Init(MaterialHover, m_zfrRect);
	m_bHasHover = true;

	m_zoActive = m_zoHover;

	action = clickAction;

	m_fLayer = layer;

	m_zoNormal->SetLayer(m_fLayer);
	m_zoHover->SetLayer(m_fLayer);
	m_zoActive->SetLayer(m_fLayer);

	viewport->AddOverlay(getNormalOverlay());


	viewport->AddOverlay(getHoverOverlay());

	viewport->AddOverlay(getActiveOverlay());

	m_zoNormal->SwitchOn();
	m_zoHover->SwitchOff();
	m_zoActive->SwitchOff();
}

VButton::VButton(CViewport* viewport, CFloatRect& rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, IViewUIObserver::Event clickAction, const float layer):
m_bHasHover(false),
action(IViewUIObserver::NOTHING){
	m_ObjectType = BUTTON;
	m_zfrRect = rect;
	m_zoNormal = new COverlay();
	m_zoNormal->Init(MaterialNormal, m_zfrRect);

	m_zoHover = new COverlay();
	m_zoHover->Init(MaterialHover, m_zfrRect);
	m_bHasHover = true;

	m_zoActive = new COverlay();
	m_zoActive->Init(MaterialActive, m_zfrRect);

	action = clickAction;

	m_fLayer = layer;

	m_zoNormal->SetLayer(m_fLayer);
	m_zoHover->SetLayer(m_fLayer);
	m_zoActive->SetLayer(m_fLayer);

	viewport->AddOverlay(getNormalOverlay());


	viewport->AddOverlay(getHoverOverlay());

	viewport->AddOverlay(getActiveOverlay());

	m_zoNormal->SwitchOn();
	m_zoHover->SwitchOff();
	m_zoActive->SwitchOff();
}

VButton::~VButton()
{
	delete m_zoNormal;
	delete m_zoHover;
	delete m_zoActive;
}

//Events
void VButton::onMouseOver(void)
{
	if (!isActive())
	{
		m_zoNormal->SwitchOff();
		m_zoHover->SwitchOn();
	}
}

void VButton::onMouseOut(void)
{
	if (!isActive())
	{
		m_zoHover->SwitchOff();
		m_zoNormal->SwitchOn();
	}
}

void VButton::onMouseClickLeft(void)
{
	notify(action);
}

void VButton::onMouseClickRight(void)
{
	//ToDo
}

void VButton::setLayer(const float layer)
{
	m_zoNormal->SetLayer(layer);
	m_zoHover->SetLayer(layer);
	m_zoActive->SetLayer(layer);
}

void VButton::updateRectangle(CFloatRect rect)
{
	m_zoNormal->SetRect(rect);
	m_zoHover->SetRect(rect);
	m_zoActive->SetRect(rect);
}

//Getter 
bool VButton::bGetHasHover()
{
	return this->m_bHasHover;
}

COverlay* VButton::getActiveOverlay()
{
	return m_zoActive;
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

void VButton::setActive(bool value)
{
	m_isActive = value;
	if (m_isActive)
	{
		m_zoNormal->SwitchOff();
		m_zoHover->SwitchOff();
		m_zoActive->SwitchOn();
	}
	else
	{
		m_zoNormal->SwitchOn();
		m_zoHover->SwitchOff();
		m_zoActive->SwitchOff();

	}
}

bool VButton::isActive()
{
	return m_isActive;
}

void VButton::switchOn()
{
	m_bisOn = true;
	m_zoNormal->SwitchOn();
	m_zoHover->SwitchOff();
	m_zoActive->SwitchOff();
}

void VButton::switchOff()
{
	m_bisOn = false;
	m_zoNormal->SwitchOff();
	m_zoHover->SwitchOff();
	m_zoActive->SwitchOff();
}


NAMESPACE_VIEW_E
