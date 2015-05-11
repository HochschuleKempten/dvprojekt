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
	NON_COPYABLE(VMaster);
	friend class VUI;

private:
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

	VUI* getVUi();
	void setVPlayingField(const std::shared_ptr<VPlayingField>& vPlayingField);
	void resize(int width, int height);

	DEBUG_EXPRESSION(void startSinglePlayerGame());
	void hostGame();
	void joinGame(const std::string& ipAddress);

	virtual void updateMoney(const int money) override;
	virtual void pauseGame() override;
	virtual void continueGame() override;
	virtual void gameOver() override;
	virtual IVFactory* getFactory() override;

	inline VPlayingField* getPlayingField()
	{
		ASSERT(vPlayingField != nullptr, "VPlayingField is not initialized");

		return vPlayingField.get();
	}
};


NAMESPACE_VIEW_E
