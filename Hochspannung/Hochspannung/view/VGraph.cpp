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

	void VGraph::checkEvent(CDeviceCursor* cursor, CDeviceKeyboard* keyboard)
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

	void VGraph::setLayer(float layer)
	{
	}

	void VGraph::updateRectangle(CFloatRect rect)
	{
	}

	void VGraph::addBar(std::string sName, CMaterial* normalMaterial)
	{
		m_bars[sName] = new Bar(m_viewport, normalMaterial, createRelativeRectangle(&m_zfrRect, &CFloatRect(0, 0, 1, 1)), 10);
		float layer = getLayer() - 0.01F * (m_bars.size() + 1);
		m_bars[sName]->setLayer(layer);
		calcHeight();
		//calcWidth();

		//		m_bars[sName]->Init(normalMaterial, createRelativeRectangle(&m_zfrRect, &CFloatRect(0, 0, 0,0)));
	}

	void VGraph::updateBar(std::string sName, float wert)
	{
		m_bars[sName]->set_m_f_value(wert);
		calcHeight();
	}

	void VGraph::calcHeight()
	{
		float fMaxSize = 0;
		Bar* tempMax = nullptr;
		CFloatRect tempRect;
		//for (m_IterBars = m_bars.begin(); m_IterBars != m_bars.end(); ++m_IterBars)
		//{
		//	if (m_IterBars->second->get_m_f_value() > fMaxSize)
		//	{
		//		fMaxSize = m_IterBars->second->get_m_f_value();
		//		tempMax = m_IterBars->second;
		//	}
		//}
		//for (m_IterBars = m_bars.begin(); m_IterBars != m_bars.end(); ++m_IterBars)
		//{
		//	float part = 0;

		//	tempRect = m_IterBars->second->getRectangle();
		//	ASSERT(fMaxSize != 0, "Devision by zero.MaxSize is zero!");
		//	part = m_IterBars->second->get_m_f_value() / fMaxSize;

		//	tempRect.SetYSize(part);
		//	m_IterBars->second->setRectangle(createRelativeRectangle(&m_zfrRect, &tempRect));
		//	m_IterBars->second->updateRectangle(createRelativeRectangle(&m_zfrRect, &tempRect));
		//}
		//tempRect.SetYSize(1.0F);
		//tempMax->setRectangle(createRelativeRectangle(&m_zfrRect, &tempRect));
		//tempMax->updateRectangle(createRelativeRectangle(&m_zfrRect, &tempRect));
		
		// sorting height according to value
		struct bar {
			bool operator() (Bar* barI, Bar* barJ) {
				return barI->get_m_f_value() > barJ->get_m_f_value();
			}
		} compareBar;

		std::vector<Bar*> sortedBars;
		for each (std::pair<std::string, Bar*> bar in m_bars) {
			sortedBars.push_back(bar.second);
			std::sort(sortedBars.begin(), sortedBars.end(), compareBar);
		}

		for (int i = 0; i < sortedBars.size(); i++) {
			sortedBars[i]->setLayer(getLayer () - 0.01F * (i+1));
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
