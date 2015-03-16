#pragma once
#include "Frames.h"

#include "DistributedGlobal.h"



//---------------------------------------------------
// CHardware: Klasse für Rendercomputer und ähnliches, welche in einer Szenengraph-Hierarchie eingebunden werden können 
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2011-08-07
//---------------------------------------------------

namespace Vektoria
{

class CHardware : public CNode
{
	friend class CHardwares;
	friend class CRoot;
private:
	void Tick(float & fTimeDelta, bool & bTickTack);
public:
	CHardware();
	~CHardware();
	CHardware operator=(CHardware hardware);
	void Copy(CHardware hardware);


	void Init(bool bThis);
	void Fini();

	void AddFrame(CFrame * pframe);

	CFrames m_frames;
	bool m_bThis;

	void SetRoot(CRoot * proot);
	CRoot * m_proot;
#ifdef NETWORKMASTER
	unsigned int GetidID();
private:

	unsigned int m_idId;
	int m_icId;
#endif
};

}