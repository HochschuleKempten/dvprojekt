#pragma once

#include "../logic/IVPlayingField.h"
#include "../logic/LPlayingField.h"
#include "../logic/Array2D.h"
#include "VMaster.h"
#include "IViewObject.h"
#include <vector>
#include <memory>

NAMESPACE_VIEW_B


class IViewBuilding;

class VPlayingField : public IViewObject, public IVPlayingField
{
private:
	const int fieldSize = 2;
	std::vector<CPlacement> m_zpPlacementHolders;	
	Array2D<CPlacement> m_zpField;
	Array2D<CGeoCube> m_zgField;
	Array2D<CMaterial> m_zmMaterials;
	Array2D<shared_ptr<IViewBuilding>> viewObjects;
	CPlacement m_zp;

public:
	VPlayingField(VMaster* vMaster, LPlayingField* lPlayingField)
		: IVPlayingField(lPlayingField),
		  m_zpPlacementHolders(lPlayingField->getFieldLength()*lPlayingField->getFieldLength() / 25),
		  m_zpField(lPlayingField->getFieldLength(), lPlayingField->getFieldLength()),
		  m_zgField(lPlayingField->getFieldLength(), lPlayingField->getFieldLength()),
		  m_zmMaterials(lPlayingField->getFieldLength(), lPlayingField->getFieldLength()),
		  viewObjects(lPlayingField->getFieldLength(), lPlayingField->getFieldLength()),
		  IViewObject(vMaster, &m_zp)
		  
	{}
	virtual ~VPlayingField()
	{}

	//TODO (V) remove building again
	template<typename T, typename... Args>
	inline void tryBuildOnField(const int x, const int y, const Args... arguments)
	{
		//todo (V) check return value from "placeBuilding"
		this->lPlayingField->placeBuilding<T>(x, y, arguments...);
	}

	inline void tryRemoveObject(const int x, const int y)
	{
		lPlayingField->removeBuilding(x, y);
	}

	void placeObject(const std::shared_ptr<IViewBuilding>& objPtr, const int x, const int y);

	virtual void initPlayingField();

	virtual void objectRemoved(const int x, const int y);
};


NAMESPACE_VIEW_E
