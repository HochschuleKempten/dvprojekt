#pragma once
#include "IViewGUIObject.h"
#include "VText.h"

NAMESPACE_VIEW_B

class VListEntry :
	public IViewGUIObject
{
public:
	
	VListEntry();
	VListEntry(CViewport* viewport,CMaterial* MaterialNormal, CMaterial* MaterialHover, const std::string& sName);

	~VListEntry();
	
	void switchOn() override;
	void switchOff() override;
	void onMouseOver() override;
	void onMouseOut() override;
	void onMouseClickLeft() override;
	void onMouseClickRight() override;
	void setLayer(const float layer) override;
	void updateRectangle(CFloatRect rect) override;


	void checkEvent(CDeviceCursor* cursor, CDeviceKeyboard* keyboard) override;
	bool bGetHasHover();

	bool isActive();

	//Getter

	COverlay* getHoverOverlay();
	COverlay* getNormalOverlay();

	CFloatRect getRectangle() override;


	//ClickAction getAction();

private:


	COverlay* m_zoNormal;
	COverlay* m_zoActive;
	COverlay* m_zoHover;

	CWriting* iwas;

	bool m_bHasHover;

	CViewport* m_viewport;

	//CWriting* m_writing;

	//VText* m_text;

	bool m_bIsActive = false;

	void setActive(bool wert);

	CFloatRect createRelativeRectangle(CFloatRect* RelativeToRect, CFloatRect* RelativeRect);
};

NAMESPACE_VIEW_E
