#pragma once

class IView;

class IVMaster
{
public:
	virtual ~IVMaster()
	{}

	virtual void addScenegraph(IView* view) = 0;
	virtual void removeScenegraph(IView* view) = 0;
};
