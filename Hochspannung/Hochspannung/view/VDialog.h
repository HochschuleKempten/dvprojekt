#pragma once
#include "IViewGUIContainer.h"
NAMESPACE_VIEW_B

class VDialog : public IViewGUIContainer
{
public:
	VDialog();
	VDialog(CFloatRect floatRect, CViewport* viewport, CMaterial* MaterialNormal);
	~VDialog();
	void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewUIObserver::Event clickAction);
	void onNotify(IViewUIObserver::Event);
	list<IViewGUIObject*> getGuiObjectList();
	virtual void switchOn();

	virtual void switchOff();
	
private:
	CFloatRect m_rect;
	CViewport* m_viewport;
	list<IViewGUIObject*> m_guiObjects;
	list<IViewGUIObject*>::iterator lIterGUIObjects;
	COverlay* m_background;
};

NAMESPACE_VIEW_E