#include "VSoundLoader.h"

NAMESPACE_VIEW_B


CScene* VSoundLoader::scene = nullptr;
DEBUG_EXPRESSION(bool VSoundLoader::initDone = false);
DEBUG_EXPRESSION(static const char* const assertMsg = "SoundLoader is not initialized");

CAudio VSoundLoader::backgroundMusicIngameStart;
std::list<CAudio> VSoundLoader::sound3DLoop;
std::unordered_map<VIdentifier::VIdentifier, std::pair<std::string, float>> VSoundLoader::sound3DLoopData;
std::unordered_map<VSoundLoader::SoundEffect, CAudio> VSoundLoader::soundeffects;
std::unordered_map<VSoundLoader::SoundEffect, CPlacement*> VSoundLoader::soundeffectsLastPlacements;
std::unordered_map<std::string, CAudio> VSoundLoader::radioMessages;

void VSoundLoader::setSoundEffectHelper(const SoundEffect soundEffect, const std::string& filename)
{
	soundeffects[soundEffect].Init(&(std::string("sounds/") + filename + std::string(".wav"))[0]);
	soundeffects[soundEffect].SetVolume(1.0f);
	scene->AddAudio(&soundeffects[soundEffect]);
	soundeffectsLastPlacements[soundEffect] = nullptr;
}

void VSoundLoader::init(CScene* scene)
{
	VSoundLoader::scene = scene;

	backgroundMusicIngameStart.Init("sounds/ambient-02-vip.wav");
	backgroundMusicIngameStart.SetVolume(0.8f);
	scene->AddAudio(&backgroundMusicIngameStart);
	
	sound3DLoopData.emplace(std::piecewise_construct, std::make_tuple(VIdentifier::VTransformerStation), std::make_tuple("sounds/bruitelectrique.wav", 0.15f));
	sound3DLoopData.emplace(std::piecewise_construct, std::make_tuple(VIdentifier::VHydroelectricPowerPlant), std::make_tuple("sounds/WaterWheelLoop.wav", 0.2f));
	sound3DLoopData.emplace(std::piecewise_construct, std::make_tuple(VIdentifier::VWindmillPowerPlant), std::make_tuple("sounds/AirPowerPlantLoop.wav", 0.8f));

	setSoundEffectHelper(BUILDING_PLACED, "createObject");
	setSoundEffectHelper(TRASSE_PLACED, "createTrasse");
	setSoundEffectHelper(OBJECT_REMOVED, "delObject");
	setSoundEffectHelper(OPERATION_CANCELED, "click");
	setSoundEffectHelper(POWERPLANT_SWITCH_ON, "gui_switch");
	setSoundEffectHelper(POWERPLANT_SWITCH_OFF, "gui_switch");
	setSoundEffectHelper(SABOTAGE_RECEIVED, "sabotage_receive");
	setSoundEffectHelper(SABOTAGE_EMITTED, "sabotage_execute");
	setSoundEffectHelper(ENERGY_LOW, "lowEnergy");
	setSoundEffectHelper(GAME_OVER, "game_lose");
	setSoundEffectHelper(GAME_WON, "game_win");

	radioMessages["STest"].Init("");
	radioMessages["STest"].SetVolume(1.0f);
	scene->AddAudio(&radioMessages["STest"]);

	DEBUG_EXPRESSION(initDone = true);
}

void VSoundLoader::playBackgroundMusicIngame()
{
	ASSERT(initDone, assertMsg);

	backgroundMusicIngameStart.Loop();
}

void VSoundLoader::play3DSoundLoop(const VIdentifier::VIdentifier building, CPlacement* placement)
{
	ASSERT(initDone, assertMsg);
	ASSERT(sound3DLoopData.count(building) > 0, "The requested 3D-Sound is not availavle");
	
	sound3DLoop.emplace_back();
	sound3DLoop.back().Init3D(&sound3DLoopData[building].first[0], sound3DLoopData[building].second);
	sound3DLoop.back().SetVolume(1.0f);
	sound3DLoop.back().Loop();
	
	placement->AddAudio(&sound3DLoop.back());
}

void VSoundLoader::playSoundeffect(const SoundEffect soundEffect, CPlacement* placement)
{
	ASSERT(initDone, assertMsg);

	//If no placement is given, add to scene
	if (placement == nullptr)
	{
		static SoundEffect previousSoundEffect = CASTS<SoundEffect>(-1);

		//Sub previous soundeffect from scene
		if (previousSoundEffect != -1)
		{
			scene->SubAudio(&soundeffects[previousSoundEffect]);
		}

		scene->AddAudio(&soundeffects[soundEffect]);
		soundeffects[soundEffect].Start();
		previousSoundEffect = soundEffect;
	}
	else
	{
		//Sub Audio from previous placement
		if (soundeffectsLastPlacements[soundEffect] != nullptr)
		{
			soundeffectsLastPlacements[soundEffect]->SubAudio(&soundeffects[soundEffect]);
		}

		placement->AddAudio(&soundeffects[soundEffect]);
		soundeffects[soundEffect].Start();
		soundeffectsLastPlacements[soundEffect] = placement;
	}
}

void VSoundLoader::playRadioMessage(const std::string& message)
{
	radioMessages["STest"].Start();
}

NAMESPACE_VIEW_E
