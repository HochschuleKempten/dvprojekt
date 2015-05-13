#include "VListView.h"
#include "VGroup.h"
#include "VDialog.h"
#include "VRegister.h"
#include "VGUIArea.h"

NAMESPACE_VIEW_B

VListView::VListView()
{
}

	VListView::VListView(CFloatRect floatRect, CViewport* viewport)
	{
		m_viewport = viewport;
		m_zfRect = floatRect;
	}

	VListView::VListView(CFloatRect floatRect, CViewport* viewport, CMaterial* materialBackground)
	{
		m_viewport = viewport;
		m_zfRect = floatRect;
		m_background = new COverlay();
		m_background->SetLayer(0.2F);
		m_background->Init(materialBackground, m_zfRect);
		m_viewport->AddOverlay(m_background);
		m_hasBackground = true;
	}

	void VListView::onNotify(Event evente)
	{
		switch (evente)
		{
		default:
			notify(evente);
			break;
		}
	}

	void VListView::addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::string& sName)
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

	void VListView::addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::string& sName)
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


	void VListView::addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, std::string sName)
	{
		m_guiObjects[sName] = new VButton(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, clickAction);

		m_guiObjects[sName]->addObserver(this);

	}

	void VListView::addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const std::string& Placeholder, std::string sName)
	{
		m_guiObjects[sName] = new VTextfield(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, MaterialActive, MaxChars, Placeholder);

		m_guiObjects[sName]->addObserver(this);

	}

	void VListView::addText(CFloatRect rect, CWritingFont* writingFont, std::string text, std::string sName)
	{
		m_guiObjects[sName] = new VText(m_viewport, createRelativeRectangle(&m_zfRect, &rect), writingFont, text);

		m_guiObjects[sName]->addObserver(this);

	}

	void VListView::addOverlay(CFloatRect rect, CMaterial* MaterialNormal, bool bChromaKeying, std::string sName)
	{
		m_Overlays[sName] = new COverlay();
		m_Overlays[sName]->Init(MaterialNormal, createRelativeRectangle(&m_zfRect, &rect));
		m_viewport->AddOverlay(m_Overlays[sName]);

	}

	void VListView::setLayer(float layer)
	{
	}

	void VListView::addEntry(CMaterial* MaterialEntryNormal, CMaterial* MaterialEntryHover, std::string sName)
	{
		m_entries[sName] = new VListEntry(m_viewport, MaterialEntryNormal, MaterialEntryHover,sName);
		m_guiObjects[sName] = m_entries[sName];
		m_guiObjects[sName]->addObserverExt(this);
		calcEntrySize();
	}

	void VListView::onNotifyExt(Event evente, std::string sName)
	{
		switch (evente)
		{
		case LIST_ITEM_SELECTED:
			m_selectedItem = m_entries[sName];
			break;
		}
	}

	VListEntry* VListView::getSelectedItem()
	{
		return m_selectedItem;
	}

	void VListView::calcEntrySize()
	{
		int i = 0;
		for (m_IterEntries = m_entries.begin(); m_IterEntries != m_entries.end(); m_IterEntries++)
		{
			//GUI Object Size Mehode hinzufügen
			m_IterEntries->second->setRectangle(createRelativeRectangle(&m_zfRect, &CFloatRect(0.1F, 0.1* static_cast<float>(i)+0.1, 0.8F, 0.08)));
			m_IterEntries->second->updateRectangle(createRelativeRectangle(&m_zfRect, &CFloatRect(0.1F, 0.1 * static_cast<float>(i)+0.1, 0.8F, 0.08)));
			m_IterEntries->second->setLayer(0.1F);
			i++;
		}
	}


	VListView::~VListView()
{
	for (m_lIterGUIObjects = m_guiObjects.begin(); m_lIterGUIObjects != m_guiObjects.end(); ++m_lIterGUIObjects)
	{
		delete m_lIterGUIObjects->second;
	}
	m_guiObjects.clear();
	if (m_hasBackground) delete m_background;
}

NAMESPACE_VIEW_E
