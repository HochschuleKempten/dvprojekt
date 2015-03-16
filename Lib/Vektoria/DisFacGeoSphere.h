#pragma once
#include "GeoSphere.h"
#include "DisFacMaterial.h"
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>

namespace Vektoria
{

typedef std::tr1::unordered_map<int,CGeoSphere*> geoSphere_map;

class CDisFacGeoSphere{

private:
	geoSphere_map m_mipGeoSphere;
public:
	CDisFacGeoSphere();
	~CDisFacGeoSphere();
	void Create(int iObjectID);
	CGeoSphere* GetGeoSphereObject(int iObjectID);
	void Init(std::stringstream &ss, int iObjectID, CDisFacMaterial &dfm);
};

}