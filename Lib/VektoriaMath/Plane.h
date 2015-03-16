#pragma once
#include "HVector.h"
#include "HVector.h"
#include "HVector.h"
#include "Ray.h"

//------------------------------------
// CPlane
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 03.09.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CPlane
{
public:
	CPlane(); // Konstruktor ohne initialisierung
	CPlane(CHVector * pvA, CHVector * pvB, CHVector * pvC); // Initialisiert eine Ebene durch die Angabe dreier Punkte
	CPlane(CHVector & vPoint, CHVector & vNormal); // (Re-)initialisiert eine Ebene durch die Angabe eines Punktes plus Normalenvektor
	~CPlane();
	CPlane operator=(CPlane & plane); // Kopieroperator
	void Copy(CPlane & plane); // Kopierfunktion

	void Init(CHVector * pvA, CHVector * pvB, CHVector * pvC); // (Re-)initialisiert eine Ebene durch die Angabe dreier Punkte
	void Init(CHVector & vPoint, CHVector & vNormal); // (Re-)initialisiert eine Ebene durch die Angabe eines Punktes plus Normalenvektor
	void Fini();

	float Angle(CPlane & plane); // Berechnet den Schnittwinkel zwischen zwei Ebenen
	CRay Intersect(CPlane & plane); // Berechnet die Schnittgerade zweier Ebenen
	CHVector Intersect(CPlane & plane2, CPlane & plane3); // Berechnet den Schnittpunkt dreier Ebenen
	CHVector Intersect(CRay & ray); // Berechnet Schnittpunkt eines Strahls mit der Ebene // noch ungetestet
	void Move(float f); // Transliert entlang der Normalen
	bool IsFront(CHVector & v); // true, wenn v vor der Ebene liegt, false ansonsten
	bool IsIn(CHVector & v); // true, wenn v in der Ebene liegt, false ansonsten
	bool IsBack(CHVector & v); // true, wenn v hinter der Ebene liegt, false ansonsten
	float GetD(); // Gibt D-Parameter der Ebene aus
	CHVector GetNormal(); // rechnet Normale der Ebene aus
	float Distance(CHVector & v); // gibt die Entfernung des angegebenen Punktes zur Ebene aus, liegt Punkt hinter der Ebene, wird der Wert negativ

	float m_fx;
	float m_fy;
	float m_fz;
	float m_fd;
};

}