#include "VText.h"

NAMESPACE_VIEW_B

	VText::VText()
	{
	}

	VText::VText(CViewport* viewport, CFloatRect rect, CWritingFont* writingFont, const std::string& text)
	{
		m_zfrRect = rect;
		m_text = text;
		m_writing = new CWriting();
		m_writing->Init(m_zfrRect, m_text.length(), writingFont);

		viewport->AddWriting(m_writing);

		m_writing->PrintF("%s", const_cast<char*>(m_text.c_str()));
		
	}


	VText::~VText()
	{
		delete m_writing;
	}

	void VText::switchOn()
	{
		m_bisOn = true;
		m_writing->SwitchOn();
		m_writing->PrintF("%s", const_cast<char*>(m_text.c_str()));
	}

	void VText::switchOff()
	{
		m_bisOn = false;
		m_writing->SwitchOff();
		m_writing->PrintF("");
		
	}

	void VText::onMouseOver()
	{
	}

	void VText::onMouseOut()
	{
	}

	void VText::onMouseClickLeft()
	{
	}

	void VText::onMouseClickRight()
	{
	}

	void VText::updateText(const std::string& text)
	{
		m_writing->PrintF("%s", const_cast<char*>(text.c_str()));
	}

	void VText::setLayer(float layer)
	{
		m_writing->SetLayer(layer);
	}

	void VText::updateRectangle(CFloatRect rect)
	{
	}

	NAMESPACE_VIEW_E
