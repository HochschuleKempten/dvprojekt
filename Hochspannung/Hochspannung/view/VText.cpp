#include "VText.h"

NAMESPACE_VIEW_B

VText::VText()
{
}

VText::VText(CViewport* viewport, CFloatRect rect, CWritingFont* writingFont, const std::string& text, const float layer, const TextMode& textmode)
	: m_text(text), m_textmode(textmode)
{
	m_ObjectType = TEXT;
	m_zfrRect = rect;
	m_writing = new CWriting();
	m_writing->Init(m_zfrRect, m_text.length(), writingFont);

	m_maxLength = m_text.length();

	m_writingFont = writingFont;

	m_fLayer = layer;

	m_writing->SetLayer(m_fLayer);

	viewport->AddWriting(m_writing);

	if (m_textmode == CENTERED)
	centerText();
		
	
	
	m_writing->PrintF("%s", &m_text[0]);
}


VText::~VText()
{
	delete m_writing;
}

void VText::switchOn()
{
	m_bisOn = true;
	m_writing->SwitchOn();
	
}

void VText::switchOff()
{
	m_bisOn = false;
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

void VText::updateText(const std::string& text)
{
	m_text = text;
	if (m_textmode == CENTERED)
		centerText();
	m_writing->PrintF("%s", &m_text[0]);
}

void VText::setLayer(float layer)
{
	m_writing->SetLayer(layer);
}

void VText::updateRectangle(CFloatRect rect)
{
	m_writing->SetRect(rect);
	m_zfrRect = rect;
}

void VText::centerText()
{
	if (m_maxLength > m_text.length())
	{
		int numCharToFill = (m_maxLength - m_text.length()) / 2;
		for (int i = 0; i < numCharToFill; i++)
		{
			m_text = " " + m_text;
		}
	}
}

CWritingFont* VText::getWritingfont()
{
	return m_writingFont;
}

std::string VText::getText()
{
	return m_text;
}

NAMESPACE_VIEW_E
