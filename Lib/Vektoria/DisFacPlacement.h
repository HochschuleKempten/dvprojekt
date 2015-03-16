#pragma once
#include "Placement.h"
#include "DisFacCamera.h"
#include "DisFacGeoSphere.h"
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>

namespace Vektoria
{

typedef std::tr1::unordered_map<int,CPlacement*> root_map;

class CDisFacPlacement{

private:
	root_map m_mipPlacement;
public:
	CDisFacPlacement();
	~CDisFacPlacement();
	void Create(int iObjectID);
	CPlacement* GetPlacementObject(int iObjectID);
	void AddCamera(std::stringstream &ss, int iObjectID,CDisFacCamera &dfc);
	void AddGeoSphere(std::stringstream &ss, int iObjectID,CDisFacGeoSphere &dfgs);
	void RotateY(std::stringstream &ss, int iObjectID);
	void RotateZDelta(std::stringstream &ss, int iObjectID);
	void RotateXDelta(std::stringstream &ss, int iObjectID);
	void TranslateDeltaVector(std::stringstream &ss, int iObjectID);
};

}