#pragma once
#include "IViewScreen.h"
#include <mutex>
NAMESPACE_VIEW_B

class VScreenLobby :
	public IViewScreen
{
public:
	explicit VScreenLobby(VUI* vUI);
	~VScreenLobby();
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

	void updateHostList(const std::unordered_map<std::string, Network::CGameObject>& hostList);

	void foundPlayer();

	void showWaitingDialog();
private:
	bool checkAddress(const std::string& address);
	COverlay* m_bigDialog;
	std::mutex mutex;
	bool m_startReady = false;
};

NAMESPACE_VIEW_E
