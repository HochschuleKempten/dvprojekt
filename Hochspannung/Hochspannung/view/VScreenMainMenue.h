#pragma once
#include "IViewScreen.h"

NAMESPACE_VIEW_B

class VScreenMainMenue :
	public IViewScreen
{
public:
	VScreenMainMenue();
	VScreenMainMenue(CFrame* frame);
	~VScreenMainMenue();

	void onNotify(Event events)override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
private:
	COverlay* m_flash;
	CBackground* m_background;
	COverlay* m_headline;
};

NAMESPACE_VIEW_E
