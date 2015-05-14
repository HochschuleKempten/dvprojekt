#pragma once

#include "../logic/IVPlayingField.h"
#include "../logic/LRemoteOperation.h"
#include "../logic/Array2D.h"
#include "IViewObject.h"
#include "VField.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B


class IViewBuilding;

/**
 * @brief The VPlayingField class controls the playing field in the game.
 *
 * Due to performance reasons the hierarchy of this class currently looks like shown in the following image:
 *
 * @image html images/VPlayingField_hierarchy.png "Hierarchy of the playing field"
 *
 * Each holder controls a small field part about 5x5 placements. On each of these placements is the geo of the field
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
	DynArray2D<VField> vFields;
	CPlacement m_zp;

public:
	VPlayingField(VMaster* vMaster, LPlayingField* lPlayingField);
	virtual ~VPlayingField();

	template<typename T, typename... Args>
	inline void tryBuildOnField(const int x, const int y, const Args... arguments)
	{
		LRemoteOperation lRemoteOperation(lPlayingField);

		bool operationSuccessful = lRemoteOperation.placeBuilding<T>(x, y, LPlayer::Local, arguments...);

		playSound<T>(operationSuccessful, &vFields[x][y].m_zp);
		if (!operationSuccessful)
		{
			DEBUG_OUTPUT("Could not place building at " << x << ", " << y);
		}
	}

	template<typename T>
	inline void playSound(const bool operationSuccessful, CPlacement* placementField)
	{
		//TODO (V) play different sound when building cannot be placed
		VSoundLoader::playSoundeffectBuildingPlaced(VSoundLoader::BUILDING_PLACED, placementField);
	}
	template<>
	inline void playSound<LPowerLine>(const bool operationSuccessful, CPlacement* placementField)
	{
		VSoundLoader::playSoundeffectBuildingPlaced(VSoundLoader::TRASSE_PLACED, placementField);
	}

	inline void tryRemoveObject(const int x, const int y)
	{
		LRemoteOperation lRemoteOperation(lPlayingField);

		lRemoteOperation.removeBuilding(x, y);
	}

	void placeObject(const std::shared_ptr<IViewBuilding>& objPtr, const int x, const int y);
	void hoverField(const int x, const int y);
	IViewBuilding * getBuilding(const int x, const int y);

	virtual void initPlayingField(const std::shared_ptr<IVPlayingField>& objPtr) override;
	virtual void buildPlayingField() override;
	virtual void objectRemoved(const int x, const int y) override;
	virtual void messageBuildingFailed(const std::string& message) override;
	float getFieldSize() const
	{
		return fieldSize;
	}
};


NAMESPACE_VIEW_E
