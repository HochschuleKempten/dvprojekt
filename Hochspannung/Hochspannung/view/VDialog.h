#pragma once
#include "IViewGUIContainer.h"
NAMESPACE_VIEW_B

class VDialog : public IViewGUIContainer
{
public:
	VDialog();
	VDialog(CViewport* viewport,CFloatRect floatRect, CMaterial* MaterialNormal);
	VDialog(CViewport* viewport, CFloatRect floatRect);
	~VDialog();
	void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, string sName) override;
	void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder, string sName) override;
	void addText(CFloatRect rect, CWritingFont* writingFont, string text, string sName)override;
	void addOverlay(CFloatRect rect, CMaterial* MaterialNormal, bool bChromaKeying, string sName) override;
	

	void onNotify(Event events) override;
	
	void switchOn() override;

	void switchOff() override;
	
	void addContainer(const IViewGUIContainer::ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const string& sName) override;
	void addContainer(const IViewGUIContainer::ContainerType& containerType, CFloatRect& floatRect, const string& sName)override;
private:
	
	//list<IViewGUIObject*> m_guiObjects;
	//list<IViewGUIObject*>::iterator lIterGUIObjects;
	COverlay* m_background;
};

NAMESPACE_VIEW_E