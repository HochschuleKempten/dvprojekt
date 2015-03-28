#pragma once

#include "Vektoria\Root.h"
#include "VektoriaMath\Util.h"
#include "../logic/IVMaster.h"
#include <vector>

class LMaster;

using namespace Vektoria;

#define NAMESPACE_VIEW_B namespace HighVoltage{ namespace view{
#define NAMESPACE_VIEW_E }}
#define DEBUG_OUTPUT(expr) do { std::stringstream s; s << expr << std::endl; OutputDebugString(s.str().c_str()); } while(0)

NAMESPACE_VIEW_B

class VFactory;

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

	std::vector<IView*> views;
	VFactory* factory;
	LMaster* lMaster;

public:
	VMaster();
	virtual ~VMaster();

	void setLMaster(LMaster* lMaster);

	void initScene(HWND hwnd, CSplash* psplash);
	void tick(float fTime, float fTimeDelta);

	virtual IVFactory* getFactory();
	virtual void addScenegraph(IView* view);
	virtual void removeScenegraph(IView* view) {}
};

NAMESPACE_VIEW_E
