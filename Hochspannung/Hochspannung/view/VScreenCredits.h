#pragma once
#include "IViewScreen.h"
NAMESPACE_VIEW_B
class VScreenCredits :
	public IViewScreen
{
public:
	void startAnimation() override;
	void StartEvent() override;
	void EndEvent() override;
public:
	explicit VScreenCredits(VUI* vUi);
	~VScreenCredits();
	void onNotify(IViewUIObserver::Event events)override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
	void checkSpecialEvent(CDeviceCursor* cursor)override;
	void tick() override;
	void checkGUIObjects(IViewGUIContainer* tempGuicontainer);
	void checkGUIContainer(IViewGUIContainer* tempGuicontainer);
	void resize(int width, int height) override;
private:
	CBackground* m_background;
};
NAMESPACE_VIEW_E
