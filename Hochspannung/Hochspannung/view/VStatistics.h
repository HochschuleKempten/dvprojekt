#pragma once
#include "IViewGUIObject.h"
#include "VGraph.h"
#include "VGraphRatio.h"
#include "VText.h";

NAMESPACE_VIEW_B

class VStatistics : public IViewGUIObject
{
public:
	VStatistics(CViewport* viewport, CFloatRect& rect, CMaterial* backgroundMaterial, const float layer);
	~VStatistics();

	void checkEvent(CDeviceCursor* cursor, CDeviceKeyboard* keyboard) override;
	void switchOn() override;
	void switchOff() override;
	void onMouseOver() override;
	void onMouseOut() override;
	void onMouseClickLeft() override;
	void onMouseClickRight() override;
	void setLayer(float layer) override;
	void updateRectangle(CFloatRect rect) override;

	void slideToggle();
	void slideIn();
	void slideOut();

	void addText(const std::string& text);

private:
	CViewport* m_viewport;
	COverlay* m_background;
	COverlay* m_text;
	bool m_hasBackground;
	bool m_hasText;
	bool m_bShown;
	std::vector<VText*> m_texts;
};

NAMESPACE_VIEW_E