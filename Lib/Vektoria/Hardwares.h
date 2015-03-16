#pragma once
#include "Hardware.h"

//------------------------------------
// CHardwares, Pluralklasse von CHardware
// 
// Autor: Prof. Dr. Tobias Breiner
// Pfungstadt, 11.10.2011
//------------------------------------

namespace Vektoria
{

class CHardwares
{
public:
	CHardwares();
	~CHardwares();
	CHardwares operator=(CHardwares hardwares);


	void Init();
	void Tick(float & fTimeDelta, bool & bTickTack);
	void Fini();

	void Add(CHardware * phardware);
	bool Sub(CHardware * phardware);

	CHardware * Make(bool bThis);
	bool Kill(CHardware * phardware);

	CHardware ** m_aphardware;
	int m_iHardwareAllocs;
	int m_iAllocBlock;
	int m_iHardwares;

	void SetRoot(CRoot * proot);
	CRoot * m_proot;
};

}