#pragma once
#include "Plane.h"
#include "Ray.h"
#include "AABB.h"

//------------------------------------
// CFrustum
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 17.07.2014
// Copyright: Vektoria
//------------------------------------

namespace Vektoria
{

class CFrustum
{
public:
	CFrustum(); // Erzeugt Pyramidenstumpf ohne Initialisierung
	CFrustum(CRay r, CHVector vNormalRight, float faHorizontal, float faVertical); // Initialisiert Pyramidenstumpf
	~CFrustum();
	CFrustum operator=(CFrustum & frustum);
	void Copy(CFrustum & frustum);

	void Init(CRay r, CHVector vNormalRight, float faHorizontal, float faVertical); // Re-Initialisiert Pyramidenstumpf
	void Fini();

	bool IsInside(CHVector & v); // Gibt true aus, wenn Punkt innerhalb des Pyramidenstumpfes liegt, ansonsten false
	bool IsInside(CHVector & v, int * aiPlane); // Gibt true aus, wenn Punkt innerhalb des Pyramidenstumpfes liegt, ansonsten false
	int IsInside(CAABB & aabb); // Gibt -1 aus, wenn Box komplett außerhalb des Pyramidenstumpfes liegt, 0 fals halb drin, haln draußen, 1 fall komplett drinnen


	CRay m_r; // Strahl, der durch die Mitte des Pyramidenstumpfes führt 
	float m_faHorizontal; // Halber horizontaler Öffnungswinkel des Pyramidenstumpfes
	float m_faVertical; // Halber vertikaler Öffnungswinkel des Pyramidenstumpfes
	CHVector m_vNormalRight; // Normalenvektor der die rechte Richtung representiert
	CHVector m_vNormalUp; // Normalenvektor der die Aufwärtsrichtung representiert

	CHVector GetCenter(); // Gibt die Mitte des Frustrums aus

	CPlane m_planeFront; // Vorderseite
	CPlane m_planeBack;  // Hinterseite
	CPlane m_planeLeft; // Linke Seite
	CPlane m_planeRight; // Rechte seite
	CPlane m_planeTop; // Oberseite
	CPlane m_planeBottom; // Unterseite

	CPlane m_planeHorizontal; // Hozizontale Schnittebene entlang der Sichtachse(Braucht man nicht unbedingt, beschleunigt aber einige Rechenoperationen)
	CPlane m_planeVertical; // Vertikale Schnittebene  entlang der Sichtachse(Braucht man nicht unbedingt, beschleunigt aber einige Rechenoperationen)

};

}
