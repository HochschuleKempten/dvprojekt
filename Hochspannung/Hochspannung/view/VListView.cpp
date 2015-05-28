#include "VListView.h"
#include "VGroup.h"
#include "VDialog.h"
#include "VRegister.h"
#include "VGUIArea.h"
#include "VMaterialLoader.h"
NAMESPACE_VIEW_B


VListView::VListView()
{
}

VListView::VListView(CFloatRect floatRect, CViewport* viewport, const float layer)
{
	m_viewport = viewport;
	m_zfRect = floatRect;
	m_fLayer = layer;
}

VListView::VListView(CFloatRect floatRect, CViewport* viewport, CMaterial* materialBackground, const float layer)
{
	m_fLayer = layer;
	m_viewport = viewport;
	m_zfRect = floatRect;
	m_background = new COverlay();
	m_background->SetLayer(m_fLayer);
	m_background->Init(materialBackground, m_zfRect);
	m_viewport->AddOverlay(m_background);
	m_hasBackground = true;
}

void VListView::onNotify(const Event& evente)
{
	switch (evente)
	{
	default:
		notify(evente);
		break;
	}
}

void VListView::addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::basic_string<char>& sName, const float layer)
{
	switch (containerType)
	{
	case Group:
		m_Guicontainer[sName] = new VGroup(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect));
		m_Guicontainer[sName]->addObserver(this);
		break;
	case Dialog:
		m_Guicontainer[sName] = new VDialog(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case Register:
		m_Guicontainer[sName] = new VRegister(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case GUIArea:
		m_Guicontainer[sName] = new VGUIArea(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	default: break;
	}
}

void VListView::addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::basic_string<char>& sName, const float layer)
{
	switch (containerType)
	{
	case Group:
		m_Guicontainer[sName] = new VGroup(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case Dialog:
		m_Guicontainer[sName] = new VDialog(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case Register:
		m_Guicontainer[sName] = new VRegister(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport, MaterialNormal, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case GUIArea:
		m_Guicontainer[sName] = new VGUIArea(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	default: break;
	}
}


void VListView::setLayer(float layer)
{
}

void VListView::addEntry(const std::string& sName, const float layer)
{
	m_entries.push_back(sName);
	m_guiObjects[sName] = new VListEntry(m_viewport, &VMaterialLoader::materialListEntryBackground, &VMaterialLoader::materialListEntryHoverBackground, sName, layer);
	m_guiObjects[sName]->addObserverExt(this);
	calcEntrySize();
}

void VListView::updateList(const std::vector<Network::CGameObject>& hostList)
{
	for (const std::string& key : m_entries)
	{
		delete m_guiObjects[key];
		m_guiObjects.erase(key);
	}
	m_entries.clear();

	for (const Network::CGameObject& go : hostList)
	{
		m_entries.push_back(go.getServerIP());
		addEntry(go.getServerIP(), getLayer() - 0.01F);
	}
}

void VListView::onNotifyExt(const Event& evente, const std::basic_string<char>& sName)
{
	switch (evente)
	{
	case LIST_ITEM_SELECTED:
		m_selectedItem = m_guiObjects[sName];
		break;
	}
}

IViewGUIObject* VListView::getSelectedItem()
{
	return m_selectedItem;
}

void VListView::calcEntrySize()
{
	int i = 0;
	for (const std::string& sName : m_entries)
	{
		//GUI Object Size Mehode hinzufügen
		m_guiObjects[sName]->setRectangle(createRelativeRectangle(&m_zfRect, &CFloatRect(0.001F, 0.08F * static_cast<float>(i) + 0.15F, 0.99F, 0.08F)));
		m_guiObjects[sName]->updateRectangle(createRelativeRectangle(&m_zfRect, &CFloatRect(0.08F, 0.05F * static_cast<float>(i) + 0.15F, 0.82F, 0.08F)));
		i++;
	}
}


VListView::~VListView()
{
	//TODO refactor
	//for (m_lIterGUIObjects = m_guiObjects.begin(); m_lIterGUIObjects != m_guiObjects.end(); ++m_lIterGUIObjects)
	//{
	//	delete m_lIterGUIObjects->second;
	//}
	//m_guiObjects.clear();
	//if (m_hasBackground) delete m_background;
}

NAMESPACE_VIEW_E
