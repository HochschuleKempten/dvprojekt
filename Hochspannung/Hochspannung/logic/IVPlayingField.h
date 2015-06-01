#pragma once
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LPlayingField;

class IVPlayingField
{
protected:
	LPlayingField* lPlayingField;

public:
	explicit IVPlayingField(LPlayingField* lPlayingField)
		: lPlayingField(lPlayingField)
	{}
	virtual ~IVPlayingField()
	{}

	virtual void initPlayingField(const std::shared_ptr<IVPlayingField>& objPtr) = 0;
	virtual void buildPlayingField() = 0;

	virtual void objectRemoved(const int x, const int y) = 0;
};

NAMESPACE_LOGIC_E