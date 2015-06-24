#include "VGraph.h"

NAMESPACE_VIEW_B


VGraph::VGraph(CViewport* viewport, CFloatRect& rect)
{
	m_viewport = viewport;
	m_zfrRect = rect;
}

VGraph::~VGraph()
{
}

void VGraph::checkEvent(CDeviceCursor* /*cursor*/, CDeviceKeyboard* keyboard)
{
}

void VGraph::switchOn()
{
}

void VGraph::switchOff()
{
}

void VGraph::onMouseOver()
{
}

void VGraph::onMouseOut()
{
}

void VGraph::onMouseClickLeft()
{
}

void VGraph::onMouseClickRight()
{
}

void VGraph::setLayer(const float /*layer*/)
{
}

void VGraph::updateRectangle(CFloatRect rect)
{
}

void VGraph::addBar(std::string sName, CMaterial* normalMaterial)
{
	m_bars[sName] = new Bar(m_viewport, normalMaterial, createRelativeRectangle(&m_zfrRect, &CFloatRect(0, 0, 1, 1)), 10);
	//calcHeight();
	//calcWidth();

	recalcRectangles();

	//		m_bars[sName]->Init(normalMaterial, createRelativeRectangle(&m_zfrRect, &CFloatRect(0, 0, 0,0)));
}

void VGraph::updateBar(std::string sName, float wert)
{
	m_bars[sName]->set_m_f_value(wert);
	calcHeight();
}

void VGraph::updateBar2(std::string sName, float wert)
{
	m_bars[sName]->set_m_f_value(wert);
	recalcRectangles();
}

void VGraph::calcHeight()
{
	float fMaxSize = 0;
	Bar* tempMax = nullptr;
	CFloatRect tempRect;
	for (m_IterBars = m_bars.begin(); m_IterBars != m_bars.end(); ++m_IterBars)
	{
		if (m_IterBars->second->get_m_f_value() > fMaxSize)
		{
			fMaxSize = m_IterBars->second->get_m_f_value();
			tempMax = m_IterBars->second;
		}
	}
	for (m_IterBars = m_bars.begin(); m_IterBars != m_bars.end(); ++m_IterBars)
	{
		float part = 0;

		tempRect = m_IterBars->second->getRectangle();
		ASSERT(fMaxSize != 0, "Devision by zero.MaxSize is zero!");
		part = m_IterBars->second->get_m_f_value() / fMaxSize;

		tempRect.SetYSize(part);
		m_IterBars->second->setRectangle(createRelativeRectangle(&m_zfrRect, &tempRect));
		m_IterBars->second->updateRectangle(createRelativeRectangle(&m_zfrRect, &tempRect));
	}
	tempRect.SetYSize(1.0F);
	tempMax->setRectangle(createRelativeRectangle(&m_zfrRect, &tempRect));
	tempMax->updateRectangle(createRelativeRectangle(&m_zfrRect, &tempRect));
}

void VGraph::recalcRectangles()
{
	float fMaxValue = 0;
	float fNewWidthPart = (!m_bars.empty()) ? m_zfrRect.GetXSize() / m_bars.size() : 0;
	float part = 0;
	int i = 0;
	CFloatRect tempRect;

	// get maximum value among all bars
	for each (std::pair<std::string, Bar*> bar in m_bars)
	{
		if (bar.second->get_m_f_value() > fMaxValue)
		{
			fMaxValue = bar.second->get_m_f_value();
		}
	}

	// recalculate rectangles for every bar
	for each (std::pair<std::string, Bar*> bar in m_bars)
	{
		//ASSERT(fMaxValue != 0, "Division by zero. MaxSize is zero!");

		tempRect = bar.second->getRectangle();
		part = (fMaxValue > 0) ? bar.second->get_m_f_value() / fMaxValue : 0;
		tempRect.SetXPos(m_zfrRect.GetXPos() + i * fNewWidthPart);
		tempRect.SetYPos(m_zfrRect.GetYPos() + (m_zfrRect.GetYSize() - part * m_zfrRect.GetYSize()));
		tempRect.SetXSize(fNewWidthPart);
		tempRect.SetYSize(m_zfrRect.GetYSize() * part);
		bar.second->setRectangle(tempRect);
		bar.second->updateRectangle(tempRect);
		i++;
	}
}

float VGraph::getMaxHeight()
{
	return 0.0F;
}

void VGraph::calcWidth()
{
	int i = 0;
	for (m_IterBars = m_bars.begin(); m_IterBars != m_bars.end(); ++m_IterBars)
	{
		//GUI Object Size Mehode hinzufügen
		CFloatRect tempRect = m_IterBars->second->getRectangle();
		m_IterBars->second->setRectangle(createRelativeRectangle(&m_zfrRect, &CFloatRect(1.0F / static_cast<float>(m_bars.size()) * static_cast<float>(i), 0.0F, 1.0F / static_cast<float>(m_bars.size()), m_IterBars->second->getRectangle().GetYSize())));
		m_IterBars->second->updateRectangle(createRelativeRectangle(&m_zfrRect, &CFloatRect(1.0F / static_cast<float>(m_bars.size()) * static_cast<float>(i), 0.0F, 1.0F / static_cast<float>(m_bars.size()), m_IterBars->second->getRectangle().GetYSize())));
		i++;
	}
}


CFloatRect VGraph::createRelativeRectangle(CFloatRect* RelativeToRect, CFloatRect* RelativeRect)
{
	return CFloatRect(RelativeToRect->GetXPos() + (RelativeToRect->GetXSize() * RelativeRect->GetXPos()), RelativeToRect->GetYPos() + (RelativeToRect->GetYSize() * RelativeRect->GetYPos()),
	                  RelativeToRect->GetXSize() * RelativeRect->GetXSize(), RelativeToRect->GetYSize() * RelativeRect->GetYSize());
}


NAMESPACE_VIEW_E
