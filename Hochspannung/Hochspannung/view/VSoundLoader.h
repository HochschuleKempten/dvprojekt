#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class VSoundLoader
{
public:
	enum SoundEffect
	{
		BUILDING_PLACED,
		TRASSE_PLACED,
		OBJECT_REMOVED
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

	static CAudio bacgroundMusicIngameStart;

	static std::unordered_map<SoundEffect, CAudio> soundeffects;
	static std::unordered_map<SoundEffect, CPlacement*> soundeffectsLastPlacements;


public:
	static void init(CScene* scene);
	static void playBackgroundMusicIngame();
	static void playSoundeffectBuildingPlaced(const SoundEffect soundEffect, CPlacement* placement);
};


NAMESPACE_VIEW_E
