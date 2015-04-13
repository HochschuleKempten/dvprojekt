#pragma once
//TODO (pb)
#include "IViewUIObserver.h"
#include "IViewSubject.h"


//---------------------------------------------------
// IGUIObjekt Interface
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------
NAMESPACE_VIEW_B

class IViewGUIObject:public IViewSubject
{
public:
	virtual ~IViewGUIObject(){};
	virtual void checkHover(float fPosX, float fPosY)=0;
	virtual void checkPressed(float fPoxX, float fPoxY, bool bLeftpressed) = 0;
	
};
NAMESPACE_VIEW_E
