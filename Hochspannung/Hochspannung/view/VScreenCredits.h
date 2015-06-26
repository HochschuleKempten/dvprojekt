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
	void checkSpecialEvent() override;
	void tick(const float fTimeDelta) override;
	void checkGUIObjects(IViewGUIContainer* tempGuicontainer);
	void checkGUIContainer(IViewGUIContainer* tempGuicontainer);
	void resize(const int width, const int height) override;

	void MoveText(COverlay* overlay);

private:

	bool animationReady = false;
	bool animationStop = false;

	CFloatRect rect;

	CBackground* m_background;
	COverlay* overlay;
	COverlay* topBorder;
	COverlay* bottomBorder;

	VText* escapeText;

	bool firststart = true;

	//Credits
	COverlay* materialCredits;
	/*COverlay* materialCreditsOrganization;
	COverlay* materialCreditsIntegration;
	COverlay* materialCreditsTextures;
	COverlay* materialCreditsNetwork;
	COverlay* materialCreditsLogic;
	COverlay* materialCreditsUI;
	COverlay* materialCreditsModelling;
	COverlay* materialCreditsModelling2;
	COverlay* materialCreditsVektoriaSplash;*/


	CFloatRect getRectForPixel(const int iPosX, const int iPosY, const int iSizeX, const int iSizeY);
	
};

NAMESPACE_VIEW_E
