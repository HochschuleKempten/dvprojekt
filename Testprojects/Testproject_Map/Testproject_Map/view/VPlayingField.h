#pragma once

#include "../logic/IVPlayingField.h"
#include "../logic/LPlayingField.h"
#include "../logic/Array2D.h"
#include "VMaster.h"
#include "IViewObject.h"

NAMESPACE_VIEW_B

class IViewBuilding;

class VPlayingField : public IVPlayingField, public IViewObject
{
private:
	Array2D<CGeoCube> m_zgField;
	Array2D<CPlacement> m_zpField;
	Array2D<IViewBuilding*> viewObjects;

public:
	VPlayingField(VMaster* vMaster, LPlayingField* playingField)
		: IVPlayingField(playingField), IViewObject(vMaster),
		  m_zgField(playingField->getFieldLength(), playingField->getFieldLength()),
		  m_zpField(playingField->getFieldLength(), playingField->getFieldLength()),
		  viewObjects(playingField->getFieldLength(), playingField->getFieldLength())
	{}
	virtual ~VPlayingField()
	{}

	void fieldClicked(const int x, const int y);

	void placeObject(IViewBuilding* viewObject, const int x, const int y);

	virtual void initPlayingField();
};


NAMESPACE_VIEW_E
