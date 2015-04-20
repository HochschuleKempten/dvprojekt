#pragma once
#include "IViewGUIContainer.h"
NAMESPACE_VIEW_B

class VDialog : public IViewGUIContainer
{
public:
	VDialog();
	VDialog(CFloatRect floatRect, CViewport* viewport, CMaterial* MaterialNormal);
	~VDialog();
	void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewUIObserver::Event clickAction) override;
	void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder) override;
	void addText(CFloatRect rect, CWritingFont* writingFont, string text)override;
	void onNotify(Event events) override;
	vector<IViewGUIObject*> getGuiObjectList() override;
	void switchOn() override;

	void switchOff() override;
	
private:
	CFloatRect m_rect;
	CViewport* m_viewport;
	//list<IViewGUIObject*> m_guiObjects;
	//list<IViewGUIObject*>::iterator lIterGUIObjects;
	COverlay* m_background;
};

NAMESPACE_VIEW_E