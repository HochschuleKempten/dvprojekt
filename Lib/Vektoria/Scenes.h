#pragma once

#include "Scene.h"

//------------------------------------
// CScenes, Pluralklasse von CScene
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 29.03.2012
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CScenes
{
public:
	CScenes();
	~CScenes();
	CScenes operator=(CScenes scenes);

	void Init();
	void Tick(float & fTimeDelta, bool & bTick);
	void Fini();



	void Add(CScene * pscene);
	bool AddOnce(CScene * pscene); // Fügt Szene nur dann in die Liste hinein, wenn sie noch nicht in der Liste eingetragen ist (Verhindert Doppeltabspeicherungen)
	bool Sub(CScene * pscene);
	bool Has(CScene * pscene); // Gibt true aus, wenn Szene in der Liste vorhanden ist

	void Draw(CCamera * pcamera, bool & bTickTack);



	CScene * Make();
	bool Kill(CScene * pscene);

	CScene ** m_apscene;
	int m_iSceneAllocs;
	int m_iAllocBlock;
	int m_iScenes;
	void SetRoot(CRoot * m_proot);
	CRoot * m_proot;
};

}