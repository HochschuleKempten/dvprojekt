#pragma once

class IView
{
public:
	IView()
	{}
	virtual ~IView()
	{}

	virtual void init() = 0;
};
