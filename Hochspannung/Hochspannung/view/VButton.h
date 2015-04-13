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
	
	
	void checkHover(float fPosX, float fPosY);
	void checkPressed(float fCursorPosX, float fCursorPosY, bool bLeftpressed);
	
	

	void onMouseOver(void);
	void onMouseOut(void);
	void onMouseClickLeft(void);
	void onMouseClickRight(void);

	

	bool bGetHasHover();

	
	
	//Getter

	COverlay* getHoverOverlay();
	COverlay *getNormalOverlay();
	
	CFloatRect getRectangle();
	
	
	//ClickAction getAction();

private:

	COverlay* m_zoNormal;
	COverlay* m_zoHover;
	
	CFloatRect m_zfrRect; 
	string m_slabel;
	
	bool m_bHasHover;

	IViewUIObserver::Event action;
	



	
};

NAMESPACE_VIEW_E