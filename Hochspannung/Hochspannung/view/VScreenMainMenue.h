#pragma once
#include "IViewScreen.h"

NAMESPACE_VIEW_B

class VScreenMainMenue :
	public IViewScreen
{

	
public:
	explicit VScreenMainMenue(VUI* vUi);
	~VScreenMainMenue();

	void onNotify(Event events)override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
	void checkSpecialEvent(CDeviceCursor* cursor)override;
	void resize(int width, int height) override;
	void tick() override;
private:
	COverlay* m_flash;
	CBackground* m_background;
	COverlay* m_headline;
};

NAMESPACE_VIEW_E
