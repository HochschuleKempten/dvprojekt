#pragma once

#include "../logic/IVPlayingField.h"
#include "../logic/LPlayingField.h"
#include "../logic/Array2D.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


class IViewBuilding;

class VPlayingField : public IVPlayingField, public IViewObject
{
private:
	const int fieldSize = 2;
	Array2D<CGeoCube> m_zgField;
	Array2D<CPlacement> m_zpField;
	Array2D<IViewBuilding*> viewObjects;

public:
	VPlayingField(VMaster* vMaster, LPlayingField* lPlayingField)
		: IVPlayingField(lPlayingField), IViewObject(vMaster),
		  m_zgField(lPlayingField->getFieldLength(), lPlayingField->getFieldLength()),
		  m_zpField(lPlayingField->getFieldLength(), lPlayingField->getFieldLength()),
		  viewObjects(lPlayingField->getFieldLength(), lPlayingField->getFieldLength())
	{}
	virtual ~VPlayingField()
	{}

	template<typename T>
	void tryBuildOnField(const int x, const int y)
	{
		this->lPlayingField->placeBuilding<T>(x, y);
	}

	void placeObject(IViewBuilding* viewObject, const int x, const int y);

	virtual void initPlayingField();
};


NAMESPACE_VIEW_E
