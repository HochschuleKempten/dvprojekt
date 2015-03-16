#pragma once
#include "Viewport.h"
#include "DisFacCamera.h"
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>

namespace Vektoria
{

typedef std::tr1::unordered_map<int,CViewport*> viewport_map;

class CDisFacViewport{

private:
	viewport_map m_mipViewport;
public:
	CDisFacViewport();
	~CDisFacViewport();
	void Create(int iObjectID);
	CViewport* GetViewportObject(int iObjectID);
	void InitFull(std::stringstream &ss, int iObjectID,CDisFacCamera &m_dfc);
};

}