#pragma once

#include "IViewGUIObject.h"
//---------------------------------------------------
// CPEmitter: Button Klasse für GUI
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------
NAMESPACE_VIEW_B

class VButton:public IViewGUIObject{
					
public:
	
	VButton();
	VButton(CViewport* viewport,CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewUIObserver::Event clickAction);
	~VButton();
	
	
	void checkHover(const float& fPosX, const float& fPosY);
	void checkPressed(const float& fPosX, const float& fPosY, const bool& bLeftpressed);
	
	

	void onMouseOver(void);
	void onMouseOut(void);
	void onMouseClickLeft(void);
	void onMouseClickRight(void);

	

	bool bGetHasHover();

	void switchOn();
	void switchOff();
	
	//Getter

	COverlay* getHoverOverlay();
	COverlay *getNormalOverlay();
	
	CFloatRect getRectangle();
	
	
	//ClickAction getAction();

private:

	COverlay* m_zoNormal;
	COverlay* m_zoHover;
	
	CFloatRect m_zfrRect; 
	
	bool m_bHasHover;

	IViewUIObserver::Event action;
	



	
};

NAMESPACE_VIEW_E