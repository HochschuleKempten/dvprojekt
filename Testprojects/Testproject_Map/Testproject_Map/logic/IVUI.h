#pragma once

class LUI;

class IVUI
{
protected:
	LUI* lUi;

public:
	inline IVUI(LUI* lUi)
		: lUi(lUi)
	{}
	inline virtual ~IVUI()
	{}
};
