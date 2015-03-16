#pragma once
#include "Light.h"

//---------------------------------------------------
// CPointLight: Klasse f�r Punktlichter
//
// Autoren: Prof. Dr. Tobias Breiner, Florian Schnell
// Letzte �nderung: 2011-02-22
//---------------------------------------------------

namespace Vektoria
{

class CPointLight : public CLight
{
public:
	CPointLight();
	~CPointLight();
	CPointLight operator=(CPointLight & pointlight);
	void Copy(CPointLight & pointlight);

	void Init(CColor color);
	void Init(CColor color, float fIntensity);
	void Init();
	void Fini();

	void SetRadius(float fRadius);

	float m_fRadius;
};

}