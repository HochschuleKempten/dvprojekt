#pragma once
#include "IViewScreen.h"
NAMESPACE_VIEW_B

	class VScreenLobby :
		public IViewScreen
	{
	public:
		explicit VScreenLobby(VUI* vUI);
		~VScreenLobby();
		void onNotify(Event events) override;
		void checkShortcut(CDeviceKeyboard* keyboard) override;
		void checkSpecialEvent(CDeviceCursor* cursor) override;
		void tick(const float fTimeDelta) override;
		void checkGUIObjects(IViewGUIContainer* tempGuicontainer);
		void checkGUIContainer(IViewGUIContainer* tempGuicontainer);
		void resize(int width, int height) override;
		void startAnimation() override;
		void StartEvent() override;
		void EndEvent() override;

		void updateHostList(const std::vector<Network::CGameObject>& hostList);
	private:
		CBackground* m_background;
		COverlay* m_bigDialog;
	};

	NAMESPACE_VIEW_E
