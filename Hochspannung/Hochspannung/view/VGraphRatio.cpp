#include "VGraphRatio.h"

NAMESPACE_VIEW_B


VGraphRatio::VGraphRatio(CViewport* viewport, CFloatRect& rect, CMaterial* normalMaterial, bool bVertical)
{
	m_viewport = viewport;
	m_zfrRect = rect;
	m_bVertical = bVertical;

	m_bar = new Bar(viewport, normalMaterial, CFloatRect(0, 0, 1, 1), 0.3F);
	updateValue(0.3f);
}

VGraphRatio::~VGraphRatio()
{
}

void VGraphRatio::checkEvent(CDeviceCursor* cursor, CDeviceKeyboard* keyboard)
{
}

void VGraphRatio::switchOn()
{
	m_bar->switchOn();
}

void VGraphRatio::switchOff()
{
	m_bar->switchOff();
}

void VGraphRatio::onMouseOver()
{
}

void VGraphRatio::onMouseOut()
{
}

void VGraphRatio::onMouseClickLeft()
{
}

void VGraphRatio::onMouseClickRight()
{
}

void VGraphRatio::setLayer(float layer)
{
}

void VGraphRatio::updateRectangle(CFloatRect rect)
{
}

void VGraphRatio::updateValue(float fRatio)
{
	m_bar->set_m_f_value(fRatio);
	recalcRectangles();
}

void VGraphRatio::recalcRectangles()
{
	CFloatRect tempRect;

	tempRect = m_bar->getRectangle();
	tempRect.SetXPos(m_zfrRect.GetXPos());
	tempRect.SetYPos(m_zfrRect.GetYPos());
	tempRect.SetXSize(m_bVertical ? m_zfrRect.GetXSize() : m_bar->get_m_f_value() * m_zfrRect.GetXSize());
	tempRect.SetYSize(!m_bVertical ? m_zfrRect.GetYSize() : m_bar->get_m_f_value() * m_zfrRect.GetYSize());

	m_bar->setRectangle(tempRect);
	m_bar->updateRectangle(tempRect);
}

void VGraphRatio::toggleType()
{
	m_bVertical = !m_bVertical;
	recalcRectangles();
}

void VGraphRatio::switchVertical()
{
	m_bVertical = true;
	recalcRectangles();
}

void VGraphRatio::switchHorizontal()
{
	m_bVertical = false;
	recalcRectangles();
}

NAMESPACE_VIEW_E
