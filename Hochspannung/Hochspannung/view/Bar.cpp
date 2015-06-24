#include "Bar.h"
NAMESPACE_VIEW_B


Bar::Bar(CViewport* viewport, CMaterial* material, CFloatRect rect, float value) :mp_zoSurface(nullptr), m_fValue(0.0F)
{
	mp_zoSurface = new COverlay();
	mp_zoSurface->Init(material, rect);
	viewport->AddOverlay(mp_zoSurface);
	m_fValue = value;
}


Bar::~Bar()
{
	delete mp_zoSurface;
}


void Bar::switchOff()
{
	mp_zoSurface->SwitchOff();
}

void Bar::onMouseOver()
{
}

void Bar::onMouseOut()
{
}

void Bar::onMouseClickLeft()
{
}

void Bar::onMouseClickRight()
{
}

void Bar::setLayer(const float /*layer*/)
{
}

void Bar::updateRectangle(CFloatRect rect)
{
	mp_zoSurface->SetRect(rect);
}

void Bar::switchOn()
{
	mp_zoSurface->SwitchOn();
}

NAMESPACE_VIEW_E
