#pragma once

#include "DistributedGlobal.h"
#include "DisFacCamera.h"
#include "DisFacFrame.h"
#include "DisFacGeoSphere.h"
#include "DisFacHardware.h"
#include "DisFacMaterial.h"
#include "DisFacParallelLight.h"
#include "DisFacPlacement.h"
#include "DisFacRoot.h"
#include "DisFacScene.h"
#include "DisFacViewport.h"

namespace Vektoria
{

typedef std::tr1::unordered_map<int,int> exist_map;

class CDisManager{
private:
	
	exist_map m_miiExist;// test auf Existenz
	CDisFacRoot m_dfr;
	CDisFacScene m_dfs;
	CDisFacPlacement m_dfp;
	CDisFacGeoSphere m_dfgs;
	CDisFacHardware m_dfh;
	CDisFacFrame m_dff;
	CDisFacViewport m_dfv;
	CDisFacCamera m_dfc;
	CDisFacParallelLight m_dfpl;
	CDisFacMaterial m_dfm;
	HWND m_hwnd;
	bool m_bDisStart;
public:
	CDisManager();
	~CDisManager();
	void ParseSS(stringstream &ss);
	void CreateObjects(int iObjectId,int iClassId);
	void UseMethods(stringstream &ss, int iObjectId, int iClassId);
	int GetExist(int ObjectId);
	void SetHWND(HWND &hwnd);
	bool GetStart();
	void SetStart(bool start);

	CDisFacRoot* GetRootObject(int iObjectId);
	CDisFacScene* GetSceneObject(int iObjectId);
	CDisFacPlacement* GetPlacementObject(int iObjectId);
	CDisFacGeoSphere* GetGeoSphereObject(int iObjectId);
	CDisFacHardware* GetHardwareObject(int iObjectId);
	CDisFacFrame* GetFrameObject(int iObjectId);
	CDisFacViewport* GetViewportObject(int iObjectId);
	CDisFacCamera* GetCameraObject(int iObjectId);
	CDisFacParallelLight* GetParallelLightObject(int iObjectId);
	CDisFacMaterial* GetMaterialObject(int iObjectId);

};

}