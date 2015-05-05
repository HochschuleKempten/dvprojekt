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
	void checkGUIContainer(IViewGUIContainer* tempGuicontainer);
	void resize(int width, int height) override;
	void tick() override;
	void checkGUIObjects(IViewGUIContainer* tempGuicontainer);
	void startAnimation() override;
	 void slideIn();

	 void StartEvent() override;
	 void EndEvent() override;

private:
	COverlay* m_flash;
	CBackground* m_background;
	COverlay* m_headline;
	bool startUp = true;
};

NAMESPACE_VIEW_E
