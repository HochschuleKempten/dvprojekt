#pragma once

class LMaster;
class IVUI;

class LUI
{
private:
	LMaster* lMaster;
	IVUI* vUi;

public:
	LUI(LMaster* lMaster);
	~LUI();
};
