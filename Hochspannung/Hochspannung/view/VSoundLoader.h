#pragma once

#include "VGeneral.h"
#include "VIdentifier.h"

NAMESPACE_VIEW_B


class VSoundLoader
{
public:
	enum SoundEffect
	{
		BUILDING_PLACED,
		TRASSE_PLACED,
		OBJECT_REMOVED,
		OPERATION_CANCELED,
		POWERPLANT_SWITCH_ON,
		POWERPLANT_SWITCH_OFF,
		SABOTAGE_RECEIVED,
		SABOTAGE_EMITTED,
		ENERGY_LOW,
		GAME_OVER,
		GAME_WON
	};

private:
	VSoundLoader() = delete;
	VSoundLoader(const VSoundLoader&) = delete;
	VSoundLoader(const VSoundLoader&&) = delete;
	VSoundLoader& operator=(const VSoundLoader&) = delete;
	VSoundLoader& operator=(const VSoundLoader&&) = delete;
	~VSoundLoader() = delete;

	static void setSoundEffectHelper(const SoundEffect soundEffect, const std::string& filename);

private:
	static CScene* scene;		//Background music needs to be added to scene
	DEBUG_EXPRESSION(static bool initDone);
	static CAudio backgroundMusicIngameStart;
	static std::list<CAudio> sound3DLoop;
	static std::unordered_map<VIdentifier::VIdentifier, std::pair<std::string, float>> sound3DLoopData;	//pair = (path, radius)
	static std::unordered_map<SoundEffect, CAudio> soundeffects;
	static std::unordered_map<SoundEffect, CPlacement*> soundeffectsLastPlacements;

public:
	static void init(CScene* scene);
	static void playBackgroundMusicIngame();
	static void play3DSoundLoop(const VIdentifier::VIdentifier building, CPlacement* placement);
	static void playSoundeffect(const SoundEffect soundEffect, CPlacement* placement);
};


NAMESPACE_VIEW_E
