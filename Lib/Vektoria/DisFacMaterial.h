#pragma once
#include "Material.h"
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>

namespace Vektoria
{

typedef std::tr1::unordered_map<int,CMaterial*> material_map;

class CDisFacMaterial{

private:
	material_map m_mipMaterial;
public:
	CDisFacMaterial();
	~CDisFacMaterial();
	void Create(int iObjectID);
	CMaterial* GetMaterialObject(int iObjectID);
	void MakeTextureDiffuse(std::stringstream &ss, int iObjectID);
	void SetTextureSpecularAsImage(std::stringstream &ss, int iObjectID);
	void MakeTextureBump(std::stringstream &ss, int iObjectID);
	void SetBumpStrength(std::stringstream &ss, int iObjectID);
};

}