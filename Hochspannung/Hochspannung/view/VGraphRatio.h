#pragma once
#include "IViewGUIObject.h"
#include "Bar.h"

NAMESPACE_VIEW_B
class VGraphRatio :
	public IViewGUIObject
{
public:
	VGraphRatio(CViewport* viewport, CFloatRect& rect, CMaterial* normalMaterial, bool bVertical = true);

	~VGraphRatio();


	void checkEvent(CDeviceCursor* cursor, CDeviceKeyboard* keyboard) override;
	void switchOn() override;
	void switchOff() override;
	void onMouseOver() override;
	void onMouseOut() override;
	void onMouseClickLeft() override;
	void onMouseClickRight() override;
	void setLayer(float layer) override;
	void updateRectangle(CFloatRect rect) override;

	void updateValue(float fRatio);
	void toggleType();
	void switchVertical();
	void switchHorizontal();

private:
	void recalcRectangles();
	CViewport* m_viewport;
	Bar* m_bar;
	bool m_bVertical;
};

NAMESPACE_VIEW_E