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
	virtual void checkHover(const float& fPosX, const float& fPosY)=0;
	virtual void checkPressed(const float& fPosX, const float& fPosY, const bool& bLeftpressed) = 0;
	virtual void switchOn()=0;
	virtual void switchOff() = 0;
};
NAMESPACE_VIEW_E
