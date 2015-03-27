#pragma once

class ILBuilding
{
private:
	const int costs;
	//todo: Später max. Ausbaustufe und aktuelle

public:
	virtual int getCosts() = 0;
};

