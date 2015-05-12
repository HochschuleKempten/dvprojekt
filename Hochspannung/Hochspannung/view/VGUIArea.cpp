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

	void VGUIArea::addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, string sName)
	{
		m_guiObjects[sName] = new VButton(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, clickAction);

		m_guiObjects[sName]->addObserver(this);
	}

	void VGUIArea::addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder, string sName)
	{
		m_guiObjects[sName] = new VTextfield(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, MaterialActive, MaxChars, Placeholder);

		m_guiObjects[sName]->addObserver(this);
	}

	void VGUIArea::addText(CFloatRect rect, CWritingFont* writingFont, string text, string sName)
	{
		m_guiObjects[sName] = new VText(m_viewport, createRelativeRectangle(&m_zfRect, &rect), writingFont, text);

		m_guiObjects[sName]->addObserver(this);
	}

	void VGUIArea::addOverlay(CFloatRect rect, CMaterial* MaterialNormal, bool bChromaKeying, string sName)
	{
		m_Overlays[sName] = new COverlay();
		m_Overlays[sName]->Init(MaterialNormal, createRelativeRectangle(&m_zfRect, &rect));
		m_viewport->AddOverlay(m_Overlays[sName]);
		m_Overlays[sName]->SetLayer(0.1F);
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
