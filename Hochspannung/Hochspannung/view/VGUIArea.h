#pragma once
#include "IViewGUIContainer.h"

NAMESPACE_VIEW_B

class VGUIArea :
	public IViewGUIContainer
{
public:
	VGUIArea();

	VGUIArea(CViewport* viewport, CFloatRect floatRect);
	VGUIArea(CViewport* viewport, CFloatRect floatRect,CMaterial* materialbackground);

	~VGUIArea();

	void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, string sName) override;
	void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder, string sName) override;
	void addText(CFloatRect rect, CWritingFont* writingFont, string text, string sName)override;
	void onNotify(Event events) override;

	void setLayer(float layer) override;

	void switchOn() override;

	void switchOff() override;

	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const string& sName) override;
	void addContainer(const IViewGUIContainer::ContainerType& containerType, CFloatRect& floatRect, const string& sName)override;
};

NAMESPACE_VIEW_E