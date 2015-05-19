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
			Credits,
			Ingame,
			Lobby
		};

		enum CursorType
		{
			Default,
			Hammer,
			Sabotage,
		};

		virtual void switchOn()
		{
			m_viewport->SwitchOn();
			m_isOn = true;
		}

		virtual void switchOff()
		{
			m_viewport->SwitchOff();
			m_isOn = false;
		}

		inline void addContainer(CViewport* viewport, const IViewGUIContainer::ContainerType& containerType, const CFloatRect& floatRect, const std::string& sName)
		{
			m_viewport = viewport;
			switch (containerType)
			{
			case IViewGUIContainer::Group:
				m_Guicontainer[sName] = new VGroup(m_viewport, floatRect);
				m_Guicontainer[sName]->addObserver(this);
				break;
			case IViewGUIContainer::Dialog:
				m_Guicontainer[sName] = new VDialog(m_viewport, floatRect);
				m_Guicontainer[sName]->addObserver(this);
				break;
			case IViewGUIContainer::Register:
				m_Guicontainer[sName] = new VRegister(floatRect, m_viewport);
				m_Guicontainer[sName]->addObserver(this);
				break;
			case IViewGUIContainer::GUIArea:
				m_Guicontainer[sName] = new VGUIArea(m_viewport, floatRect);
				m_Guicontainer[sName]->addObserver(this);
				break;
			case IViewGUIContainer::ListView:
				m_Guicontainer[sName] = new VListView(floatRect,m_viewport);
				m_Guicontainer[sName]->addObserver(this);
				break;
			}
		}

		inline void addContainer(CViewport* viewport, const IViewGUIContainer::ContainerType& containerType, const CFloatRect& floatRect, CMaterial* materialBackground, const std::string& sName)
		{
			m_viewport = viewport;
			switch (containerType)
			{
			case IViewGUIContainer::Group:
				m_Guicontainer[sName] = new VGroup(m_viewport, floatRect, materialBackground);
				m_Guicontainer[sName]->addObserver(this);
				break;
			case IViewGUIContainer::Dialog:
				m_Guicontainer[sName] = new VDialog(m_viewport, floatRect, materialBackground);
				m_Guicontainer[sName]->addObserver(this);
				break;
			case IViewGUIContainer::Register:
				m_Guicontainer[sName] = new VRegister(floatRect, m_viewport, materialBackground);
				m_Guicontainer[sName]->addObserver(this);
				break;
			case IViewGUIContainer::GUIArea:
				m_Guicontainer[sName] = new VGUIArea(m_viewport, floatRect, materialBackground);
				m_Guicontainer[sName]->addObserver(this);
				break;
			case IViewGUIContainer::ListView:
				m_Guicontainer[sName] = new VListView(floatRect,m_viewport, materialBackground);
				m_Guicontainer[sName]->addObserver(this);
				break;
			}
		}

		IViewGUIContainer* getContainer(const std::string& sName)
		{
			ASSERT(m_Guicontainer.find(sName) != m_Guicontainer.end(), "GUIContainer not available");
			return m_Guicontainer[sName];
		}

		std::unordered_map<std::string, IViewGUIContainer*> getGuiContainerMap()
		{
			return m_Guicontainer;
		}

		bool isOn()
		{
			return m_isOn;
		}

		virtual void checkShortcut(CDeviceKeyboard* keyboard) =0;
		virtual void checkSpecialEvent(CDeviceCursor* cursor) = 0;
		virtual void tick(const float fTimeDelta) = 0;
		virtual void resize(const int width, const int height) = 0;


		virtual void startAnimation() = 0;

		virtual void StartEvent() = 0;

		virtual void EndEvent() = 0;

		void switchCursor(const CursorType& cursorType)
		{
			switch (cursorType)
			{
			default:
				break;
			case Default:
				delete m_pCursorImage;

				m_pCursorImage = new COverlay();
				m_pCursorImage->Init(&VMaterialLoader::m_zmDefaultCursor, CFloatRect(0.0F, 0.0F, 0.05F, 0.05F));
				m_viewport->AddOverlay(m_pCursorImage);
				m_pCursorImage->SetLayer(0.0F);
				break;
			case Hammer:
				delete m_pCursorImage;

				m_pCursorImage = new COverlay();
				m_pCursorImage->Init(&VMaterialLoader::m_zmHammerCursor, CFloatRect(0.0F, 0.0F, 0.05F, 0.05F));
				m_viewport->AddOverlay(m_pCursorImage);
				m_pCursorImage->SetLayer(0.0F);
				break;
			case Sabotage:
				delete m_pCursorImage;

				m_pCursorImage = new COverlay();
				m_pCursorImage->Init(&VMaterialLoader::materialRed, CFloatRect(0.0F, 0.0F, 0.05F, 0.05F));
				m_viewport->AddOverlay(m_pCursorImage);
				m_pCursorImage->SetLayer(0.0F);
				break;
			}
		}

		void switchCursor(char* imagefile, const bool bChromaKeying)
		{
			m_viewport->SubOverlay(m_pCursorImage);
			delete m_pCursorImage;
			m_pCursorImage = new COverlay();
			m_pCursorImage->Init(imagefile, CFloatRect(0.0F, 0.0F, 0.05F, 0.05F), bChromaKeying);
			m_viewport->AddOverlay(m_pCursorImage);
			m_pCursorImage->SetLayer(0.0F);
		}

	
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
		CViewport* m_viewport;
		CCamera m_camera;
		ScreenType m_screenType;
		COverlay* m_pCursorImage = nullptr;

		bool m_isOn = false;

	};


	NAMESPACE_VIEW_E
