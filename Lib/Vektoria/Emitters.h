#pragma once

#include "Emitter.h"

//------------------------------------
// CEmitters, Pluralklasse von CEmitter
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CEmitters
{
public:
	CEmitters();
	~CEmitters();
	CEmitters operator=(CEmitters emitters);

	void Init();
	void Tick(CHMat & m, bool & bTick);
	void Fini();

	void Add(CEmitter * pemitter);
	bool Sub(CEmitter * pemitter);

	CEmitter * Make(CPlacements * pplacements);
	bool Kill(CEmitter * pemitter);

	void Draw(CHMat & mGlobal);

	CEmitter ** m_apemitter;
	int m_iEmitterAllocs;
	int m_iAllocBlock;
	int m_iEmitters;
};

}