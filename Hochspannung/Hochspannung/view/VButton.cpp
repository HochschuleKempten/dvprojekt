#include "VButton.h"
NAMESPACE_VIEW_B

VButton::VButton():
m_zfrRect(CFloatRect(0,0,0,0)),
m_bHasHover(false)
{

}
VButton::VButton(CViewport* viewport,CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewObserver::Event clickAction) :
m_zfrRect(CFloatRect(0, 0, 0, 0)),
m_bHasHover(false),
action(IViewObserver::NOTHING)
{
	m_zoNormal = new COverlay();
	m_zoNormal->Init(MaterialNormal,rect);

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
	notify(IViewObserver::START_GAME);
	//ToDo
}
void VButton::onMouseClickRight(void)
{
	//ToDo
}


void VButton::checkHover(float fPosX, float fPosY)
{

	//Prüfe ob X-Koordinate innerhalb des Buttons
	if ((fPosX > m_zfrRect.GetXPos()) && (fPosX < (m_zfrRect.GetXPos() + m_zfrRect.GetXSize())))
	{
		//Prüfe ob Y-Koordinate innerhalb des Buttons
		if ((fPosY >  m_zfrRect.GetYPos()) && (fPosY < (m_zfrRect.GetYPos() + m_zfrRect.GetYSize())))
		{
			//Koordinaten sind auf Button
			m_zoNormal->SwitchOff();
			m_zoHover->SwitchOn();
		}
		else
		{
			//X-Koordinate passt aber Y-Koordinate nicht
			//Koordinaten sind auf Button
			m_zoHover->SwitchOff();
			m_zoNormal->SwitchOn();
			
		}
	}
	else
	{
		//X-Koordinate passt nicht
		m_zoHover->SwitchOff();
		m_zoNormal->SwitchOn();
	}

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


void VButton::checkPressed(float fPosX, float fPosY, bool bLeftpressed)
{
	if (bLeftpressed)
	{
		if ((fPosX > m_zfrRect.GetXPos()) && (fPosX < (m_zfrRect.GetXPos() + m_zfrRect.GetXSize())))
		{
			//Prüfe ob Y-Koordinate innerhalb des Buttons
			if ((fPosY >  m_zfrRect.GetYPos()) && (fPosY < (m_zfrRect.GetYPos() + m_zfrRect.GetYSize())))
			{
				OutputDebugString("Button Clickevent ausgelöst\n ");
				OutputDebugString("button->Benachrichtige alle Beobachter\n");
				notify(action);
				
			}
			
	}
	else
	{
		return;
	}
}
}

NAMESPACE_VIEW_E