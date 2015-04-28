#pragma once
#include "IViewGUIContainer.h"
#include "VTab.h"

NAMESPACE_VIEW_B

class VRegister :
	public IViewGUIContainer
{
public:
	VRegister();
	VRegister(CFloatRect floatRect, CViewport* viewport);
	VRegister(CFloatRect floatRect, CViewport* viewport, CMaterial* materialBackground);
	~VRegister();

	void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction,string sName) override;
	void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder, string sName) override;
	void addText(CFloatRect rect, CWritingFont* writingFont, string text, string sName)override;
	void onNotify(Event events) override;
	void addContainer(const IViewGUIContainer::ContainerType& containerType, CFloatRect& floatRect,CMaterial* MaterialNormal, const string& sName) override;
	void addContainer(const IViewGUIContainer::ContainerType& containerType, CFloatRect& floatRect, const string& sName)override;
	void switchOn() override;

	void switchOff() override;
	void addTab(CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* background, Event events, string sName);
	void calcButtonSize();
	void SwitchToTab(string sName);
	VTab* getTab(string sName);
private:
	map<string, VTab*> m_tabs;
	

};

NAMESPACE_VIEW_E
