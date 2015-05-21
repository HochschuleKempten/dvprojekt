
#include "VTextfield.h"
#include "VMaterialLoader.h"


NAMESPACE_VIEW_B

	VTextfield::VTextfield()
	{
	}

	VTextfield::VTextfield(CViewport* viewport, CFloatRect& rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int MaxChars, const std::string& Placeholder)
		:
		m_bIsActive(false),
		m_sInputtext(std::string())
	{
		m_ObjectType = TEXTFIELD;
		m_zfrRect = rect;
		m_sPlaceholder = Placeholder;

		m_iMaxChars = MaxChars;
		m_writingfont = &VMaterialLoader::standardFont;
		m_writing = new CWriting();

		//Initialize Writing
		m_writing->Init(CFloatRect(m_zfrRect.GetXPos() + (m_zfrRect.GetXPos() / 100), m_zfrRect.GetYPos() - 0.01, m_zfrRect.GetXSize() - (m_zfrRect.GetXPos() / 100), m_zfrRect.GetYSize() + 0.06), m_iMaxChars,
		                m_writingfont);

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

		m_zoNormal->SetLayer(0.7F);
		m_zoHover->SetLayer(0.7F);
		m_zoActive->SetLayer(0.7F);

		m_writing->PrintF("%s", const_cast<char*>(m_sPlaceholder.c_str()));
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
				if (m_sInputtext.empty())
				{
					m_writing->PrintF("%s", const_cast<char*>(m_sPlaceholder.c_str()));
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
		if (m_sInputtext.length() < m_iMaxChars)
		{
			m_sInputtext += character;

			m_writing->PrintF("%s", const_cast<char*>(m_sInputtext.c_str()));
		}
	
	}

	void VTextfield::deleteChar()
	{
		if (!m_sInputtext.empty())
		{
			/*m_sInputtext.erase(m_sInputtext.length()-2,1);*/
			m_sInputtext.resize(m_sInputtext.length() - 1);
			m_writing->PrintF("%s", const_cast<char*>(m_sInputtext.c_str()));
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
