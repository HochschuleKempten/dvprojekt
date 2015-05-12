#include "VGUIArea.h"
#include "VGroup.h"
#include "VMaterialLoader.h"
#include "VRegister.h"
#include "VDialog.h"
#include "VListView.h"

NAMESPACE_VIEW_B

	VGUIArea::VGUIArea()
	{
	}


	VGUIArea::VGUIArea(CViewport* viewport, CFloatRect floatRect)
	{
		m_viewport = viewport;
		m_zfRect = floatRect;
	}

	VGUIArea::VGUIArea(CViewport* viewport, CFloatRect floatRect, CMaterial* materialbackground)
	{
		m_viewport = viewport;
		m_zfRect = floatRect;
		m_background = new COverlay();
		m_background->SetLayer(0.9F);
		m_background->Init(materialbackground, m_zfRect);
		m_viewport->AddOverlay(m_background);
		m_hasBackground = true;
	}

	VGUIArea::~VGUIArea()
	{
		for (m_lIterGUIObjects = m_guiObjects.begin(); m_lIterGUIObjects != m_guiObjects.end(); ++m_lIterGUIObjects)
		{
			delete m_lIterGUIObjects->second;
		}
		m_guiObjects.clear();
		if (m_hasBackground) delete m_background;
	}

	

	void VGUIArea::onNotify(Event events)
	{
		switch (events)
		{
		default:
			notify(events);
		}
	}


	void VGUIArea::addContainer(const IViewGUIContainer::ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const string& sName)
	{
		switch (containerType)
		{
		case Group:
			m_Guicontainer[sName] = new VGroup(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case Dialog:
			m_Guicontainer[sName] = new VDialog(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case Register:
			m_Guicontainer[sName] = new VRegister(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport, MaterialNormal);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case GUIArea:
			m_Guicontainer[sName] = new VGUIArea(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case ListView:
			m_Guicontainer[sName] = new VListView(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport, MaterialNormal);
			m_Guicontainer[sName]->addObserver(this);
			break;
		default: break;
		}
	}

	void VGUIArea::addContainer(const IViewGUIContainer::ContainerType& containerType, CFloatRect& floatRect, const string& sName)
	{
		switch (containerType)
		{
		case Group:
			m_Guicontainer[sName] = new VGroup(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect));
			m_Guicontainer[sName]->addObserver(this);
			break;
		case Dialog:
			m_Guicontainer[sName] = new VDialog(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect));
			m_Guicontainer[sName]->addObserver(this);
			break;
		case Register:
			m_Guicontainer[sName] = new VRegister(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case GUIArea:
			m_Guicontainer[sName] = new VGUIArea(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect));
			m_Guicontainer[sName]->addObserver(this);
			break;
		case ListView:
			m_Guicontainer[sName] = new VListView(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport);
			m_Guicontainer[sName]->addObserver(this);
			break;
		default: break;
		}
	}


	NAMESPACE_VIEW_E
