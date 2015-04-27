#pragma once
#include "IViewScreen.h"

NAMESPACE_VIEW_B
class VScreenOptions :
	public IViewScreen
{
public:
	VScreenOptions();
	VScreenOptions(CFrame* frame);
	~VScreenOptions();
	void onNotify(IViewUIObserver::Event events)override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
	void checkSpecialEvent(CDeviceCursor* cursor)override;
private:
	CBackground* m_background;
};
NAMESPACE_VIEW_E
