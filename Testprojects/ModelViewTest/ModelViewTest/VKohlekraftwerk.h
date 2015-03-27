#pragma once

#include "IVKohlekraftwerk.h"
#include "MKraftwerke.h"
#include <iostream>

class VKohlekraftwerk : public IVKohlekraftwerk
{
private:
	MKohlekraftwerk<VKohlekraftwerk>* model;

public:
	VKohlekraftwerk(MKohlekraftwerk<VKohlekraftwerk>* model)
		: model(model)
	{}

	virtual void resize(const int width, const int height)
	{
		std::cout << "width = " << width << ", height = " << height << std::endl;
	}
};
