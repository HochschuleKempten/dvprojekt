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

	explicit VScreenCredits(VUI* vUi);
	~VScreenCredits();
	void onNotify(const Event& events) override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
	void checkSpecialEvent(CDeviceCursor* cursor) override;
	void tick(const float fTimeDelta) override;
	void checkGUIObjects(IViewGUIContainer* tempGuicontainer);
	void checkGUIContainer(IViewGUIContainer* tempGuicontainer);
	void resize(const int width, const int height) override;

	void MoveText();

private:
	CBackground* m_background;
	COverlay* overlay;
	COverlay* topBorder;
};

NAMESPACE_VIEW_E
