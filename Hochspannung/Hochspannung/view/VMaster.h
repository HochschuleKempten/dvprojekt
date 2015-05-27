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

	void startSinglePlayerGame();
	void hostGame();
	void joinGame(const std::string& ipAddress);

	virtual void updateMoney(const int money) override;
	virtual void updateRemainingSabotageActs(const int remainingSabotageActs) override;
	virtual void updateAddedPowerPlant(const LIdentifier::LIdentifier id) override;
	virtual void updateRemovedPowerPlant(const LIdentifier::LIdentifier id) override;
	virtual void updateNumberPowerLines(const int newNumberPowerLines) override;
	virtual void pauseGame() override;
	virtual void continueGame() override;
	virtual void gameWon() override;
	virtual void gameOver() override;
	virtual void updateGameList(const std::vector<Network::CGameObject>& gameList) override;
	virtual void messageSabotageFailed(const std::string& message) override;
	virtual void messageBuildingFailed(const std::string& message) override;
	virtual IVFactory* getFactory() override;

	inline VPlayingField* getVPlayingField()
	{
		ASSERT(vPlayingField != nullptr, "VPlayingField is not initialized");

		return vPlayingField.get();
	}
};


NAMESPACE_VIEW_E
