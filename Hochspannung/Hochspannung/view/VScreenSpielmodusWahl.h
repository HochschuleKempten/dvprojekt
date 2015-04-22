#pragma once
#include "IViewScreen.h"
NAMESPACE_VIEW_B

class VScreenSpielmodusWahl :
	public IViewScreen
{
public:
	VScreenSpielmodusWahl();
	VScreenSpielmodusWahl(CFrame* frame);
	~VScreenSpielmodusWahl();

	void onNotify(IViewUIObserver::Event events);
	void checkShortcut(CDeviceKeyboard* keyboard);
private:
	COverlay* m_flash;
	CBackground* m_background;
	COverlay* m_headline;
};

NAMESPACE_VIEW_E

