#pragma once

#include "LGeneral.h"
#include "LUtility.h"

NAMESPACE_LOGIC_B

class IVMaster;
class LWindmillPowerPlant;
class LSolarPowerPlant;
class LHydroelectricPowerPlant;
class LCoalPowerPlant;
class LOilRefinery;
class LNuclearPowerPlant;
class LPowerLine;

class LMessageLoader
{
public:
	enum MessageID
	{
		SABOTAGE_EMITTED,
		SABOTAGE_NO_ACTS_LEFT,
		SABOTAGE_WAIT,
		SABOTAGE_NO_MONEY,
		BUILD_NO_MONEY,
		BUILD_FIELD_OCCUPIED,
		BUILD_FIELD_WRONG_TYPE,
		NETWORK_CONNECTION_LOST
	};

private:
	LMessageLoader() = delete;
	LMessageLoader(const LMessageLoader&) = delete;
	LMessageLoader(const LMessageLoader&&) = delete;
	LMessageLoader& operator=(const LMessageLoader&) = delete;
	LMessageLoader& operator=(const LMessageLoader&&) = delete;
	~LMessageLoader() = delete;

private:
	static IVMaster* vMaster;
	DEBUG_EXPRESSION(static bool initDone);

public:
	static void init(IVMaster* vMaster);
	
	static void emitMessage(const MessageID messageId, const std::vector<std::string>& param = {});

	template<typename T> static std::string getNameForBuildingType() { return ""; }
	template<> static std::string getNameForBuildingType<LWindmillPowerPlant>() { return "Windkraftwerk"; }
	template<> static std::string getNameForBuildingType<LSolarPowerPlant>() { return "Solarkraftwerk"; }
	template<> static std::string getNameForBuildingType<LHydroelectricPowerPlant>() { return "Wasserkraftwerk"; }
	template<> static std::string getNameForBuildingType<LCoalPowerPlant>() { return "Kohlekraftwerk"; }
	template<> static std::string getNameForBuildingType<LOilRefinery>() { return "Ölkraftwerk"; }
	template<> static std::string getNameForBuildingType<LNuclearPowerPlant>() { return "Atomkraftwerk"; }
	template<> static std::string getNameForBuildingType<LPowerLine>() { return "Strommasten"; }

	static std::string getNameForFieldType(const int fieldType);
};

NAMESPACE_LOGIC_E
