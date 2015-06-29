#pragma once
#include "IViewScreen.h"

NAMESPACE_VIEW_B

class VScreenOptions :
	public IViewScreen
{
public:

	explicit VScreenOptions(VUI* vUi);
	~VScreenOptions();
	void onNotify(const Event& events) override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
	void checkSpecialEvent() override;

	void tick(const float fTimeDelta) override;
	void checkGUIObjects(IViewGUIContainer* tempGuicontainer);
	void checkGUIContainer(IViewGUIContainer* tempGuicontainer);
	void resize(const int width, const int height) override;


	void startAnimation() override;
	void StartEvent() override;
	void EndEvent() override;
private:
	COverlay* m_backgroundOverlay;
};

NAMESPACE_VIEW_E
