#pragma once

#include <string>
#include <iostream>
#include <sstream>

//#define NETWORKMASTER // to get all methods on the stream when being used by the master
#define DISTRIBUTED_RENDERING // for the client to use the stream and to use the enums

#ifdef NETWORKMASTER
extern unsigned int g_idId; //int distributed, eindeutige,fortlaufende ID für alle Objekte
#endif

#ifdef DISTRIBUTED_RENDERING
extern std::stringstream g_ssMaster; //Verzicht auf singelton 

// enums to keep the maintaining of distributed Vektoria a little bit simpler
// every time a new adapter or factory is written it needs to be registered in the enums and in the switch-cases of the managerclass
namespace Vektoria
{

enum EDisClass{
	eDisRoot=1,
	eDisScene,
	eDisPlacement,
	eDisGeoSphere,
	eDisHardware,
	eDisFrame,
	eDisViewport,
	eDisCamera,
	eDisParallelLight,
	eDisMaterial
};
enum EDisFacRoot{
	edfrAddFrameHere=1,
	edfrAddScene,
	edfrTick
};
enum EDisFacScene{
	edfsAddPlacement=1,
	edfsAddParallelLight
};
enum EDisFacPlacement{
	edfpAddCamera=1,
	edfpAddGeo,
	edfpRotateY,
	edfpRotateZDelta,
	edfpRotateXDelta,
	edfpTranslateDeltaVector
};
enum EDisFacGeoSphere{edfgsInit=1};
enum EDisFacHardware{};
enum EDisFacFrame{
	edffInit=1,
	edffAddViewport
};
enum EDisFacViewport{edfvInitFull=1};
enum EDisFacCamera{edfcInit=1};
enum EDisFacParallelLight{edfplInit=1};
enum EDisFacMaterial{
	edfmMakeTextureDiffuse=1,
	edfmSetTextureSpecularAsImage,
	edfmMakeTextureBump,
	edfmSetBumpStrength
};

#endif

}