#pragma once
#include "IViewScreen.h"
NAMESPACE_VIEW_B

class VScreenLobby :
	public IViewScreen
{
public:
	explicit VScreenLobby(VUI* vUI);
	~VScreenLobby();
	void onNotify(const Event& events) override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;
	void checkSpecialEvent(CDeviceCursor* cursor) override;
	void tick(const float fTimeDelta) override;
	void checkGUIObjects(IViewGUIContainer* tempGuicontainer);
	void checkGUIContainer(IViewGUIContainer* tempGuicontainer);
	void resize(const int width, const int height) override;
	void startAnimation() override;
	void StartEvent() override;
	void EndEvent() override;

	void updateHostList(const std::vector<Network::CGameObject>& hostList);

	void foundPlayer();
private:
	CBackground* m_background;
	COverlay* m_bigDialog;

	bool m_JoinReady = false;
	bool m_startReady = false;
};

NAMESPACE_VIEW_E
