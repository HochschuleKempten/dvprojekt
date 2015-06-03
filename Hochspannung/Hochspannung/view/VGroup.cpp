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

VGroup::VGroup(CViewport* viewport, CFloatRect floatRect, const std::string& sName)
{
	m_viewport = viewport;
	m_zfRect = floatRect;

	m_sName = sName;
}

VGroup::VGroup(CViewport* viewport, CFloatRect floatRect, CMaterial* materialbackground, const std::string& sName)
{
	m_viewport = viewport;
	m_zfRect = floatRect;
	m_background = new COverlay();
	m_background->SetLayer(0.9F);
	m_background->Init(materialbackground, m_zfRect);
	m_viewport->AddOverlay(m_background);
	m_hasBackground = true;

	m_sName = sName;
}

VGroup::~VGroup()
{
}


void VGroup::onNotify(const Event& events)
{
	switch (events)
	{
	default:
		notify(events);
	}
}

VButton* VGroup::addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, const Event& clickAction, const std::basic_string<char>& sName, const float layer)
{
	m_guiObjects[sName] = new VButton(m_viewport, rect, MaterialNormal, MaterialHover, clickAction, layer);

	m_guiObjects[sName]->addObserver(this);


	return CASTD<VButton*>(m_guiObjects[sName]);
}

VButton* VGroup::addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const Event& clickAction, const std::string& sName, const float layer)
{
	m_guiObjects[sName] = new VButton(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, MaterialActive, clickAction, layer);

	m_guiObjects[sName]->setName(sName);
	m_guiObjects[sName]->addObserver(this);


	return CASTD<VButton*>(m_guiObjects[sName]);
}

VTextfield* VGroup::addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int MaxChars, const std::basic_string<char>& Placeholder, const std::basic_string<char>& sName, const float layer)
{
	m_guiObjects[sName] = new VTextfield(m_viewport, rect, MaterialNormal, MaterialHover, MaterialActive, MaxChars, Placeholder, layer);

	m_guiObjects[sName]->addObserver(this);


	return CASTD<VTextfield*>(m_guiObjects[sName]);
}

VText* VGroup::addText(CFloatRect rect, CWritingFont* writingFont, const std::basic_string<char>& text, const std::basic_string<char>& sName, const float layer)
{
	m_guiObjects[sName] = new VText(m_viewport, rect, writingFont, text, layer);

	m_guiObjects[sName]->addObserver(this);


	return CASTD<VText*>(m_guiObjects[sName]);
}

COverlay* VGroup::addOverlay(CFloatRect rect, CMaterial* MaterialNormal, const std::basic_string<char>& sName, const float layer)
{
	m_Overlays[sName] = new COverlay();
	m_Overlays[sName]->Init(MaterialNormal, rect);
	m_viewport->AddOverlay(m_Overlays[sName]);


	return m_Overlays[sName];
}

void VGroup::addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::basic_string<char>& sName, const float layer)
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
		m_Guicontainer[sName] = new VGUIArea(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal,sName, layer);
		m_Guicontainer[sName]->addObserver(this);
		break;
	default: break;
	}
}

void VGroup::addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::basic_string<char>& sName, const float layer)
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
	default: break;
	}
}


NAMESPACE_VIEW_E
