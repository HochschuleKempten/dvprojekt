#pragma once

class ILBuilding
{
private:
	const int costs;
	//todo: Sp�ter max. Ausbaustufe und aktuelle

public:
	virtual int getCosts() = 0;
};

