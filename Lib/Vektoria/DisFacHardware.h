#pragma once
#include "Hardware.h"
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>

namespace Vektoria
{

typedef std::tr1::unordered_map<int,CHardware*> hardware_map;

class CDisFacHardware{

private:
	hardware_map m_mipHardware;
public:
	CDisFacHardware();
	~CDisFacHardware();
	void Create(int iObjectID);
	CHardware* GetHardwareObject(int iObjectID);
};

}