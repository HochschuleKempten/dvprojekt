#pragma once

#include "../logic/IVMaster.h"
#include "VFactory.h"
#include "VGeneral.h"
#include "VUI.h"

class LMaster;

NAMESPACE_VIEW_B


class IViewObject;
class VPlayingField;

class VMaster : public IVMaster
{
private:
	CRoot m_zr;
	CFrame m_zf;
	
	VFactory factory;
	VUI vUi;
	LMaster* lMaster = nullptr;
	VPlayingField* vPlayingField = nullptr;

public:
	VMaster();
	virtual ~VMaster()
	{}

	void setLMaster(LMaster* lMaster);

	void initScene(HWND hwnd, CSplash* psplash);
	void tick(float fTime, float fTimeDelta);

	virtual IVFactory* getFactory();
	VPlayingField* getPlayingField();

	void setVPlayingField(VPlayingField* vPlayingField);
	
	void resize(int width, int height);

	friend class VUI;
};


NAMESPACE_VIEW_E
