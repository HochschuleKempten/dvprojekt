#pragma once

#include "IViewGUIObject.h"
//---------------------------------------------------
// CPEmitter: Button Klasse für GUI
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------
NAMESPACE_VIEW_B

class VButton:public IViewGUIObject
{
public:

	VButton();
	VButton(CViewport* viewport, CFloatRect& rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewUIObserver::Event clickAction, const float layer);
	VButton(CViewport* viewport, CFloatRect& rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, IViewUIObserver::Event clickAction, const float layer);
	~VButton();


	virtual void switchOn() override final;
	virtual void switchOff() override final;

	virtual void onMouseOver(void) override final;
	virtual void onMouseOut(void) override final;
	virtual void onMouseClickLeft(void) override final;
	virtual void onMouseClickRight(void) override final;

	virtual void setLayer(const float layer) override;
	virtual void updateRectangle(CFloatRect rect) override;
	bool bGetHasHover();


	//Getter
	COverlay* getActiveOverlay();
	COverlay* getHoverOverlay();
	COverlay* getNormalOverlay();

	CFloatRect getRectangle() override;


	//ClickAction getAction();

	void setActive(bool value = true);

private:

	COverlay* m_zoNormal = nullptr;
	COverlay* m_zoHover = nullptr;
	COverlay* m_zoActive = nullptr;

	bool m_bHasHover;
	bool m_isActive = false;
	bool isActive();

	IViewUIObserver::Event action = IViewUIObserver::Event::NOTHING;
};

NAMESPACE_VIEW_E
