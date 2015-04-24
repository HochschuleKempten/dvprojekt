#pragma once
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LTransformerStation;

class IVTransformerStation
{
protected:
	LTransformerStation* lTransformerStation;

public:
	inline IVTransformerStation(LTransformerStation* lTransformerStation)
		: lTransformerStation(lTransformerStation)
	{}
	inline virtual ~IVTransformerStation()
	{}

	virtual void initTransformerStation(const std::shared_ptr<IVTransformerStation>& objPtr, const int x, const int y) = 0;

	//TODO (L) what methodes are needed? 

};

NAMESPACE_LOGIC_E