#pragma once
#include "IViewScreen.h"
NAMESPACE_VIEW_B
class VScreenIngame :
	public IViewScreen
{
public:
	explicit VScreenIngame(VUI* vUi);
	virtual ~VScreenIngame();
	void onNotify(Event events) override;
	void switchOn() override;
	void switchOff() override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
	void checkSpecialEvent(CDeviceCursor* cursor)override;
//	void resize(int width, int height)override;

	//Schnittstellenmethoden
	void updateMoney(const int wert);
	
	void updatePopulation(const int wert);

	void updateInfofeld(string& neuerText);

	CFloatRect getTopSpace();
	
	CFloatRect getBottomSpace();

	void tick() override;
	void resize(int width, int height) override;

	void handleInput(float fTimeDelta);
	std::map<int, std::vector<int>> pickElements();
	
private:
	CCamera m_zc;
	CPlacement m_zpCamera;
	CScene m_scene;
	CParallelLight m_zl;
	CBackground m_zb;

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

	VIdentifier::VIdentifier m_selectedBuilding;
};

NAMESPACE_VIEW_E