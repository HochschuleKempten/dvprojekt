#pragma once

#include "Material.h"

//------------------------------------
// CMaterials, Pluralklasse von CMaterial
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{
	class CHardware;

class CMaterials
{
public:
	CMaterials();
	~CMaterials();
	CMaterials operator=(CMaterials materials);

	void Init();
	void Tick(float & fTimeDelta, CHardware & m_zh);
	void Fini();
	
	bool Add(CMaterial * pmaterial); // Trägt Material in die Liste ein
	bool AddOnce(CMaterial * pmaterial); // Trägt Material nur dann in die Liste ein, wenn noch nicht vorhanden
	bool Sub(CMaterial * pmaterial);

	bool Has(CMaterial * pmaterial);
	CMaterial * Make(CColor colorDiffuse, CColor colorAmbient, CColor colorSpecular);
	bool Kill(CMaterial * pmaterial);

	CMaterial ** m_apmaterial;
	int m_iMaterialAllocs;
	int m_iAllocBlock;
	int m_iMaterials;
};

}