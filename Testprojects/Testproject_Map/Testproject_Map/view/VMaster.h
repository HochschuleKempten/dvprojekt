#pragma once

#include "../logic/IVMaster.h"
#include "IViewObject.h"
#include "VFactory.h"

class LMaster;

NAMESPACE_VIEW_B


class VPlayingField;

class VMaster : public IVMaster
{
private:
	CRoot m_zr;
	CFrame m_zf;
	CViewport m_zv;
	CCamera m_zc;
	CPlacement m_zpCamera;
	CScene m_zs;
	CDeviceKeyboard m_zk;
	CDeviceCursor m_zkCursor;
	CDeviceMouse m_zkMouse;
	CParallelLight m_zl;
	CBackground m_zb;

	std::map<std::string, IViewObject*> views;
	VFactory factory;
	LMaster* lMaster;

public:
	VMaster();
	virtual ~VMaster()
	{}

	void setLMaster(LMaster* lMaster);

	void initScene(HWND hwnd, CSplash* psplash);
	void tick(float fTime, float fTimeDelta);

	virtual IVFactory* getFactory();
	VPlayingField* getPlayingField();

	void addScenegraph(const std::string &name, IViewObject* view);
	void removeScenegraph(const std::string &name, IViewObject* view) {}

};


NAMESPACE_VIEW_E
