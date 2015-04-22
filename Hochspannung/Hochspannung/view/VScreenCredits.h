#pragma once
#include "IViewScreen.h"
NAMESPACE_VIEW_B
class VScreenCredits :
	public IViewScreen
{
public:
	VScreenCredits();
	VScreenCredits(CFrame* frame);
	~VScreenCredits();
	void onNotify(IViewUIObserver::Event events)override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
	
private:
	CBackground* m_background;
};
NAMESPACE_VIEW_E
