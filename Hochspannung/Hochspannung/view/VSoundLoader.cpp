#include "VSoundLoader.h"

NAMESPACE_VIEW_B


CScene* VSoundLoader::scene = nullptr;
DEBUG_EXPRESSION(bool VSoundLoader::initDone = false);
DEBUG_EXPRESSION(static const char* const assertMsg = "SoundLoader is not initialized");

CAudio VSoundLoader::bacgroundMusicIngameStart;
std::unordered_map<VSoundLoader::SoundEffect, CAudio> VSoundLoader::soundeffects;
std::unordered_map<VSoundLoader::SoundEffect, CPlacement*> VSoundLoader::soundeffectsLastPlacements;


void VSoundLoader::setSoundEffectHelper(const SoundEffect soundEffect, const std::string& filename)
{
	soundeffects[soundEffect].Init(const_cast<char*>((std::string("sounds/") + filename + std::string(".wav")).c_str()));
	soundeffects[soundEffect].SetVolume(1.0f);
	scene->AddAudio(&soundeffects[soundEffect]);
	soundeffectsLastPlacements[soundEffect] = nullptr;
}

void VSoundLoader::init(CScene* scene)
{
	VSoundLoader::scene = scene;

	bacgroundMusicIngameStart.Init("sounds/ambient-02.wav");
	bacgroundMusicIngameStart.SetVolume(1.0f);
	scene->AddAudio(&bacgroundMusicIngameStart);

	setSoundEffectHelper(BUILDING_PLACED, "createObject");
	setSoundEffectHelper(TRASSE_PLACED, "createTrasse");
	setSoundEffectHelper(OBJECT_REMOVED, "delObject");

	initDone = true;
}

void VSoundLoader::playBackgroundMusicIngame()
{
	ASSERT(initDone, assertMsg);

	bacgroundMusicIngameStart.Loop();
	bacgroundMusicIngameStart.Start();
}

void VSoundLoader::playSoundeffectBuildingPlaced(const SoundEffect soundEffect, CPlacement* placement)
{
	ASSERT(initDone, assertMsg);

	if (soundeffectsLastPlacements[soundEffect] != nullptr)
	{
		soundeffectsLastPlacements[soundEffect]->SubAudio(&soundeffects[soundEffect]);
	}

	placement->AddAudio(&soundeffects[soundEffect]);
	soundeffects[soundEffect].Start();
	soundeffectsLastPlacements[soundEffect] = placement;
}

NAMESPACE_VIEW_E
