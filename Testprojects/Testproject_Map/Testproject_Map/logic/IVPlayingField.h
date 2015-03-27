#pragma once

#include "IView.h"
#include "LPlayingField.h"

class IVPlayingField : public IView
{
protected:
	LPlayingField* field;

public:
	IVPlayingField(IVMaster* master, LPlayingField* field)
		: IView(master), field(field)
	{}
	virtual ~IVPlayingField()
	{}
};
