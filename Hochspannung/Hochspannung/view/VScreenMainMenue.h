#pragma once
#include "IViewScreen.h"

NAMESPACE_VIEW_B

class VScreenMainMenue :
	public IViewScreen
{
public:
	VScreenMainMenue();
	VScreenMainMenue(CFrame* frame);
	~VScreenMainMenue();

	void onNotify(IViewUIObserver::Event events);
	
};

NAMESPACE_VIEW_E
