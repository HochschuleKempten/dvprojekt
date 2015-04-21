#pragma once

#include "VGeneral.h"
#include "VFactory.h"
#include "VUI.h"
#include "../logic/IVMaster.h"

NAMESPACE_VIEW_B


class LMaster;
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
	std::shared_ptr<VPlayingField> vPlayingField = nullptr;

public:
	VMaster();
	virtual ~VMaster();

	void setLMaster(LMaster* lMaster);

	void initScene(HWND hwnd, CSplash* psplash);
	void tick(float fTime, float fTimeDelta);

	virtual IVFactory* getFactory() override;
	VPlayingField* getPlayingField();

	void setVPlayingField(const std::shared_ptr<VPlayingField>& vPlayingField);
	
	void resize(int width, int height);

	friend class VUI;
};


NAMESPACE_VIEW_E
