#pragma once

class IVMaster;
class LPlayingField;
class LPlayer;
class LUI;

class LMaster
{

private:
	IVMaster* vMaster;
	LPlayingField* lPlayingField;
	LPlayer* lPlayer;
	LUI* lUi;

public:
	LMaster(IVMaster* vMaster);
	~LMaster();

	void startNewGame();
	void tick(float fTime, float fTimeDelta);

	LPlayingField* getLPlayingField();
	IVMaster* getVMaster();
	LPlayer* getPlayer();

};
