#pragma once
#include "IViewScreen.h"
NAMESPACE_VIEW_B
class VScreenLobby :
	public IViewScreen
{
public:
	VScreenLobby();
	VScreenLobby(CFrame* frame);
	~VScreenLobby();
	void onNotify(Event events)override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
	void checkSpecialEvent(CDeviceCursor* cursor)override;
private:
	CBackground* m_background;
	COverlay* m_bigDialog;

};

NAMESPACE_VIEW_E