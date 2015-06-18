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
	topBorder->Init(&VMaterialLoader::materialErrorBackground, CFloatRect(0.0F, 0.0F, 1.0F, 0.05F));

	rect = getRectForPixel((vUi->m_zf.m_iWidthWindow/2) - (1280/ 2), vUi->m_zf.m_iHeightWindow, 1280, 720);

	
	
	
	materialCreditsOrganization=new COverlay();
	materialCreditsIntegration = new COverlay();
	materialCreditsTextures = new COverlay();
	materialCreditsNetwork = new COverlay();
	materialCreditsLogic = new COverlay();
	materialCreditsUI = new COverlay();
	materialCreditsModelling = new COverlay();
	materialCreditsModelling2 = new COverlay();
	materialCreditsVektoriaSplash = new COverlay();

	materialCreditsOrganization->Init(&VMaterialLoader::materialCreditsOrganization,rect);
	materialCreditsIntegration->Init(&VMaterialLoader::materialCreditsIntegration, rect);
	materialCreditsTextures->Init(&VMaterialLoader::materialCreditsTextures, rect);
	materialCreditsNetwork->Init(&VMaterialLoader::materialCreditsNetwork, rect);
	materialCreditsLogic->Init(&VMaterialLoader::materialCreditsLogic, rect);
	materialCreditsUI->Init(&VMaterialLoader::materialCreditsUI, rect);
	materialCreditsModelling->Init(&VMaterialLoader::materialCreditsModelling, rect);
	materialCreditsModelling2->Init(&VMaterialLoader::materialCreditsModelling2, rect);

	materialCreditsVektoriaSplash->Init(&VMaterialLoader::materialCreditsVektoriaSplash, getRectForPixel((vUi->m_zf.m_iWidthWindow / 2) - (1000 / 2), vUi->m_zf.m_iHeightWindow, 1000, 600));


	m_viewport->AddOverlay(materialCreditsOrganization);
	m_viewport->AddOverlay(materialCreditsIntegration);
	m_viewport->AddOverlay(materialCreditsTextures);
	m_viewport->AddOverlay(materialCreditsNetwork);
	m_viewport->AddOverlay(materialCreditsLogic);
	m_viewport->AddOverlay(materialCreditsUI);
	m_viewport->AddOverlay(materialCreditsModelling);
	m_viewport->AddOverlay(materialCreditsModelling2);
	m_viewport->AddOverlay(materialCreditsVektoriaSplash);


	materialCreditsOrganization->SetLayer(0.3F);
	materialCreditsIntegration->SetLayer(0.3F);
	materialCreditsTextures->SetLayer(0.3F);
	materialCreditsNetwork->SetLayer(0.3F);
	materialCreditsLogic->SetLayer(0.3F);
	materialCreditsUI->SetLayer(0.3F);
	materialCreditsModelling->SetLayer(0.3F);
	materialCreditsModelling2->SetLayer(0.3F);

	
	m_viewport->AddOverlay(topBorder);

	m_viewport->AddBackground(m_background);

}

VScreenCredits::~VScreenCredits()
{
	delete materialCreditsOrganization;
	delete materialCreditsIntegration;
	delete materialCreditsTextures;
	delete materialCreditsNetwork;
	delete materialCreditsLogic;
	delete materialCreditsUI;
	delete materialCreditsModelling;
	delete materialCreditsModelling2;
	delete materialCreditsVektoriaSplash;
}

void VScreenCredits::startAnimation()
{
}

void VScreenCredits::StartEvent()
{
	std::thread([this] {

		std::thread([this] {MoveText(materialCreditsOrganization); }).detach();

		std::this_thread::sleep_for(std::chrono::seconds(3));

		std::thread([this] {MoveText(materialCreditsIntegration); }).detach();

		std::this_thread::sleep_for(std::chrono::seconds(4));
		

		std::thread([this] {MoveText(materialCreditsNetwork); }).detach();

		std::this_thread::sleep_for(std::chrono::seconds(5));


		std::thread([this] {MoveText(materialCreditsTextures); }).detach();

		std::this_thread::sleep_for(std::chrono::seconds(5));


		std::thread([this] {MoveText(materialCreditsLogic); }).detach();

		std::this_thread::sleep_for(std::chrono::seconds(5));


		std::thread([this] {MoveText(materialCreditsUI); }).detach();

		std::this_thread::sleep_for(std::chrono::seconds(5));


		std::thread([this] {MoveText(materialCreditsModelling); }).detach();

		std::this_thread::sleep_for(std::chrono::seconds(4));


		std::thread([this] {MoveText(materialCreditsModelling2); }).detach();

		std::this_thread::sleep_for(std::chrono::seconds(6));


		std::thread([this] {MoveText(materialCreditsVektoriaSplash); animationReady = true; }).detach();



	}).detach();

}

void VScreenCredits::EndEvent()
{
	materialCreditsOrganization->SetRect(rect);
	materialCreditsIntegration->SetRect(rect);
	materialCreditsTextures->SetRect(rect);
	materialCreditsNetwork->SetRect(rect);
	materialCreditsLogic->SetRect(rect);
	materialCreditsUI->SetRect(rect);
	materialCreditsModelling->SetRect(rect);
	materialCreditsModelling2->SetRect(rect);
	materialCreditsVektoriaSplash->SetRect(getRectForPixel((vUi->m_zf.m_iWidthWindow / 2) - (1000 / 2), vUi->m_zf.m_iHeightWindow, 1000, 600));
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
	static bool running = false;


	if (keyboard->KeyPressed(DIK_M)&&!running)
	{
		running = true;
		
		
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
		vUi->switchScreen("MainMenue");
		animationReady = false;
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
	//std::thread([this] {
		/*while (getContainer("Text")->getContainer("1")->getRectangle().GetYPos() > -1.25F)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			getContainer("Text")->getContainer("1")->slideUp(0.05F);
		}*/
	//}).detach();

	

	
		for (float i = overlay->GetRect().GetYPos(); i > -overlay->GetRect().GetYSize(); i = i - 0.002F)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			CFloatRect tempRect = overlay->GetRect();
			tempRect.SetYPos(i);
			overlay->SetRect(tempRect);

		}
	
	/*CFloatRect tempRect;
	while (getContainer("Text")->getContainer("1")->getRectangle().GetYPos() > -1.25F)
	{
		tempRect = getContainer("Text")->getContainer("1")->getRectangle();
		tempRect.SetYPos(tempRect.GetYPos() - 0.03F);
		CASTD<VText*>(getContainer("Text")->getContainer("1")->getGuiObject("GUI"))->updateRectangle(tempRect);
		
	}*/
	
}

CFloatRect VScreenCredits::getRectForPixel(const int iPosX, const int iPosY, const int iSizeX, const int iSizeY)
{
	CFloatRect tempRectangle;
	const int iFensterBreite = vUi->m_zf.m_iWidthWindow;
	const int iFensterHöhe = vUi->m_zf.m_iHeightWindow;

	//ASSERT((((iPosX + iSizeX) <= iFensterBreite) && ((iPosY + iSizeY) <= iFensterHöhe)), "Angegebener Bereich liegt außerhalb des Fensters");

	/* iFensterBreite/100% = iPosX/X% => iFensterbreite=(iPosX*100%)/x =>x=(iPosX*100%)/iFensterBreite */

	tempRectangle.SetXPos(iPosX / CASTS<float>(iFensterBreite));
	tempRectangle.SetYPos(iPosY / CASTS<float>(iFensterHöhe));
	tempRectangle.SetXSize(iSizeX / CASTS<float>(iFensterBreite));
	tempRectangle.SetYSize(iSizeY / CASTS<float>(iFensterHöhe));

	return tempRectangle;
}

NAMESPACE_VIEW_E
