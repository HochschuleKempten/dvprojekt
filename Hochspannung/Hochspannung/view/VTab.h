#pragma once
#include "IViewGUIContainer.h"
NAMESPACE_VIEW_B

class VTab :
	public IViewGUIContainer
{
public:
	VTab(CViewport* viewport,CFloatRect rect, CMaterial* materialBackground);
	~VTab();

	void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, string sName) override;
	void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder, string sName) override;
	void addText(CFloatRect rect, CWritingFont* writingFont, string text, string sName)override;
	void onNotify(Event events) override;
	void addContainer(const IViewGUIContainer::ContainerType& containerType, const CFloatRect& floatRect, const string& sName) override;
	void switchOn() override;

	void switchOff() override;

private:
	COverlay* m_background;

};

NAMESPACE_VIEW_E
