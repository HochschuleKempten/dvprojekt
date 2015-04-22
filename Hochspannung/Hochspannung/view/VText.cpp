#include "VText.h"

NAMESPACE_VIEW_B
VText::VText()
{
}

VText::VText(CViewport* viewport, CFloatRect rect, CWritingFont* writingFont, string text)
	{
		m_zfrRect = rect;
		m_text = text;
		m_writing = new CWriting();
		m_writing->Init(m_zfrRect, m_text.length(),writingFont);
		
		viewport->AddWriting(m_writing);

		m_writing->PrintF("%s", const_cast<char*>(m_text.c_str()));
		
	}


	VText::~VText()
{
}

	void VText::switchOn()
	{
		m_writing->SwitchOn();
	}

	void VText::switchOff()
	{
		m_writing->SwitchOff();
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

	void VText::updateText(string text)
	{
		m_writing->PrintF("%s", const_cast<char*>(text.c_str()));
	}

	NAMESPACE_VIEW_E