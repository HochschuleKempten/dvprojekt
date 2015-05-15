#include "VListEntry.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


VListEntry::VListEntry()
{
}

VListEntry::VListEntry(CViewport* viewport,CMaterial* MaterialNormal, CMaterial* MaterialHover, const std::string& sName):
m_bHasHover(false)
{
	//m_zfrRect = rect;
	m_zoNormal = new COverlay();
	m_zoNormal->Init(MaterialNormal, m_zfrRect);

	m_zoActive = new COverlay();
	m_zoActive->Init(MaterialHover, m_zfrRect);

	m_zoHover = new COverlay();
	m_zoHover->Init(MaterialHover, m_zfrRect);
	m_bHasHover = true;

	m_sName = sName;

	m_writingfont = &VMaterialLoader::standardFont;

	m_writing = new CWriting();

	//Initialize Writing
	m_writing->Init(createRelativeRectangle(&m_zfrRect,&CFloatRect(0.1F,0.05F,0.8F,0.9F)), 15,
		m_writingfont);


	viewport->AddWriting(m_writing);
	viewport->AddOverlay(m_zoActive);
	viewport->AddOverlay(getNormalOverlay());
	viewport->AddOverlay(getHoverOverlay());

	m_zoHover->SwitchOff();
	m_zoActive->SwitchOff();

	m_writing->SetLayer(0.1);
	m_zoHover->SetLayer(0.19);
	m_zoNormal->SetLayer(0.19);

	m_writing->PrintF("%s", const_cast<char*>(sName.c_str()));
}

VListEntry::~VListEntry()
{
	delete m_zoNormal;
	delete m_zoHover;
	delete m_zoActive;
	delete m_writing;
}


	void VListEntry::switchOn()
	{
		m_bisOn = true;
		m_zoNormal->SwitchOn();
		m_zoActive->SwitchOff();
		m_zoHover->SwitchOff();
		m_writingfont->SwitchOff();
		m_writing->SwitchOn();
		m_bIsActive = false;
	}

	void VListEntry::switchOff()
	{
		m_bisOn = false;
		m_zoNormal->SwitchOff();
		m_zoActive->SwitchOff();
		m_zoHover->SwitchOff();
		m_writingfont->SwitchOff();
		m_writing->SwitchOff();
		m_bIsActive = false;
	}

	void VListEntry::onMouseOver()
	{
		if (!m_bIsActive)
		{
			m_zoNormal->SwitchOff();
			m_zoActive->SwitchOff();
			m_zoHover->SwitchOn();
		}
	}

	void VListEntry::onMouseOut()
	{
		if (!m_bIsActive)
		{
			m_zoNormal->SwitchOn();
			m_zoHover->SwitchOff();
		}
	}

	void VListEntry::onMouseClickLeft()
	{
		m_bIsActive = true;
		m_zoNormal->SwitchOff();
		m_zoHover->SwitchOff();
		m_zoActive->SwitchOn();
		notifyExt(IViewUIObserver::LIST_ITEM_SELECTED, m_sName);
		
	}

	void VListEntry::onMouseClickRight()
	{
	}

	void VListEntry::setLayer(float layer)
	{
		m_zoNormal->SetLayer(layer);
		m_zoHover->SetLayer(layer);
		m_writing->SetLayer(layer);
	}

	bool VListEntry::isActive()
	{
		return m_bIsActive;
	}

	void VListEntry::setActive(bool wert)
	{
		m_bIsActive = wert;
	}

	CFloatRect VListEntry::createRelativeRectangle(CFloatRect* RelativeToRect, CFloatRect* RelativeRect)
	{
		return CFloatRect(RelativeToRect->GetXPos() + (RelativeToRect->GetXSize() * RelativeRect->GetXPos()), RelativeToRect->GetYPos() + (RelativeToRect->GetYSize() * RelativeRect->GetYPos()),
			RelativeToRect->GetXSize() * RelativeRect->GetXSize(), RelativeToRect->GetYSize() * RelativeRect->GetYSize());

	}

	bool VListEntry::bGetHasHover()
	{
		return this->m_bHasHover;
	}

	COverlay* VListEntry::getHoverOverlay()
	{
		return m_zoHover;
	}

	COverlay* VListEntry::getNormalOverlay()
	{
		return m_zoNormal;
	}

	CFloatRect VListEntry::getRectangle()
	{
		return m_zfrRect;
	}

	void VListEntry::updateRectangle(CFloatRect rect)
	{
		m_zoNormal->SetRect(rect);
		m_zoHover->SetRect(rect);
		m_zoActive->SetRect(rect);
	}

	void VListEntry::checkEvent(CDeviceCursor* cursor, CDeviceKeyboard* keyboard)
	{
		//Mouse
		float fPosX;
		float fPosY;
		cursor->GetFractional(fPosX, fPosY, true);
		if (checkHover(fPosX, fPosY))
		{
			if (cursor->ButtonPressedLeft())
			{
				onMouseClickLeft();
			}
		}
		else
		{
			if (cursor->ButtonPressedLeft())
			{
				setActive(false);
				m_zoActive->SwitchOff();
				
			}
		}

		if (isActive())
		{
			
		}
	}

	NAMESPACE_VIEW_E