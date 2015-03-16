#pragma once
#include "HVector.h"
#include "HMat.h"

//------------------------------------
// CQuaternion
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.12.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CQuaternion
{
public:
	CQuaternion();  
	CQuaternion(float fx, float fy, float fz, float fw);

	CQuaternion operator=(CQuaternion quaternion); // Zuweisung
	void Copy(CQuaternion quaternion); // Kopiert Quaternion

	bool operator==(CHVector & hvector); // Vergleich zweier Quaternionen auf Gleichheit
	bool operator!=(CHVector & hvector); // Vergleich zweier Quaternionen auf Ungleichheit


	CQuaternion operator*(CQuaternion & q); // Quaternionenmultiplikation
	CQuaternion operator+(CQuaternion & q); // Quaternionenaddition
	CQuaternion operator-(CQuaternion & q); // Quaternionensubtraktion

	CQuaternion operator*=(CQuaternion & q); // Quaternionenmultiplikation -Schnelloperator
	CQuaternion operator+=(CQuaternion & q); // Quaternionenaddition -Schnelloperator
	CQuaternion operator-=(CQuaternion & q); // Quaternionensubtraktion -Schnelloperator

	CQuaternion operator*(float f); // Skalarprodukt (Quaternionenskalierung durch Multiplikation, rechts)
	CQuaternion operator/(float f); // Skalardivision (Quaternionenskalierung durch Division, rechts)
	CQuaternion operator*=(float f); // Quaternionenskalierung durch Multiplikation -Schnelloperator
	CQuaternion operator/=(float f); // Quaternionenskalierung durch Division -Schnelloperator
	
	void Init(float fx, float fy, float fz, float fw); // Setzt Quaternion auf angegebene Werte
	void Fini(); // Finalisiert Quaternion (macht zuzeit aber noch gar nix, weils nix zu finalisieren gibt)

	void Conjugate(); // Konjugiert Quaternion
	void Inverse(); // Invertiert Quaternion
	void Norm(); // Normiert Quaternion
	float Length(); // Gibt den Betrag des Quaternions aus

	CHVector ApplyRotation(CHVector & v); // Rotiert Punkt v mit Hilfe des Rotationsquaterions v und gibt Ergebnis als Returnwert aus 

	void RotateX(float fa);		// Generiert Rotationsquaternion um x-Achse mit Winkel fa
	void RotateY(float fa);		// Generiert Rotationsquaternion um y-Achse mit Winkel fa
	void RotateZ(float fa);		// Generiert Rotationsquaternion um z-Achse mit Winkel fa
	void Rotate(float fx, float fy, float fz, float fa); // Generiert beliebiges Rotationsquaternion um die Drehachse fx, fy, fz mit Winkel fa
	void Rotate(CHVector & v, float fa); // Generiert beliebiges Rotationsquaternion um die Drehachse v mit Winkel fa

	void Lerp(CQuaternion qFrom, CQuaternion qTo, float fr); // Lineare Interpolation zwischen zwei Quaternionen
	void Slerp(CQuaternion qFrom, CQuaternion qTo, float fr); // Spherische Interpolation zwischen zwei Quaternionen

	CHVector GetVector(); // holt XYZ und schreibt ihn in den Vektor, der homogene Faktor wird auf 0 gesetzt
	void SetVector(CHVector  & v); // Setzt XYZ des Quaternions auf die Werte des Vektors, w wird auf 0 gesetzt

	CHMat GetMatrix(); // Generiert Rotationsmatrix aus Quaternion und gibt sie aus
	CHMat GetMatrixByNormed(); // Generiert Rotationsmatrix aus einem normierten Quaternion und gibt sie aus, Achtung Quaternion muss normiert sein, sonst kommt hier was falsches raus, dafür ist sie etwas schneller
	void SetMatrix(CHMat & m); // Generiert Quaternion aus der Raotationsmatrix m


	void SetX(float f); // setzt X-Wert
	void SetY(float f); // setzt Y-Wert
	void SetZ(float f); // setzt Z-Wert
	void SetW(float f); // setzt rationalen Wert

	float GetX(); // gibt aktuellen X-Wert aus
	float GetY(); // gibt aktuellen Y-Wert aus
	float GetZ(); // gibt aktuellen Z-Wert aus
	float GetW(); // gibt rationalen Wert aus

	float m_fx;
	float m_fy;
	float m_fz;
	float m_fw;

};

}