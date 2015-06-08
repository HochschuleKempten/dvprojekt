#include "VListEntry.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


VListEntry::VListEntry()
{
}

VListEntry::VListEntry(CViewport* viewport, CMaterial* MaterialNormal, CMaterial* MaterialHover, const std::string& sName, const float layer) :
	m_bHasHover(false)
{
	m_ObjectType = LIST_ENTRY;

	m_viewport = viewport;
	//m_zfrRect = rect;
	m_zoNormal = new COverlay();
	m_zoNormal->Init(MaterialNormal, m_zfrRect);

	m_zoActive = new COverlay();
	m_zoActive->Init(MaterialHover, m_zfrRect);

	m_zoHover = new COverlay();
	m_zoHover->Init(MaterialHover, m_zfrRect);
	m_bHasHover = true;

	m_sName = sName;

	m_fLayer = layer;


	iwas = new CWriting();


	viewport->AddWriting(iwas);
	viewport->AddOverlay(m_zoActive);
	viewport->AddOverlay(getNormalOverlay());
	viewport->AddOverlay(getHoverOverlay());

	m_zoHover->SwitchOff();
	m_zoActive->SwitchOff();


	m_zoHover->SetLayer(m_fLayer);
	m_zoNormal->SetLayer(m_fLayer);
	m_zoActive->SetLayer(m_fLayer);
	iwas->SetLayer(m_fLayer - 0.01F);
}

VListEntry::~VListEntry()
{
	m_viewport->SubOverlay(m_zoNormal);
	m_viewport->SubOverlay(m_zoHover);
	m_viewport->SubOverlay(m_zoActive);
	m_viewport->SubWriting(iwas);

	delete m_zoNormal;
	delete m_zoHover;
	delete m_zoActive;
	delete iwas;
}


void VListEntry::switchOn()
{
	m_bisOn = true;
	m_zoNormal->SwitchOn();
	m_zoActive->SwitchOff();
	m_zoHover->SwitchOff();
	m_bIsActive = false;
}

void VListEntry::switchOff()
{
	m_bisOn = false;
	m_zoNormal->SwitchOff();
	m_zoActive->SwitchOff();
	m_zoHover->SwitchOff();
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
	iwas->SetLayer(layer - 0.01F);
}

bool VListEntry::isActive()
{
	return m_bIsActive;
}

void VListEntry::setActive(bool wert)
{
	m_bIsActive = wert;
	if (m_bIsActive)
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

	m_viewport->SubWriting(iwas);
	delete iwas;
	iwas = new CWriting();
	iwas->SetRect(rect);
	iwas->Init(createRelativeRectangle(&rect, &CFloatRect(0.1F, 0.1F, 0.8F, 0.8F)), m_sName.length(), &VMaterialLoader::standardFont);

	iwas->PrintF(&m_sName[0]);
	iwas->SetLayer(getLayer() - 0.01F);

	m_viewport->AddWriting(iwas);

	m_zfrRect = rect;
}

void VListEntry::checkEvent(CDeviceCursor* cursor, CDeviceKeyboard* keyboard)
{
	//Mouse
	float fPosX;
	float fPosY;
	cursor->GetFractional(fPosX, fPosY);
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
