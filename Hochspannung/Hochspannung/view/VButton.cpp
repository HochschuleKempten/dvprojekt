#include "VButton.h"
NAMESPACE_VIEW_B

	VButton::VButton() :
		m_bHasHover(false)
	{
	}

	VButton::VButton(CViewport* viewport, CFloatRect& rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewUIObserver::Event clickAction) :
		m_bHasHover(false),
		action(IViewUIObserver::NOTHING)
	{
		m_zfrRect = rect;
		m_zoNormal = new COverlay();
		m_zoNormal->Init(MaterialNormal, m_zfrRect);

		m_zoHover = new COverlay();
		m_zoHover->Init(MaterialHover, m_zfrRect);
		m_bHasHover = true;

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
	}

	void VButton::updateRectangle(CFloatRect rect)
	{
		m_zoNormal->SetRect(rect);
		m_zoHover->SetRect(rect);
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

	void VButton::setActive(bool value)
	{
		m_isActive = value;
		if (m_isActive)
		{
			m_zoNormal->SwitchOff();
			m_zoHover->SwitchOn();
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
	}

	void VButton::switchOff()
	{
		m_bisOn = false;
		m_zoNormal->SwitchOff();
		m_zoHover->SwitchOff();
	}


	NAMESPACE_VIEW_E
