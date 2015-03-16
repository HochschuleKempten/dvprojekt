#pragma once
#include "Camera.h"

//------------------------------------------------------------------
// CCameras: Pluralklasse für Kameras
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2011-08-07
//-------------------------------------------------------------------

namespace Vektoria
{

class CCameras
{
public:
	CCameras();
	~CCameras();
	CCameras operator=(CCameras cameras);

	void Init();
	void Tick(CHMat & m, bool & bTick);
	void Fini();

	void Add(CCamera * pcamera);
	bool Sub(CCamera * pcamera);

	bool Has(CCamera * pcamera); // gibt true aus, wen Camera in der Liste enthalten

	CCamera * Make(float faFov, float fNearClipping, float fFarClipping);
	bool Kill(CCamera * pcamera);

	CCamera ** m_apcamera;
	int m_iCameraAllocs;
	int m_iAllocBlock;
	int m_iCameras;
};

}