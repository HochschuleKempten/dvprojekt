#include "VGUIArea.h"
#include "VGroup.h"
#include "VRegister.h"
#include "VDialog.h"
#include "VListView.h"

NAMESPACE_VIEW_B

VGUIArea::VGUIArea()
{
}


VGUIArea::VGUIArea(CViewport* viewport, CFloatRect floatRect, const std::string& sName, const float layer)
{
	m_fLayer = layer;
	m_viewport = viewport;
	m_zfRect = floatRect;

	m_sName = sName;
}

VGUIArea::VGUIArea(CViewport* viewport, CFloatRect floatRect, CMaterial* materialbackground, const std::string& sName, const float layer)
{
	m_fLayer = layer;
	m_viewport = viewport;
	m_zfRect = floatRect;
	m_background = new COverlay();
	m_background->SetLayer(m_fLayer);
	m_background->Init(materialbackground, m_zfRect);
	m_viewport->AddOverlay(m_background);
	m_hasBackground = true;

	m_sName = sName;
}

VGUIArea::~VGUIArea()
{
}

void VGUIArea::onNotify(const Event& events)
{
	switch (events)
	{
	default:
		notify(events);
	}
}


void VGUIArea::addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::basic_string<char>& sName, const float layer)
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
	case ListView:
		m_Guicontainer[sName] = new VListView(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport, MaterialNormal, sName, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	default: break;
	}
}

void VGUIArea::addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::basic_string<char>& sName, const float layer)
{
	switch (containerType)
	{
	case Group:
		m_Guicontainer[sName] = new VGroup(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect),sName);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case Dialog:
		m_Guicontainer[sName] = new VDialog(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), sName, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case Register:
		m_Guicontainer[sName] = new VRegister(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport, sName, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case GUIArea:
		m_Guicontainer[sName] = new VGUIArea(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), sName, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	case ListView:
		m_Guicontainer[sName] = new VListView(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport, sName, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	default: break;
	}
}


NAMESPACE_VIEW_E
