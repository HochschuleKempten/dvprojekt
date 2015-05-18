#pragma once

#include "IViewScreen.h"
#include "VIdentifier.h"
#include "VModelWindmillPowerPlant.h"
#include "VModelSolarPowerplant.h"
#include "VModelNuclearPowerPlant.h"
#include "VModelOilRefinery.h"
#include "VModelPowerLine.h"

NAMESPACE_VIEW_B


class VScreenIngame : public IViewScreen
{
public:
	explicit VScreenIngame(VUI* vUi);
	virtual ~VScreenIngame();
	void onNotify(const Event& events) override;
	void switchOn() override;
	void switchOff() override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
	void checkSpecialEvent(CDeviceCursor* cursor) override;

	//Schnittstellenmethoden
	void updateMoney(const int wert);

	void updatePopulation(const int wert);

	void updateInfofield(const std::string& neuerText);

	CFloatRect getTopSpace();

	CFloatRect getBottomSpace();

	void tick(const float fTimeDelta) override;
	void checkGUIObjects(IViewGUIContainer* tempGuicontainer);
	void checkGUIContainer(IViewGUIContainer* tempGuicontainer);
	void resize(const int width, const int height) override;

	void handleInput();
	std::map<int, std::vector<int>> pickElements();

	void addToScene(CPlacement* placement);

	void startAnimation() override;
	void StartEvent() override;
	void EndEvent() override;

private:
	CFloatRect getRectForPixel(const int iPosX, const int iPosY, const int iSizeX, const int iSizeY);
	void handleLeftClick(const std::map<int, std::vector<int>>& pickedElements);
	void handleRightClick(const std::map<int, std::vector<int>>& pickedElements);

	CScene m_scene;
	//CViewport m_viewport;
	CBackground m_zb;
	CParallelLight m_zl;
	CCamera m_zc;
	CPlacement m_zpCamera;

	COverlay m_bottomBar;
	COverlay m_topBar;
	COverlay m_bottomBarBorderTop;
	COverlay m_bottomBarBorderBottom;
	COverlay m_bottomBarBorderLeft;
	COverlay m_bottomBarBorderRight;
	COverlay m_bottomBarSeperatorMenueInfofeld;
	COverlay m_bottomBarSeperatorMenueMinimap;
	COverlay m_bottomBarSeperatorMenueEnergy;

	//bool bK = false;
	float mouseWheelPosition = 0.0F;
	float cameraAngle = 0.0F;

	VIdentifier::VIdentifier m_selectedBuilding = VIdentifier::Undefined;
	bool clickActive = false;

	//Detailled model view
	CScene m_sceneModels;
	CParallelLight m_zlModels;
	CCamera m_CamModels;
	CViewport m_viewportModels;
	CBackground m_zmbackgroundModels;
	CPlacement m_zpModels;

	VModelWindmillPowerPlant modelWindmill;
	VModelSolarPowerPlant modelSolar;
	VModelNuclearPowerPlant modelNuclear;
	VModelOilRefinery modelOil;
	VModelPowerLine modelPowerline;
	std::unordered_map<VIdentifier::VIdentifier, IViewModel*> models;

	void updateModelView();
};


NAMESPACE_VIEW_E
