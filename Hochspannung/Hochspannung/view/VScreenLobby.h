#pragma once
#include "IViewScreen.h"
NAMESPACE_VIEW_B
class VScreenLobby :
	public IViewScreen
{

	
public:
	VScreenLobby(VUI* vUI);
	~VScreenLobby();
	void onNotify(Event events)override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
	void checkSpecialEvent(CDeviceCursor* cursor)override;
	void tick() override;
	void resize(int width, int height) override;
private:
	CBackground* m_background;
	COverlay* m_bigDialog;

};

NAMESPACE_VIEW_E