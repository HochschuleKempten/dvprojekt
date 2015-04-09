#pragma once

#include "IVKohlekraftwerk.h"

class MKraftwerke
{
public:
	virtual void myCoolFunction() = 0;
};

template<class T>
class MKohlekraftwerk : public MKraftwerke
{
private:
	IVKohlekraftwerk* view;

public:
	MKohlekraftwerk()
		: view(new T(this))
	{}

	virtual void myCoolFunction()
	{
		view->resize(2, 19);
	}
};
