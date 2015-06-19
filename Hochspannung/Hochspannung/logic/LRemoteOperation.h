#pragma once

#include "LGeneral.h"
#include "LUtility.h"
#include "LPlayingField.h"

NAMESPACE_LOGIC_B

class ILPowerPlant;
class LPlayer;

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
	LPlayer* lPlayer = nullptr;
	LCity* lCity = nullptr;
	DEBUG_EXPRESSION(const char* const msglPowerPlantNotInitialized = "lPowerPlant is not initialized. Make sure you pass a valid pointer to ILPowerPlant in the constructor");

private:
	//Objects of this class should never be allocated on the heap
	static void* operator new(const size_t) = delete;
	static void* operator new[](const size_t) = delete;
	static std::deque<std::function<void()>> storedNetworkCalls;

public:
	explicit LRemoteOperation(LPlayingField* lPlayingField);
	LRemoteOperation(LPlayingField* lPlayingField, ILPowerPlant* lPowerPlant);
	LRemoteOperation(LPlayingField* lPlayingField, LPlayer* lPlayer);
	LRemoteOperation(LPlayingField* lPlayingField, LCity* lCity);
	~LRemoteOperation();

	//LPlayingField methods
	template <typename T, typename... Args>
	bool placeBuilding(const int x, const int y, const int playerId, const Args... arguments)
	{
		return lPlayingField->placeBuilding<T, Args...>(x, y, playerId, arguments...);
	}
	bool removeBuilding(const int x, const int y);
	void upgradeBuilding(const int x, const int y);

	//ILPowerPlant methods
	void switchOn();
	void switchOff();
	void sabotagePowerPlantEnd();

	//LPlayer methods
	bool sabotageRemove(ILBuilding* lBuilding);
	bool sabotageDeactivate(ILPowerPlant* lPowerPlant);
	bool sabotageResource(ILPowerPlant* lPowerPlant);

	//LCity methods
	void setPopulationTotal(const int populationTotal);

public:
	static void sendStoredNetworkCalls();
};

NAMESPACE_LOGIC_E
