#pragma once

#include "Relation.h"

//------------------------------------
// CRelations, Pluralklasse von CRelation
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CRelations
{
public:
	CRelations();
	~CRelations();
	CRelations operator=(CRelations relations);

	void Init();
	void Tick(float & fTimeDelta);
	void Fini();

	void Add(CRelation * prelation);
	bool Sub(CRelation * prelation);

	CRelation * Make();
	bool Kill(CRelation * prelation);

	CRelation ** m_aprelation;
	int m_iRelationAllocs;
	int m_iAllocBlock;
	int m_iRelations;
};

}