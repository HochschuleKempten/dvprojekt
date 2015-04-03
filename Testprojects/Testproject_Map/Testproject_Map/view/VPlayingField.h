#pragma once

#include "../logic/IVPlayingField.h"
#include "../logic/LPlayingField.h"
#include "../logic/Array2D.h"
#include "VMaster.h"
#include "IViewObject.h"

NAMESPACE_VIEW_B


class IViewBuilding;

class VPlayingField : public IViewObject, public IVPlayingField
{
private:
	CPlacement m_zp;
	CMaterial m_zm;
	const int fieldSize = 2;
	//TODO (V) Neue Struktur der Placements
	//TODO (V) Sicht auf das Spielfeld anpassen
	Array2D<CGeoCube> m_zgField;
	Array2D<CPlacement> m_zpField;
	Array2D<IViewBuilding*> viewObjects;
	Array2D<CMaterial> m_zmMaterials;

public:
	VPlayingField(VMaster* vMaster, LPlayingField* lPlayingField)
		: IViewObject(vMaster, &m_zp), IVPlayingField(lPlayingField),
		  m_zgField(lPlayingField->getFieldLength(), lPlayingField->getFieldLength()),
		  m_zpField(lPlayingField->getFieldLength(), lPlayingField->getFieldLength()),
		  viewObjects(lPlayingField->getFieldLength(), lPlayingField->getFieldLength()),
		  m_zmMaterials(lPlayingField->getFieldLength(), lPlayingField->getFieldLength())
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
