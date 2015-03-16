#pragma once
#include "Material.h"
#include "../VektoriaMath/HVector.h"
#include "Vertex.h"
#include "../VektoriaMath/HMat.h"

namespace Vektoria
{

class CFace
{
public:
	CFace();
	CFace operator=(CFace face);
	void Copy(CFace face);

	void Init(CVertex * pvertexA, CVertex * pvertexB, CVertex * pvertexC);

	CVertex * m_pvertexA;
	CVertex * m_pvertexB;
	CVertex * m_pvertexC;
};

}