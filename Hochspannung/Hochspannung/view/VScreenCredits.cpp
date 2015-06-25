#include "VScreenCredits.h"
#include "VUI.h"
#include <thread>
#include "VUIHelper.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B


VScreenCredits::VScreenCredits(VUI* vUi) : IViewScreen(vUi)
{
	m_viewport = new CViewport();
	m_camera.Init();
	m_viewport->InitFull(&m_camera);
	vUi->m_zf.AddViewport(m_viewport);

	//Cursor


	m_background = new CBackground();

	m_background->InitFull(&VMaterialLoader::materialBlack);

	

	topBorder = new COverlay();
	bottomBorder = new COverlay();
	topBorder->Init(&VMaterialLoader::materialErrorBackground, CFloatRect(0.0F, 0.0F, 1.0F, 0.05F));

	bottomBorder->Init(&VMaterialLoader::materialErrorBackground, CFloatRect(0.0F, 0.95F, 1.0F, 0.05F));

	rect = getRectForPixel((vUi->m_zf.m_iWidthWindow/2) - (1280/ 2), vUi->m_zf.m_iHeightWindow, 1280, 6500);

	
	

	materialCredits = new COverlay();

	escapeText = new VText(m_viewport, CFloatRect(0.80F, 0.83, 0.18F, 0.10F), &VMaterialLoader::standardFont, "Press escape to quit...",0.1F);
	
	
	materialCredits->Init(&VMaterialLoader::materialCredits, rect);
	materialCredits->SetLayer(0.3F);
	m_viewport->AddOverlay(materialCredits);
	m_viewport->AddOverlay(topBorder);
	m_viewport->AddOverlay(bottomBorder);

	m_viewport->AddBackground(m_background);

}

VScreenCredits::~VScreenCredits()
{
	delete materialCredits;
}

void VScreenCredits::startAnimation()
{
}

void VScreenCredits::StartEvent()
{
		std::thread([this] {
			std::this_thread::sleep_for(std::chrono::seconds(2));
			MoveText(materialCredits);
			animationReady = true;
		}).detach();
}

void VScreenCredits::EndEvent()
{
	materialCredits->SetRect(rect);
	
}

void VScreenCredits::onNotify(const Event& events)
{
	switch (events)
	{
	default:
		notify(events);
		break;
	}
}

void VScreenCredits::checkShortcut(CDeviceKeyboard* keyboard)
{
	
	if (keyboard->KeyPressed(DIK_ESCAPE))
	{
		animationStop = true;
		
	}
}

void VScreenCredits::checkSpecialEvent(CDeviceCursor* cursor)
{
}

void VScreenCredits::tick(const float fTimeDelta)
{
	if (!vUi->m_zkCursor.ButtonPressedLeft())
	{
		vUi->m_BlockCursorLeftPressed = false;
	}

	if (animationReady)
	{
		animationReady = false;
		vUi->switchScreen("MainMenue");
		return;
		
	}
	std::unordered_map<std::string, IViewGUIContainer*> tempGuiContainer;

	checkShortcut(&vUi->m_zkKeyboard);
	checkSpecialEvent(&vUi->m_zkCursor);
	tempGuiContainer = getGuiContainerMap();

	//For all containers in the screen
	for (const std::pair<std::string, IViewGUIContainer*>& ContainerPair : tempGuiContainer)
	{
		checkGUIContainer(ContainerPair.second);
	}

	if (vUi->m_zkCursor.ButtonPressedLeft())
	{
		vUi->m_BlockCursorLeftPressed = true;
	}
}

void VScreenCredits::checkGUIObjects(IViewGUIContainer* tempGuicontainer)
{
	std::unordered_map<std::string, IViewGUIObject*> tempGUIObjects = tempGuicontainer->getGuiObjectList();

	for (const std::pair<std::string, IViewGUIObject*>& ObjectPair : tempGUIObjects)
	{
		if (ObjectPair.second->isOn())
		{
			if (!vUi->m_BlockCursorLeftPressed)
			{
				//check for events
				ObjectPair.second->checkEvent(&vUi->m_zkCursor, &vUi->m_zkKeyboard);
			}
			//if screen was changed
			if (vUi->m_screenChanged)
			{
				vUi->m_screenChanged = false;

				vUi->m_BlockCursorLeftPressed = true;
				return;
			}
		}
	}
}


void VScreenCredits::checkGUIContainer(IViewGUIContainer* tempGuicontainer)
{
	std::unordered_map<std::string, IViewGUIContainer*> tempGuiContainerMap;

	tempGuiContainerMap = tempGuicontainer->getGuiContainerMap();

	checkGUIObjects(tempGuicontainer);
	for (const std::pair<std::string, IViewGUIContainer*>& ContainerPair : tempGuiContainerMap)
	{
		if (tempGuicontainer->getGuiContainerMap().size() > 0)
		{
			checkGUIContainer(ContainerPair.second);
		}
	}
}

void VScreenCredits::resize(const int width, const int height)
{
}

void VScreenCredits::MoveText(COverlay* overlay)
{
		for (float i = overlay->GetRect().GetYPos(); i > -overlay->GetRect().GetYSize(); i = i - 0.002F)
		{
			if (animationStop)
			{
				animationStop = false;
				return;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			CFloatRect tempRect = overlay->GetRect();
			tempRect.SetYPos(i);
			overlay->SetRect(tempRect);

		}
}

CFloatRect VScreenCredits::getRectForPixel(const int iPosX, const int iPosY, const int iSizeX, const int iSizeY)
{
	CFloatRect tempRectangle;
	const int iFensterBreite = vUi->m_zf.m_iWidthWindow;
	const int iFensterHöhe = vUi->m_zf.m_iHeightWindow;


	/* iFensterBreite/100% = iPosX/X% => iFensterbreite=(iPosX*100%)/x =>x=(iPosX*100%)/iFensterBreite */

	tempRectangle.SetXPos(iPosX / CASTS<float>(iFensterBreite));
	tempRectangle.SetYPos(iPosY / CASTS<float>(iFensterHöhe));
	tempRectangle.SetXSize(iSizeX / CASTS<float>(iFensterBreite));
	tempRectangle.SetYSize(iSizeY / CASTS<float>(iFensterHöhe));

	return tempRectangle;
}

NAMESPACE_VIEW_E
