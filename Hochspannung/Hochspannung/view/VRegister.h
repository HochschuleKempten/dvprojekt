#pragma once
#include "IViewGUIContainer.h"

NAMESPACE_VIEW_B

class VRegister :
	public IViewGUIContainer
{
public:
	VRegister();
	VRegister(CFloatRect floatRect, CViewport* viewport, CMaterial* MaterialNormal);
	~VRegister();

	void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction) override;
	void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder) override;
	void addText(CFloatRect rect, CWritingFont* writingFont, string text)override;
	void onNotify(Event events) override;
	
	void switchOn() override;

	void switchOff() override;

private:
	CFloatRect m_rect;
	CViewport* m_viewport;
	COverlay* m_background;
};

NAMESPACE_VIEW_E
