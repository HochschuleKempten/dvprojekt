#pragma once
#include "Scene.h"
#include "DisFacPlacement.h"
#include "DisFacParallelLight.h"
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>

namespace Vektoria
{

typedef std::tr1::unordered_map<int,CScene*> scene_map;

class CDisFacScene{

private:
	scene_map m_mipScene;
public:
	CDisFacScene();
	~CDisFacScene();
	void Create(int iObjectID);
	CScene* GetSceneObject(int iObjectID);
	void AddPlacement(std::stringstream &ss, int iObjectID,CDisFacPlacement &dfp);
	void AddParallelLight(std::stringstream &ss, int iObjectID,CDisFacParallelLight &dfpl);

};

}