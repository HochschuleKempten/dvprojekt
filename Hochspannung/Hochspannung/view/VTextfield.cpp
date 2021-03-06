#include "VTextfield.h"
#include "VMaterialLoader.h"
#include "VUIHelper.h"

NAMESPACE_VIEW_B

VTextfield::VTextfield()
{
}

VTextfield::VTextfield(CViewport* viewport, CFloatRect& rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int MaxChars, const std::string& Placeholder, const float layer)
	:
	m_bIsActive(false),
	m_sInputtext(std::string()),
	m_sPlaceholder(Placeholder)
{
	m_ObjectType = TEXTFIELD;
	m_zfrRect = rect;

	m_fLayer = layer;

	m_iMaxChars = MaxChars;
	m_writingfont = &VMaterialLoader::standardFont;
	m_writing = new CWriting();

	
	m_writing->Init(CREATE_RELATIVE_RECT(&rect, &CFloatRect(0.02F, 0.15F, 0.98F, 0.8F)), m_iMaxChars, m_writingfont);

	m_zoNormal = new COverlay();
	m_zoNormal->Init(MaterialNormal, m_zfrRect);
	m_zoActive = new COverlay();
	m_zoActive->Init(MaterialActive, m_zfrRect);

	m_zoHover = new COverlay();
	m_zoHover->Init(MaterialHover, m_zfrRect);


	viewport->AddWriting(m_writing);
	viewport->AddOverlay(m_zoActive);
	viewport->AddOverlay(m_zoHover);
	viewport->AddOverlay(m_zoNormal);

	m_zoHover->SwitchOff();
	m_zoActive->SwitchOff();

	m_zoNormal->SetLayer(m_fLayer);
	m_zoHover->SetLayer(m_fLayer);
	m_zoActive->SetLayer(m_fLayer);

	m_writing->SetLayer(m_fLayer - 0.01f);

	m_writing->PrintF("%s", &m_sPlaceholder[0]);
}

VTextfield::~VTextfield()
{
	delete m_zoNormal;
	delete m_zoHover;
	delete m_zoActive;
	delete m_writingfont;
	delete m_writing;
}

void VTextfield::checkEvent(CDeviceCursor* cursor, CDeviceKeyboard* keyboard)
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
			m_zoNormal->SwitchOn();
			if (m_sInputtext.empty())
			{
				m_writing->PrintF("%s", &m_sPlaceholder[0]);
			}
		}
	}

	if (isActive())
	{
		if (keyboard->GetKey() == 0)
		{
			pressedBefore = false;
		}

		if (!pressedBefore && keyboard->KeyPressed(DIK_BACK))
		{
			deleteChar();
			pressedBefore = true;
		}
		if (!pressedBefore && keyboard->GetKey() != 0)
		{
			AddChar(keyboard->GetChar(keyboard->GetKey()));
			pressedBefore = true;
		}
	}
}

void VTextfield::switchOn()
{
	m_bisOn = true;
	m_zoNormal->SwitchOn();
	m_zoActive->SwitchOff();
	m_zoHover->SwitchOff();
	m_writingfont->SwitchOff();
	m_writing->SwitchOn();
	m_bIsActive = false;
}

void VTextfield::switchOff()
{
	m_bisOn = false;
	m_zoNormal->SwitchOff();
	m_zoActive->SwitchOff();
	m_zoHover->SwitchOff();
	m_writingfont->SwitchOff();
	m_writing->SwitchOff();
	m_bIsActive = false;
}

void VTextfield::AddChar(const char character)
{
	// ignore numpad input 
	if (character != 0 && m_sInputtext.length() < m_iMaxChars)
	{
		m_sInputtext += character;

		m_writing->PrintF("%s", &m_sInputtext[0]);
	}
}

void VTextfield::deleteChar()
{
	if (!m_sInputtext.empty())
	{
		/*m_sInputtext.erase(m_sInputtext.length()-2,1);*/
		m_sInputtext.resize(m_sInputtext.length() - 1);
		m_writing->PrintF("%s", &m_sInputtext[0]);
	}
}

bool VTextfield::isActive()
{
	return m_bIsActive;
}

void VTextfield::setLayer(const float layer)
{
	m_zoNormal->SetLayer(layer);
	m_zoHover->SetLayer(layer);
	m_zoActive->SetLayer(layer);
}

void VTextfield::updateRectangle(CFloatRect rect)
{
}

std::string VTextfield::getValue()
{
	return m_sInputtext;
}

void VTextfield::onMouseClickLeft()
{
	m_bIsActive = true;
	m_zoNormal->SwitchOff();
	m_zoHover->SwitchOff();
	m_zoActive->SwitchOn();
}

void VTextfield::onMouseClickRight()
{
}

void VTextfield::onMouseOver()
{
	if (!m_bIsActive)
	{
		m_zoNormal->SwitchOff();
		m_zoActive->SwitchOff();
		m_zoHover->SwitchOn();
	}
}

void VTextfield::onMouseOut()
{
	if (!m_bIsActive)
	{
		m_zoNormal->SwitchOn();
		m_zoHover->SwitchOff();
	}
}

void VTextfield::setActive(const bool wert)
{
	m_bIsActive = wert;
}

NAMESPACE_VIEW_E
