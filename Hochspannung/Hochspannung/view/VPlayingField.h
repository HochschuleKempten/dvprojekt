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

/**
 * @brief The VPlayingField class controls the playing field in the game.
 *
 * Due to performance reasons the hierarchy of this class currently looks like shown in the following image:
 *
 * @image html images/VPlayingField_hierarchy.png "Hierarchy of the playing field"
 *
 * Each holder coltrols a small field part about 5x5 placements. On each of these placements is the geo of the field
 * itself and a view object, if some was placed.
 */
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
	virtual ~VPlayingField();

	//TODO (V) remove building again
	template<typename T, typename... Args>
	inline void tryBuildOnField(const int x, const int y, const Args... arguments)
	{
		if (!lPlayingField->placeBuilding<T>(x, y, arguments...)) {
			DEBUG_OUTPUT("Could not place building at " << x << ", " << y);
		}
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
