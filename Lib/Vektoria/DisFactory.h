#include "Root.h"
#include <map>
#include <unordered_map>

namespace Vektoria
{
 
class CDisFactory{
private:
	std::tr1::unordered_map<int,CRoot*> m_mipRoot;
	std::tr1::unordered_map<int,CScene*> m_mipScene;
	std::tr1::unordered_map<int,CPlacement*> m_mipPlacement;
	std::tr1::unordered_map<int,CGeoSphere*> m_mipGeoSphere;
	std::tr1::unordered_map<int,CHardware*> m_mipHardware;
	std::tr1::unordered_map<int,CFrame*> m_mipFrame;
	std::tr1::unordered_map<int,CViewport*> m_mipViewport;
	std::tr1::unordered_map<int,CCamera*> m_mipCamera;
	std::tr1::unordered_map<int,CParallelLight*> m_mipParallelLight;
	std::tr1::unordered_map<int,CMaterial*> m_mipMaterial;
	std::tr1::unordered_map<int,int> m_miiExist;// test auf Existenz
public:
	CDisFactory();
	~CDisFactory();
	void Create(int iObjectId,int iClassId);
	void Do(stringstream &stream);
	CRoot* GetRoot(int iObjectId); 
	CScene* GetScene(int iObjectId);
	CPlacement* GetPlacement(int iObjectId);
	CGeoSphere* GetGeoSphere(int iObjectId);
	CHardware* GetHardware(int iObjectId);
	CFrame* GetFrame(int iObjectId);
	CViewport* GetViewport(int iObjectId);
	CCamera* GetCamera(int iObjectId);
	CParallelLight* GetParallelLight(int iObjectId);
	CMaterial* GetMaterial(int iObjectId);

};

}