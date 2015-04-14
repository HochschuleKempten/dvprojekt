#pragma once

#include "../logic/IVPlayingField.h"
#include "../logic/LPlayingField.h"
#include "../logic/Array2D.h"
#include "VMaster.h"
#include "IViewObject.h"
#include <memory>
#include "VField.h"

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
	friend class VField;

private:
	const float fieldSize = 2.0f;
	const float fieldDepth = 0.5f;
	const CHVector size = CHVector(fieldSize, fieldSize, fieldDepth);

	std::vector<CPlacement> m_zpPlacementHolders;	
	Array2D<VField> vFields;
	CPlacement m_zp;

public:
	VPlayingField(VMaster* vMaster, LPlayingField* lPlayingField)
		: IVPlayingField(lPlayingField),
		m_zpPlacementHolders(lPlayingField->getFieldLength()*lPlayingField->getFieldLength() / 25),
		vFields(lPlayingField->getFieldLength(), lPlayingField->getFieldLength(), [this] (VField& vField)
		{
			vField.vPlayingField = this;
		}),
		IViewObject(vMaster, &m_zp)
	{
		vMaster->setVPlayingField(this);
	}
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
