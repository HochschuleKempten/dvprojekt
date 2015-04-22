#pragma once
#include "Node3D.h"
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "Material.h"

//---------------------------------------------------
// CEmitter: einfacher CPU-basierter Partikelemitter
//
// Autor: Tobias Breiner
//---------------------------------------------------

namespace Vektoria
{

class CPlacements;
class CApiRender;
class CGeo;
class CTimer;

enum EEmitterShape
{
	eEmitterShape_Conical,
	eEmitterShape_Radial,
	eEmitterShape_Planar,
	eEmitterShape_Linear
};



class CEmitter : public CNode3D
{
public:
	CEmitter();
	~CEmitter();
	CEmitter operator=(CEmitter & emitter);
	void Copy(CEmitter & emitter);

	void InitConical(float faCone, EAxis eAxis = eAxisZ);
	void InitRadial();
	void InitPlanar(float fxSize, float fySize, EAxis eAxis = eAxisY);
	void InitLinear(float fSize, EAxis eAxis = eAxisZ);

	void Tick(CHMat & m, bool & bTick);
	void Fini();

	void Draw(CHMat & mGlobal );

	virtual void UpdateAABB();
	
	EEmitterShape m_eEmitterShape;
	float m_faCone; 
	float m_fxSize;
	float m_fySize;
	float m_fSize;

};

}