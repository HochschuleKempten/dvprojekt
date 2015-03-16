#pragma once
#include "ParallelLight.h"
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>

namespace Vektoria
{

typedef std::tr1::unordered_map<int,CParallelLight*> parallelLight_map;

class CDisFacParallelLight{

private:
	parallelLight_map m_mipParallelLight;
public:
	CDisFacParallelLight();
	~CDisFacParallelLight();
	void Create(int iObjectID);
	CParallelLight* GetParallelLightObject(int iObjectID);
	void Init(std::stringstream &ss, int iObjectID);
};

}