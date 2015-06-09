#include "VRegister.h"
#include "VGroup.h"
#include "VDialog.h"
#include "VMaterialLoader.h"
#include "VGUIArea.h"

NAMESPACE_VIEW_B

VRegister::VRegister()
{
}

VRegister::VRegister(CFloatRect floatRect, CViewport* viewport, const std::string& sName, const float layer) :
activeTab(nullptr)
{
	m_fLayer = layer;
	m_viewport = viewport;
	m_zfRect = floatRect;

	m_sName = sName;
}

VRegister::VRegister(CFloatRect floatRect, CViewport* viewport, CMaterial* materialBackground, const std::string& sName, const float layer) :
activeTab(nullptr)
{
	m_fLayer = layer;
	m_viewport = viewport;
	m_zfRect = floatRect;
	m_background = new COverlay();
	m_background->SetLayer(m_fLayer);
	m_background->Init(materialBackground, m_zfRect);
	//float breiteButton = floatRect.GetXSize() / anzahlRegisterkarten;
	m_viewport->AddOverlay(m_background);
	m_hasBackground = true;

	m_sName = sName;
}

VRegister::~VRegister()
{
	for (std::pair<std::string, VTab*> TabPair : m_tabs)
	{
		delete TabPair.second;
	}
	m_tabs.clear();
}

void VRegister::onNotify(const Event& events)
{
	switch (events)
	{
	default:
		notify(events);
		break;
	}
}

void VRegister::addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::basic_string<char>& sName, const float layer)
{
	switch (containerType)
	{
	case Group:
		m_Guicontainer[sName] = new VGroup(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal,sName);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case Dialog:
		m_Guicontainer[sName] = new VDialog(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal, sName, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case Register:
		m_Guicontainer[sName] = new VRegister(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport, MaterialNormal, sName, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case GUIArea:
		m_Guicontainer[sName] = new VGUIArea(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal, sName, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	default: break;
	}
}

void VRegister::addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::basic_string<char>& sName, const float layer)
{
	switch (containerType)
	{
	case Group:
		m_Guicontainer[sName] = new VGroup(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), sName);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case Dialog:
		m_Guicontainer[sName] = new VDialog(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), sName, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case Register:
		m_Guicontainer[sName] = new VRegister(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport,sName, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case GUIArea:
		m_Guicontainer[sName] = new VGUIArea(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect),sName, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	default: break;
	}
}


void VRegister::addTab(CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* background, const Event& events, const std::string& sName, const float layer)
{
	m_Guicontainer[sName] = new VTab(m_viewport, createRelativeRectangle(&m_zfRect, &CFloatRect(0.0F, 0.2F, 1.0F, 0.8F)), background, sName, layer);
	m_tabs[sName] = dynamic_cast<VTab*>(m_Guicontainer[sName]);
	m_Guicontainer[sName]->addObserver(this);

	addButton(CFloatRect(0.0F, 0.0F, 0.5F, 0.1F), MaterialNormal, MaterialHover, events, sName, layer - 0.01F);
	calcButtonSize();
}

void VRegister::addTab(CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, CMaterial* background, const Event& events, const std::string& sName, const float layer)
{
	m_Guicontainer[sName] = new VTab(m_viewport, createRelativeRectangle(&m_zfRect, &CFloatRect(0.0F, 0.2F, 1.0F, 0.8F)), background, sName, layer);
	m_tabs[sName] = dynamic_cast<VTab*>(m_Guicontainer[sName]);
	m_Guicontainer[sName]->addObserver(this);

	addButton(CFloatRect(0.0F, 0.0F, 0.5F, 0.1F), MaterialNormal, MaterialHover, MaterialActive, events, sName, layer - 0.01F);
	calcButtonSize();
}

void VRegister::calcButtonSize()
{
	int i = 0;
	for (std::pair<std::string, IViewGUIObject*> ObjectPair : m_guiObjects)
	{
		//GUI Object Size Mehode hinzufügen
		CFloatRect tempRect = ObjectPair.second->getRectangle();
		ObjectPair.second->setRectangle(createRelativeRectangle(&m_zfRect, &CFloatRect(1.0F / static_cast<float>(m_guiObjects.size()) * static_cast<float>(i), 0.0F, 1.0F / static_cast<float>(m_guiObjects.size()), 0.2F)));
		ObjectPair.second->updateRectangle(createRelativeRectangle(&m_zfRect, &CFloatRect(1.0F / static_cast<float>(m_guiObjects.size()) * static_cast<float>(i), 0.0F, 1.0F / static_cast<float>(m_guiObjects.size()), 0.2F)));
		//ObjectPair.second->setLayer(0.3F);
		i++;
	}
}

void VRegister::SwitchToTab(const std::string& sName)
{
	std::unordered_map<std::string, VTab*>::iterator it = m_tabs.find(sName);
	ASSERT(it != m_tabs.end(), "Tab not available");

	/*for (it = m_tabs.begin(); it != m_tabs.end(); it++)
	{
		it->second->switchOff();
	}*/

	if (activeTab)
	{
		activeTab->switchOff();

		CASTD<VButton*>(getGuiObject(activeTab->getName()))->setActive(false);
	}
	else
	{
		for (std::pair<std::string,VTab*> tab :m_tabs)
		{
			tab.second->switchOff();
			CASTD<VButton*>(getGuiObject(tab.second->getName()))->setActive(false);
		}
	}

	m_tabs[sName]->switchOn();
	activeTab = m_tabs[sName];
	CASTD<VButton*>(getGuiObject(sName))->setActive();
}

VTab* VRegister::getTab(const std::string& sName)
{
	std::unordered_map<std::string, VTab*>::iterator it = m_tabs.find(sName);
	ASSERT(it != m_tabs.end(), "Tab not available");
	return m_tabs[sName];
}

VTab* VRegister::getActiveTab()
{
	return activeTab;
}

void VRegister::setActiveTab(const std::string& sName)
{
	std::unordered_map<std::string, VTab*>::iterator it = m_tabs.find(sName);
	ASSERT(it != m_tabs.end(), "Tab not available");

	if (activeTab)
		CASTD<VButton*>(getGuiObject(activeTab->getName()))->setActive(false);

	activeTab = m_tabs[sName];
	CASTD<VButton*>(getGuiObject(sName))->setActive();
}

NAMESPACE_VIEW_E
