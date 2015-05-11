#pragma once
#include "IViewGUIObject.h"

NAMESPACE_VIEW_B

class Bar:public IViewGUIObject
{
public:
	Bar(CViewport* viewport, CMaterial *material, CFloatRect rect, float value);
	~Bar();

	void switchOn() override;
	void switchOff() override;
	void onMouseOver() override;
	void onMouseOut() override;
	void onMouseClickLeft() override;


	COverlay* get_mp_zo_surface() const
	{
		return mp_zoSurface;
	}

	void set_mp_zo_surface(COverlay* mp_zo_surface)
	{
		mp_zoSurface = mp_zo_surface;
	}

	float get_m_f_value() const
	{
		return m_fValue;
	}

	void set_m_f_value(float m_f_value)
	{
		m_fValue = m_f_value;
	}

	void onMouseClickRight() override;
	void setLayer(float layer) override;
	void updateRectangle(CFloatRect rect) override;

private:
	COverlay* mp_zoSurface = nullptr;
	float m_fValue = 0;
	
		
};

NAMESPACE_VIEW_E
