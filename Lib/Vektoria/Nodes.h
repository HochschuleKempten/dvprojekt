//------------------------------------
// CNodes, Pluralklasse von CNode
// 
// Autor: Florian Schnell, Prof. Dr. Tobias Breiner
// Kempten, 22.05.2012
//------------------------------------
#pragma once

namespace Vektoria
{

class CNode;

class CNodes
{
public:
	CNodes();
	~CNodes();
	CNodes operator=(CNodes & nodes);

	void Copy(CNodes & nodes);

	void Add(CNode* pnode);
	bool Sub(CNode* pnode);
    
    int GetCount(void);

	CNode** m_apnode;
	int m_iNodeAllocs;
	int m_iAllocBlock;
	int m_iNodes;
};

}