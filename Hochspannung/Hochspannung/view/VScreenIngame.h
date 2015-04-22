#pragma once
#include "IViewScreen.h"
NAMESPACE_VIEW_B
class VScreenIngame :
	public IViewScreen
{
public:
	
	VScreenIngame(CFrame* frame, CRoot* root, CScene* scene, CPlacement* camplacement);
	
	VScreenIngame();
	~VScreenIngame();
	void onNotify(Event events) override;
	void switchOn() override;
	void switchOff() override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
//	void resize(int width, int height)override;

	//Schnittstellenmethoden
	void updateMoney(const int wert);
	
	void updatePopulation(const int wert);

	
private:
	CCamera m_zc;
	CPlacement* m_zpCamera;
	CScene* m_scene;
	CParallelLight m_zl;
	CBackground m_zb;
	CRoot m_zr;

	COverlay m_bottomBar;
	COverlay m_topBar;
	COverlay m_bottomBarBorderTop;
	COverlay m_bottomBarBorderBottom;
	COverlay m_bottomBarBorderLeft;
	COverlay m_bottomBarBorderRight;
	COverlay m_bottomBarSeperatorMenueInfofeld;
	COverlay m_bottomBarSeperatorMenueMinimap;

	CCamera m_CamMiniMap;
	CViewport m_minimap;
	CPlacement m_zpMinimapCam;

	bool bK = false;
};

NAMESPACE_VIEW_E