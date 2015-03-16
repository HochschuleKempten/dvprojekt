#pragma once
#include "Light.h"
#include "../VektoriaMath/HVector.h"

#include "DistributedGlobal.h"

namespace Vektoria
{

class CParallelLight : public CLight
{
public:
	CParallelLight();
	~CParallelLight();
	CParallelLight operator=(CParallelLight & parallellight);
	void Copy(CParallelLight & parallellight);

	void Init(CHVector vDirection, CColor color);
	void Fini();

	CHVector m_vDirection;
#ifdef NETWORKMASTER
	unsigned int GetidId();
private:
	unsigned int m_idId;
	int m_icId;
#endif
};

}