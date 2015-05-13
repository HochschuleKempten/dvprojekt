#include "VGroup.h"
#include "VButton.h"
#include "VTextfield.h"
#include "VText.h"
#include "VDialog.h"
#include "VRegister.h"
#include "VGUIArea.h"
NAMESPACE_VIEW_B

	VGroup::VGroup()
	{
	}

	VGroup::VGroup(CViewport* viewport, CFloatRect floatRect)
	{
		m_viewport = viewport;
		m_zfRect = floatRect;
	}

	VGroup::VGroup(CViewport* viewport, CFloatRect floatRect, CMaterial* materialbackground)
	{
		m_viewport = viewport;
		m_zfRect = floatRect;
		m_background = new COverlay();
		m_background->SetLayer(0.9F);
		m_background->Init(materialbackground, m_zfRect);
		m_viewport->AddOverlay(m_background);
		m_hasBackground = true;
	}

	VGroup::~VGroup()
	{
		for (m_lIterGUIObjects = m_guiObjects.begin(); m_lIterGUIObjects != m_guiObjects.end(); ++m_lIterGUIObjects)
		{
			delete m_lIterGUIObjects->second;
		}
		m_guiObjects.clear();
		if (m_hasBackground) delete m_background;
	}


	void VGroup::onNotify(Event events)
	{
		switch (events)
		{
		default:
			notify(events);
		}
	}

	void  VGroup::addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, std::string sName)
	{
		m_guiObjects[sName] = new VButton(m_viewport, rect, MaterialNormal, MaterialHover, clickAction);

		m_guiObjects[sName]->addObserver(this);
	}

	void  VGroup::addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const std::string& Placeholder, std::string sName)
	{
		m_guiObjects[sName] = new VTextfield(m_viewport, rect, MaterialNormal, MaterialHover, MaterialActive, MaxChars, Placeholder);

		m_guiObjects[sName]->addObserver(this);
	}

	void  VGroup::addText(CFloatRect rect, CWritingFont* writingFont, std::string text, std::string sName)
	{
		m_guiObjects[sName] = new VText(m_viewport, rect, writingFont, text);

		m_guiObjects[sName]->addObserver(this);
	}

	void  VGroup::addOverlay(CFloatRect rect, CMaterial* MaterialNormal, bool bChromaKeying, std::string sName)
	{
		m_Overlays[sName] = new COverlay();
		m_Overlays[sName]->Init(MaterialNormal, rect);
		m_viewport->AddOverlay(m_Overlays[sName]);
	}

	void VGroup::addContainer(const IViewGUIContainer::ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::string& sName)
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
		default: break;
		}
	}

	void VGroup::addContainer(const IViewGUIContainer::ContainerType& containerType, CFloatRect& floatRect, const std::string& sName)
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
		default: break;
		}
	}


	NAMESPACE_VIEW_E
