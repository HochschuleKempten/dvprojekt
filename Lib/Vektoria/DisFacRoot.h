#pragma once
#include "Root.h"
#include "DisFacScene.h"
#include "DisFacFrame.h"
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>

namespace Vektoria
{

typedef std::tr1::unordered_map<int,CRoot*> disroot_map;

class CDisFacRoot{
	
private:
	disroot_map m_mipRoot;
public:
	CDisFacRoot();
	~CDisFacRoot();
	void Create(int iObjectID);
	CRoot* GetRootObject(int iObjectID);
	void AddFrameHere(std::stringstream &ss,int iObjectID, CDisFacFrame &dff);
	void AddScene(std::stringstream &ss,int iObjectID,CDisFacScene &dfs);
	void Tick(std::stringstream &ss,int iObjectID);
};

}