#pragma once
#include "Camera.h"
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>

namespace Vektoria
{

typedef std::tr1::unordered_map<int,CCamera*> camera_map;

class CDisFacCamera{

private:
	
public:
	camera_map m_mipCamera;
	CDisFacCamera();
	~CDisFacCamera();
	void Create(int iObjectID);
	CCamera* GetCameraObject(int iObjectID);
	void Init(std::stringstream &ss, int iObjectID);
};

}