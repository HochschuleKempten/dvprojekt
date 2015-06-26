#include "VStatistics.h"
#include "VMaterialLoader.h"
#include <vector>
#include <string>
#include <sstream>

NAMESPACE_VIEW_B

VStatistics::VStatistics(CViewport* viewport, CFloatRect& rect, CMaterial* materialBackground, const float layer)
{
	m_viewport = viewport;
	m_zfrRect  = rect;
	m_fLayer   = layer;

	m_background = new COverlay();
	m_background->SetLayer(m_fLayer);
	m_background->Init(materialBackground, m_zfrRect);
	m_background->SetTransparency(0.1F);
	m_viewport->AddOverlay(m_background);
	m_hasBackground = true;
}

VStatistics::~VStatistics()
{
	for each (VText* text in m_texts)
	{
		delete text;
	}

	m_texts.clear();
}

void VStatistics::updateRectangle(CFloatRect rect)
{

}

void VStatistics::slideToggle()
{
	
}

void VStatistics::slideIn()
{

}

void VStatistics::slideOut()
{

}

void HighVoltage::VStatistics::addText(const std::string& text)
{
	float fTextHeight = m_zfrRect.GetYSize() * 0.05F;
	float fXPos = m_zfrRect.GetXPos() + m_zfrRect.GetXSize () * 0.05F;

	std::stringstream data(text);
	std::string line;

	while (std::getline(data, line, '\n')) {
		float fYPos = m_zfrRect.GetYPos() + fTextHeight * m_texts.size() + fTextHeight;

		VText * vtext = new VText(m_viewport, CFloatRect(fXPos, fYPos, m_zfrRect.GetXSize() * 0.9F, m_zfrRect.GetYSize() * 0.05F), &VMaterialLoader::standardFont, line, m_fLayer - 0.01F);
		m_texts.push_back(vtext);
	}
	
	m_hasText = true;
}

void VStatistics::setLayer(const float layer)
{
	if (m_hasBackground)
		m_background->SetLayer(layer);
	
	// set layer of everything inside the statistics container
}

void VStatistics::onMouseClickRight()
{

}

void VStatistics::onMouseClickLeft()
{

}

void VStatistics::onMouseOut()
{

}

void VStatistics::onMouseOver()
{

}

void VStatistics::switchOff()
{
	if (m_hasBackground) m_background->SwitchOff();
	for each (VText * text in m_texts)
	{
		text->switchOff();
	}

	slideOut();
}

void VStatistics::switchOn()
{
	if (m_hasBackground) m_background->SwitchOn();
	for each (VText * text in m_texts)
	{
		text->switchOn();
	}

	slideIn();
}

void VStatistics::checkEvent(CDeviceCursor* cursor, CDeviceKeyboard* keyboard)
{
	if (cursor->ButtonPressedRight() || cursor->ButtonPressedLeft () || keyboard->KeyPressed (DIK_ESCAPE)) {
		switchOff();
	}
}

NAMESPACE_VIEW_E