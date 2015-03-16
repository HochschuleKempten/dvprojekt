#pragma once

#include "Vertex.h"

//------------------------------------
// CVertexs, Pluralklasse von CVertex
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CVertexs
{
public:
	CVertexs();
	~CVertexs();
	CVertexs operator=(CVertexs vertexs);

	void CopyHierarchy(CVertexs vertexs);

	void Init();
	void Tick(float & fTimeDelta);
	void Fini();

	void Add(CVertex * pvertex);
	bool Sub(CVertex * pvertex);

	CVertex CalcMid(); // Mittelt alle Werte aller Vertices und gibt sie aus

	void SetPos(CHVector & v); // Setzt die Positionen in allen Vertices auf den Wert v
	void SetNormal(CHVector & v); // Setzt die Normalenvektoren in allen Vertices auf den Wert v
	void SetTangent(CHVector & v); // Setzt die Tangentenvektoren in allen Vertices auf den Wert v
	void SetBitangent(CHVector & v); // Setzt die Bitangentenvektoren in allen Vertices auf den Wert v
	void Transform(CHMat & m); // Transformiert alle Vertices mit der Matrix m


//	bool SubRange(int iFrom, int iTo); TODO

	void AddFirst(CVertex * pvertex);


	CVertex * Make(CHVector vPos, CHVector vNormal, CHVector vTangent, float fU=0, float fV=0);
	bool Kill(CVertex * pvertex);

	CVertex ** m_apvertex;
	int m_iVertexAllocs;
	int m_iAllocBlock;
	int m_iVertexs;
};

}