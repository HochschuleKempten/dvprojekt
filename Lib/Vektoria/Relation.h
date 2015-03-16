#pragma once

//---------------------------------------------------
// CRelation: Klasse für Verbindungen 
//
// Autoren: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2011-08-07
//---------------------------------------------------

namespace Vektoria
{

class CRelation
{
public:
	CRelation();
	~CRelation();
	CRelation operator=(CRelation relation);
	void Copy(CRelation relation);

	void Init();
	void Tick(float & fTimeDelta);
	void Fini();

	float m_fStrength;
};

}