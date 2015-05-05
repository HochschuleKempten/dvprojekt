#pragma once
#include "IViewGUIObject.h"
#include "Bar.h"

NAMESPACE_VIEW_B
class VGraph :
	public IViewGUIObject
{
public:
	VGraph(CViewport* viewport, CFloatRect& rect);

	~VGraph();


	void checkEvent(CDeviceCursor* cursor, CDeviceKeyboard* keyboard) override;
	void switchOn() override;
	void switchOff() override;
	void onMouseOver() override;
	void onMouseOut() override;
	void onMouseClickLeft() override;
	void onMouseClickRight() override;
	void setLayer(float layer) override;
	void updateRectangle(CFloatRect rect) override;

	void addBar(string sName,CMaterial* normalMaterial);
	void updateBar(string sName, float wert);
private:
	CFloatRect createRelativeRectangle(CFloatRect* RelativeToRect, CFloatRect* RelativeRect);
	void calcWidth();
	void calcHeight();
	float getMaxHeight();
	CViewport* m_viewport;
	map<string, Bar*> m_bars;
	map<string, Bar*>::iterator m_IterBars;
};

NAMESPACE_VIEW_E