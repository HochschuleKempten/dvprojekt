#pragma once

#include "IViewScreen.h"
#include "VIdentifier.h"
#include "VModelWindmillPowerPlant.h"
#include "VModelSolarPowerplant.h"
#include "VModelNuclearPowerPlant.h"
#include "VModelOilRefinery.h"
#include "VModelPowerLine.h"
#include "VModelHydroelectricPowerPlant.h"
#include "VContextInfo.h"
#include "VModelCoalPowerPlant.h"

NAMESPACE_VIEW_B


class VScreenIngame : public IViewScreen
{
	friend class VContextInfo;

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

	enum INFOTYPE
	{
		CRAFTBUILDING,
		FIELDINFO,
		SABOTAGEINFO,
		NOINFO
	};


	explicit VScreenIngame(VUI* vUi);
	virtual ~VScreenIngame();
	void onNotify(const Event& events) override;
	void switchOn() override;
	void switchOff() override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
	void checkSpecialEvent() override;

	//Schnittstellenmethoden
	void updateMoney(const int wert, const LPlayer::PlayerId playerId);
	void updatePopulation(const int wert);
	void updateAddedPowerPlant(const LIdentifier::LIdentifier id, const LPlayer::PlayerId playerId);
	void updateRemovedPowerPlant(const LIdentifier::LIdentifier id, const LPlayer::PlayerId playerId);
	void updateNumberPowerLines(const int newNumberPowerLines, const LPlayer::PlayerId playerId);
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
	void stopCooldown(const INTERACTIONS interaction);
	void startCooldown(const INTERACTIONS interaction);

	void setSabotageNumber(const int value);


	void updateFieldStorageValue(std::pair<int, int> pos, const std::string& name, const std::string& wert);

	void switchInfo(INFOTYPE);

	void updateSabotageCost(LSabotage::LSabotage sabotageType, const int value);

private:

	void handleInput(const float fTimeDelta);
	std::map<int, std::vector<int>> pickElements();

	CFloatRect getRectForPixel(const int iPosX, const int iPosY, const int iSizeX, const int iSizeY);
	void handleLeftClick(const std::map<int, std::vector<int>>& pickedElements);

	bool tryBuilding(const int x, const int y);
	bool trySabotage(const int x, const int y);
	bool tryBuildingInteraction(const int x, const int y);

	int getNumberofBuildings(const LPlayer::PlayerId playerId);

	void updateModelView();

	void SabotageTabSwitchOn();

	void SabotageTabSwitchOff();


	VButton* activeButton = nullptr;

	IViewGUIContainer* activeInfo = nullptr;

	CScene m_scene;
	CCamera m_zc;
	CPlacement m_zpCamera;


	VRegister* vrRegister = nullptr;

	//Lightning
	CParallelLight m_zl;
	CSpotLight m_zlSpot;
	CPlacement m_zpSpot;
	CHVector m_PointingSpot;

	IViewGUIContainer* m_vtTopbar = nullptr;
	VTab* m_vtTabStatistics = nullptr;
	VTab* m_vtTabSabotage = nullptr;
	VTab* m_vtTabBuilding = nullptr;


	VGraph *m_vgGraphEnergy = nullptr;
	VGraphRatio *m_vgGraphEnergyRatioOwn = nullptr;
	VGraphRatio *m_vgGraphEnergyRatioEnemy = nullptr;


	//bool bK = false;
	float cameraZoomPosition = 0.0f;
	float cameraMovementPositionLeftRight = 0.0f;
	float cameraMovementPositionBackForward= 0.0f;
	float cameraFlipPosition = 0;


	VIdentifier::VIdentifier selectedBuilding = VIdentifier::Undefined;
	bool clickActive = false;
	std::pair<int, int> lastClickPosition = std::make_pair(0, 0);

	std::map<BUILDINGTYPE, int> statPlacedBuildingsOwn;
	std::map<BUILDINGTYPE, int> statPlacedBuildingsEnemy;
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
	VModelCoalPowerPlant modelCoal;
	std::unordered_map<VIdentifier::VIdentifier, IViewModel*> models;

	std::unordered_map<std::pair<int, int>, VContextInfo,LPlayingFieldHasher> m_fieldValueStorage;

	bool m_CooldownPowerLineCut = false;
	bool m_CooldownStrike = false;
	bool m_CooldownHalfResource = false;
	float cooldownRemove = 0.0f;
	float cooldownDeactivate = 0.0f;
	float cooldownResource = 0.0f;

	int m_RemoveCost = 0;
	int m_ResourceCost = 0;
	int m_DeactivateCost = 0;
};


NAMESPACE_VIEW_E
