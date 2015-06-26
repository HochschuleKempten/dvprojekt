#pragma once
#include "IViewScreen.h"

NAMESPACE_VIEW_B

class VScreenMainMenue :
	public IViewScreen
{
public:
	explicit VScreenMainMenue(VUI* vUi);
	~VScreenMainMenue();

	void onNotify(const Event& events) override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
	void checkSpecialEvent() override;
	void checkGUIContainer(IViewGUIContainer* tempGuicontainer);
	void resize(const int width, const int height) override;
	void tick(const float fTimeDelta) override;
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
