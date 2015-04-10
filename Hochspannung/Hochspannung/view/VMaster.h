#pragma once

#include "../logic/IVMaster.h"
#include "VFactory.h"
#include "VGeneral.h"
#include "../logic/IDGenerator.h"

class LMaster;

NAMESPACE_VIEW_B


class IViewObject;
class VPlayingField;
class VUI;

class VMaster : public IVMaster
{
private:
	CRoot m_zr;
	CFrame m_zf;
	

	std::map<std::string, IViewObject*> views;
	VFactory factory;
	LMaster* lMaster;
	VUI* vUi;

public:
	VMaster();
	virtual ~VMaster()
	{}

	void setLMaster(LMaster* lMaster);
	void setVUI(VUI* vUi);

	void initScene(HWND hwnd, CSplash* psplash);
	void tick(float fTime, float fTimeDelta);

	virtual IVFactory* getFactory();
	VPlayingField* getPlayingField();

	void addScenegraph(const std::string &name, IViewObject* view);
	//void removeScenegraph(const std::string &name, IViewObject* view) {}
	void resize(int width, int height);

	friend class VUI;
	static int id;
};


NAMESPACE_VIEW_E
