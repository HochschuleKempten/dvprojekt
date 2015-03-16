#pragma once
#include "Frame.h"
#include "DisFacViewport.h"
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>

namespace Vektoria
{

typedef std::tr1::unordered_map<int,CFrame*> frame_map;

class CDisFacFrame{

private:
	frame_map m_mipFrame;
public:
	CDisFacFrame();
	~CDisFacFrame();
	void Create(int iObjectID);
	CFrame* GetFrameObject(int iObjectID);
	void Init(std::stringstream &ss, int iObjectID, HWND hwnd);
	void AddViewport(std::stringstream &ss, int iObjectID, CDisFacViewport &dfv);
};

}