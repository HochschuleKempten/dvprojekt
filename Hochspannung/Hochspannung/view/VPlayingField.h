#pragma once

#include "../logic/IVPlayingField.h"
#include "../logic/LPlayingField.h"
#include "../logic/Array2D.h"
#include "VMaster.h"
#include "IViewObject.h"
#include "../logic/IDGenerator.h"
#include <vector>
#include <memory>


NAMESPACE_VIEW_B


class IViewBuilding;

class VPlayingField : public IViewObject, public IVPlayingField
{
private:
	CPlacement m_zp;
	CMaterial m_zm;
	const int fieldSize = 2;
	//TODO (V) Neue Struktur der Placements
	std::vector<CPlacement> m_zpPlacementHolders;	
	Array2D<CGeoCube> m_zgField;
	Array2D<CPlacement> m_zpField;
	Array2D<shared_ptr<IViewBuilding>> viewObjects;
	Array2D<CMaterial> m_zmMaterials;

public:
	VPlayingField(VMaster* vMaster, LPlayingField* lPlayingField)
		: IViewObject(vMaster, &m_zp), IVPlayingField(lPlayingField),
		m_zpPlacementHolders(lPlayingField->getFieldLength()*lPlayingField->getFieldLength() / 25),
		  m_zgField(lPlayingField->getFieldLength(), lPlayingField->getFieldLength()),
		  m_zpField(lPlayingField->getFieldLength(), lPlayingField->getFieldLength()),
		  viewObjects(lPlayingField->getFieldLength(), lPlayingField->getFieldLength()),
		  m_zmMaterials(lPlayingField->getFieldLength(), lPlayingField->getFieldLength())
		  
	{}
	virtual ~VPlayingField()
	{}

	//TODO (V) remove building again
	template<typename T>
	inline void tryBuildOnField(const int x, const int y)
	{
		//todo (V) check return value from "placeBuilding"
		this->lPlayingField->placeBuilding<T>(x, y);
	}

	inline void tryRemoveObject(const int x, const int y)
	{
		lPlayingField->removeBuilding(x, y);
	}

	void placeObject(const std::shared_ptr<IViewBuilding>& objPtr, const int x, const int y);

	virtual void initPlayingField();

	virtual void objectRemoved(const int x, const int y);


	static const int id = __COUNTER__;
};


NAMESPACE_VIEW_E
