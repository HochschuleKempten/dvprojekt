#pragma once
#include "TriangleStrip.h"
#include "../VektoriaMath/FloatRect.h"
#include "../VektoriaMath/HMat.h"

namespace Vektoria
{

class CGeoQuad :
	public CTriangleStrip
{
public:
	CGeoQuad(void);
	~CGeoQuad(void);
    const char* ClassName() { return "CGeoQuad"; }

	void SetAxis(EAxis eAxis);

	void Init(float fxSize, float fySize, CMaterial * pmaterial, float fuStart = 0, float fvStart = 0, float fUEnd = 1, float fVEnd = 1); // Initialisiert eine Rechteckige planare Geometrie 
	void InitForSprites(CFloatRect & floatrect, CMaterial * pmaterial); // Initialisiert eine Rechteckige planare Geometrie 

	CVertex m_avertex[4];
	EAxis m_eAxis;
};

}