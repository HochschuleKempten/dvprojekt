#pragma once
#include "IViewScreen.h"
NAMESPACE_VIEW_B
class VScreenIngame :
	public IViewScreen
{
public:
	
	VScreenIngame(CFrame* frame, CRoot* root, CScene* scene, CPlacement* camplacement);
	VScreenIngame(CViewport* viewp,CFrame* frame);
	VScreenIngame();
	~VScreenIngame();
	void onNotify(IViewUIObserver::Event events);
	void VScreenIngame::switchOn();
	void VScreenIngame::switchOff();
	void checkShortcut(CDeviceKeyboard* keyboard);
private:
	CCamera m_zc;
	CPlacement* m_zpCamera;
	CScene* m_scene;
	CParallelLight m_zl;
	CBackground m_zb;
	CRoot m_zr;

	COverlay m_bottomBar;
	COverlay m_topBar;
	CCamera m_miniMap;
	CViewport m_minimap;

	bool bK = false;
};

NAMESPACE_VIEW_E