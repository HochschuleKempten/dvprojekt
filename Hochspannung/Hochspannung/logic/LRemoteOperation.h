#pragma once

#include "LGeneral.h"
#include "LUtility.h"
#include "LPlayingField.h"
#include "ILPowerPlant.h"

NAMESPACE_LOGIC_B

/*
 * @brief The LRemoteOperation class is supposed to be used from the view side for all operations which trigger a remote operation (e. g. placing a object on the field).
 *
 * You need to create an additional object of this class for every operation. So don't put objects into class member variables, create them separately on the stack instead.
 */
class LRemoteOperation
{
	NON_COPYABLE(LRemoteOperation);

private:
	LPlayingField* lPlayingField = nullptr;
	ILPowerPlant* lPowerPlant = nullptr;

private:
	//Objects of this class should never be allocated on the heap
	static void* operator new(const size_t) = delete;
	static void* operator new[](const size_t) = delete;
	
public:
	inline explicit LRemoteOperation(LPlayingField* lPlayingField)
		: lPlayingField(lPlayingField)
	{
		lPlayingField->beginRemoteOperation();
	}
	inline LRemoteOperation(LPlayingField* lPlayingField, ILPowerPlant* lPowerPlant)
		: lPlayingField(lPlayingField), lPowerPlant(lPowerPlant)
	{
		lPlayingField->beginRemoteOperation();
	}
	inline ~LRemoteOperation()
	{
		lPlayingField->endRemoteOperation();
	}

	//LPlayingField methods
	template <typename T, typename... Args>
	inline bool placeBuilding(const int x, const int y, const int playerId, const Args... arguments)
	{
		return lPlayingField->placeBuilding<T, Args...>(x, y, playerId, arguments...);
	}
	inline bool removeBuilding(const int x, const int y)
	{
		return lPlayingField->removeBuilding(x, y);
	}
	inline void upgradeBuilding(const int x, const int y)
	{
		lPlayingField->upgradeBuilding(x, y);
	}

	//ILPowerPlant methods
	inline void switchOn()
	{
		lPowerPlant->switchOn();
	}
	inline void switchOff()
	{
		lPowerPlant->switchOff();
	}
	inline void sabotage()
	{
		lPowerPlant->sabotage();
	}
	inline void sabotageResource()
	{
		lPowerPlant->sabotageResource();
	}
};

NAMESPACE_LOGIC_E
