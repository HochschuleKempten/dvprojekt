#pragma once

#include "VMaster.h"
#include "../logic/IVPlayingField.h"
#include "../logic/LPlayingField.h"
#include "../logic/Array2D.h"
#include "IViewObject.h"

NAMESPACE_VIEW_B

//TODO(MB) IVKraftwerk und VKraftwerk anlegen
//TODO(MB) Methoden zur Verfügung stellen, sodass sich das Kraftwerk beim VPlayingField einklinken kann


class VPlayingField : public IVPlayingField, public IViewObject
{
private:
	Array2D<CGeoCube> m_zgField;
	Array2D<CPlacement> m_zpField;

public:
	VPlayingField(VMaster* vMaster, LPlayingField* playingField)
		: IVPlayingField(playingField), IViewObject(vMaster),
		  m_zgField(playingField->getFieldLength(), playingField->getFieldLength()),
		  m_zpField(playingField->getFieldLength(), playingField->getFieldLength())
	{}

	void fieldClicked(const int i, const int j);

	void placeObject(int i, int j);

	virtual ~VPlayingField()
	{}
	
	virtual void initPlayingField();
};


NAMESPACE_VIEW_E
