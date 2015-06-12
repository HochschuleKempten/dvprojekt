#pragma once

#include "IViewScreen.h"
#include "VIdentifier.h"
#include "VModelWindmillPowerPlant.h"
#include "VModelSolarPowerplant.h"
#include "VModelNuclearPowerPlant.h"
#include "VModelOilRefinery.h"
#include "VModelPowerLine.h"
#include "VModelHydroelectricPowerPlant.h"

NAMESPACE_VIEW_B


class VScreenIngame : public IViewScreen
{
public:
	enum BUILDINGTYPE
	{
		BUILDING_WINDMILL,
		BUILDING_HYDROPOWERPLANT,
		BUILDING_SOLARPOWERPLANT,
		BUILDING_NUCLEARPOWERPLANT,
		BUILDING_COALPOWERPLANT,
		BUILDING_OILPOWERPLANT,
		BUILDING_POWERLINE
	};

	enum INTERACTIONS
	{
		SABOTAGE_CUTPOWERLINE,
		SABOTAGE_STRIKE,
		SABOTAGE_HALF
	};

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
	void updateAddedPowerPlant(const LIdentifier::LIdentifier id);
	void updateRemovedPowerPlant(const LIdentifier::LIdentifier id);
	void updateNumberPowerLines(const int newNumberPowerLines);
	void updatePowerPlants();
	void updateGraphProdNeeded(float fProduced, float fNeeded);
	void updateEnergyOverload(int overload);
	void updateOwnGraphRatio(float fRatio);
	void updateEnemyGraphRatio(float fRatio);

	CFloatRect getTopSpace();

	CFloatRect getBottomSpace();

	void tick(const float fTimeDelta) override;
	void checkGUIObjects(IViewGUIContainer* tempGuicontainer);
	void checkGUIContainer(IViewGUIContainer* tempGuicontainer);
	void resize(const int width, const int height) override;

	void addToScene(CPlacement* placement);

	void startAnimation() override;
	void StartEvent() override;
	void EndEvent() override;

	void setActiveButton(const std::string& sName);

	std::unordered_map<std::string, IViewGUIObject*> getScreenObjects();
	std::unordered_map<std::string, IViewGUIObject*> getObjects(IViewGUIContainer* container);

	void showMessage(const std::string& messageRow1, const std::string& messageRow2, const int timeSeconds);
	void startCooldown(const INTERACTIONS interaction);

private:

	void clearInfofield();

	void hideBottomBar();

	void handleInput();
	std::map<int, std::vector<int>> pickElements();

	CFloatRect getRectForPixel(const int iPosX, const int iPosY, const int iSizeX, const int iSizeY);
	void handleLeftClick(const std::map<int, std::vector<int>>& pickedElements);

	bool tryBuilding(const int x, const int y);
	bool trySabotage(const int x, const int y);
	bool tryBuildingInteraction(const int x, const int y);

	void updateModelView();

	void SabotageTabSwitchOn();

	void SabotageTabSwitchOff();


	VButton* activeButton = nullptr;

	CScene m_scene;
	CCamera m_zc;
	CPlacement m_zpCamera;


	VRegister* vrRegister;

	//Lightning
	CParallelLight m_zl;
	CSpotLight m_zlSpot;
	CPlacement m_zpSpot;
	CHVector m_PointingSpot;

	IViewGUIContainer* m_vtTopbar;
	VTab* m_vtTabStatistics;
	VTab* m_vtTabSabotage;
	VTab* m_vtTabBuilding;


	VGraph *m_vgGraphEnergy;
	VGraphRatio *m_vgGraphEnergyRatioOwn;
	VGraphRatio *m_vgGraphEnergyRatioEnemy;


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
	int cameraAngle = 0;

	VIdentifier::VIdentifier selectedBuilding = VIdentifier::Undefined;
	bool clickActive = false;

	std::map<BUILDINGTYPE, int> statPlacedBuildings;
	std::map<BUILDINGTYPE, std::string> m_powerPlantsNameMapping;

	IViewBuilding::action selectedAction = IViewBuilding::Undefined;

	//Detailled model view
	CScene m_sceneModels;
	CCamera m_CamModels;
	CViewport m_viewportModels;
	CBackground m_zmbackgroundModels;
	CPlacement m_zpModels;

	VModelWindmillPowerPlant modelWindmill;
	VModelSolarPowerPlant modelSolar;
	VModelNuclearPowerPlant modelNuclear;
	VModelOilRefinery modelOil;
	VModelPowerLine modelPowerline;
	VModelHydroelectricPowerPlant modelHydroelectric;
	std::unordered_map<VIdentifier::VIdentifier, IViewModel*> models;

	bool m_CooldownStrike=false;
	bool m_CooldownPowerLineCut = false;
	bool m_CooldownHalfResource = false;
};


NAMESPACE_VIEW_E
