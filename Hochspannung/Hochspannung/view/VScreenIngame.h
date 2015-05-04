#pragma once
#include "IViewScreen.h"
#include "VIdentifier.h"

NAMESPACE_VIEW_B


class VScreenIngame : public IViewScreen
{
public:
	explicit VScreenIngame(VUI* vUi);
	virtual ~VScreenIngame();
	void onNotify(Event events) override;
	void switchOn() override;
	void switchOff() override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
	void checkSpecialEvent(CDeviceCursor* cursor) override;

	//Schnittstellenmethoden
	void updateMoney(const int wert);

	void updatePopulation(const int wert);

	void updateInfofield(const string& neuerText);

	CFloatRect getTopSpace();

	CFloatRect getBottomSpace();

	void tick() override;
	void resize(int width, int height) override;

	void handleInput();
	std::map<int, std::vector<int>> pickElements();

	void addToScene(CPlacement* placement);

private:
	CScene m_scene;
	CViewport m_viewport;
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

	CCamera m_CamMiniMap;
	CViewport m_minimap;
	CPlacement m_zpMinimapCam;

	bool bK = false;
	float mouseWheelPosition = 0.0F;
	float cameraAngle = 0.0F;

	VIdentifier::VIdentifier m_selectedBuilding = VIdentifier::Undefined;
};


NAMESPACE_VIEW_E
