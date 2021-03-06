#pragma once
#include "VGeneral.h"
#include "IViewGUIContainer.h"
#include "IViewUIObserver.h"
#include "IViewSubject.h"
#include "VGroup.h"
#include "VMaterialLoader.h"
#include "VDialog.h"
#include "VRegister.h"
#include "VGUIArea.h"
#include "VListView.h"

NAMESPACE_VIEW_B


//---------------------------------------------------
// IScreen Interface
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------

class VUI;


class IViewScreen:public IViewUIObserver, public IViewSubject
{
public:
	explicit IViewScreen(VUI* vUi)
		: vUi(vUi)
	{
	}

	virtual ~IViewScreen()
	{
		for (const std::pair<std::string, IViewGUIContainer*>& ContainerPair : m_Guicontainer)
		{
			delete ContainerPair.second;
		}
		m_Guicontainer.clear();

		delete m_viewport;
		delete m_pCursorImage;
	}

	enum ScreenType
	{
		MainMenue,
		Options,
		Help,
		Controls,
		Credits,
		Ingame,
		Lobby,
		GameOver
	};


	virtual void switchOn()
	{
		ASSERT(m_viewport != nullptr, "Viewport is not initialized");

		m_viewport->SwitchOn();
		m_isOn = true;
	}

	virtual void switchOff()
	{
		ASSERT(m_viewport != nullptr, "Viewport is not initialized");

		m_viewport->SwitchOff();
		m_isOn = false;
	}

	inline void addContainer(CViewport* viewport, const IViewGUIContainer::ContainerType& containerType, const CFloatRect& floatRect, const std::string& sName, const float layer)
	{
		m_viewport = viewport;
		switch (containerType)
		{
		case IViewGUIContainer::Group:
			m_Guicontainer[sName] = new VGroup(m_viewport, floatRect, sName);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::Dialog:
			m_Guicontainer[sName] = new VDialog(m_viewport, floatRect, sName, layer);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::Register:
			m_Guicontainer[sName] = new VRegister(floatRect, m_viewport, sName, layer);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::GUIArea:
			m_Guicontainer[sName] = new VGUIArea(m_viewport, floatRect, sName, layer);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::ListView:
			m_Guicontainer[sName] = new VListView(floatRect, m_viewport, sName, layer);
			m_Guicontainer[sName]->addObserver(this);
			break;
		}
	}

	inline void addContainer(CViewport* viewport, const IViewGUIContainer::ContainerType& containerType, const CFloatRect& floatRect, CMaterial* materialBackground, const std::string& sName, const float layer)
	{
		m_viewport = viewport;
		switch (containerType)
		{
		case IViewGUIContainer::Group:
			m_Guicontainer[sName] = new VGroup(m_viewport, floatRect, materialBackground,sName);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::Dialog:
			m_Guicontainer[sName] = new VDialog(m_viewport, floatRect, materialBackground, sName, layer);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::Register:
			m_Guicontainer[sName] = new VRegister(floatRect, m_viewport, materialBackground, sName, layer);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::GUIArea:
			m_Guicontainer[sName] = new VGUIArea(m_viewport, floatRect, materialBackground, sName, layer);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case IViewGUIContainer::ListView:
			m_Guicontainer[sName] = new VListView(floatRect, m_viewport, materialBackground, sName, layer);
			m_Guicontainer[sName]->addObserver(this);
			break;
		}
	}

	IViewGUIContainer* getContainer(const std::string& sName)
	{
		ASSERT(m_Guicontainer.find(sName) != m_Guicontainer.end(), "GUIContainer not available");
		return m_Guicontainer[sName];
	}

	const std::unordered_map<std::string, IViewGUIContainer*> &getGuiContainerMap()
	{
		return m_Guicontainer;
	}

	bool isOn()
	{
		return m_isOn;
	}

	virtual void checkShortcut(CDeviceKeyboard* keyboard) =0;
	virtual void checkSpecialEvent() = 0;
	virtual void tick(const float fTimeDelta) = 0;
	virtual void resize(const int width, const int height) = 0;


	virtual void startAnimation() = 0;

	virtual void StartEvent() = 0;

	virtual void EndEvent() = 0;


	virtual void updateCursorImagePos(CDeviceCursor* cursor)
	{
		float curPosX;
		float curPosY;

		cursor->GetFractional(curPosX, curPosY, true);
		m_pCursorImage->SetRect(CFloatRect(curPosX, curPosY, 0.05F, 0.05F));
		//m_pCursorImage->GetRect().SetYPos(curPosY);
	}


protected:
	std::unordered_map<std::string, IViewGUIContainer*> m_Guicontainer;

	VUI* vUi;
	CViewport* m_viewport = nullptr;
	CCamera m_camera;
	ScreenType m_screenType = CASTS<ScreenType>(-1);
	COverlay* m_pCursorImage = nullptr;

	bool m_isOn = false;
};


NAMESPACE_VIEW_E
