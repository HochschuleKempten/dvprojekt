#ifndef _VUIHELPER_H_
#define _VIUHELPER_H_
#include "VGeneral.h"


NAMESPACE_VIEW_B
#define CREATE_RELATIVE_RECT(RectSource,RectWantRelative) createRelativeRectangle(RectSource,RectWantRelative)


inline CFloatRect createRelativeRectangle(CFloatRect* RelativeToRect, CFloatRect* RelativeRect)
{
	return CFloatRect(RelativeToRect->GetXPos() + (RelativeToRect->GetXSize() * RelativeRect->GetXPos()), RelativeToRect->GetYPos() + (RelativeToRect->GetYSize() * RelativeRect->GetYPos()),
	                  RelativeToRect->GetXSize() * RelativeRect->GetXSize(), RelativeToRect->GetYSize() * RelativeRect->GetYSize());
}



NAMESPACE_VIEW_E

#endif _VIUHELPER_H_
