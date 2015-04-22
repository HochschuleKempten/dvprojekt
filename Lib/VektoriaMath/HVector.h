#pragma once

// #include "Vector3.h"

//---------------------------------------------------
// CHVector: Klasse für homogene Vektoren
//
// Autoren: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2012-06-05
//---------------------------------------------------

namespace Vektoria
{

enum EAxis
{
	eAxisX = 0,
	eAxisY,
	eAxisZ
};

class CHVector
{
public:
	CHVector(); // Konstruktor 1 (alle Werte auf Null)
	CHVector(float fx, float fy, float fz, float fw); // Konstruktor 2 (alle Werte werden dediziert übergeben)
	CHVector(float fx, float fy, float fz); // Konstruktor 3 (x,y und z-Position werden angegeben, letzter homogener Wert wird auf Eins gesetzt)
	CHVector(EAxis eAxis); // Konstruktor 4 (Erzegt angegebenen Axenrichtungsvektor, letzter Wert wird auf Null gesetzt)


	CHVector operator=(CHVector & hvector); // Vektorzuweisung
	CHVector operator+(CHVector & hvector); // Vektoraddition
	CHVector operator-(CHVector & hvector); // Vektorsubtraktion
	CHVector operator+=(CHVector & hvector); // Vektoraddition -Schnelloperator
	CHVector operator-=(CHVector & hvector); // Vektorsubtraktion -Schnelloperator
	float operator*(CHVector & hvector); // Skalarprodukt
	float operator/(CHVector & hvector); // Skalardivision
	CHVector operator*(float f); // Skalarprodukt (rechts)
	// friend CHVector operator* (float f, CHVector & hvector); // Skalarprodukt (links)
	CHVector operator/(float f); // Skalardivision (rechts)
	CHVector operator*=(float f); // Vektorskalierung durch Multiplikation -Schnelloperator
	CHVector operator/=(float f); // Vektorskalierung durch Division -Schnelloperator
	bool operator==(CHVector & hvector); // Vergleich zweier Vektoren auf Gleichheit
	bool operator!=(CHVector & hvector); // Vergleich zweier Vektoren auf Ungleichheit
	float operator[] (int iPos); // Gibt Stelle iPos des Vektors aus
	CHVector operator -(void); // Negativzeichen vor Vektor => Minus vor allen Vektorelementen
	CHVector operator +(void); // Positivzeichen vor Vektor => keine Veränderung, trotzdem der mathematisch vollwertigenNotation halber wichtig
 
	CHVector operator^(CHVector & hvector); // Kreuzprodukt

	void Copy(CHVector & hvector);	// kopiert den Vektor

	void Init(float fx, float fy, float fz, float fw); // initialisiert oder überschreibt die Werte des Vektors
	void InitPoint(float fx, float fy, float fz); // initialisiert oder überschreibt die Werte des Vektors, der W-Wert ist Eins um einen Raumpunkt anzuzeigen
	void InitDirection(float fx, float fy, float fz); // initialisiert oder überschreibt die Werte des Vektors, der W-Wert ist Null  um eine Richtung anzuzeigen
	void Null(); // Setzt alle Tupelwerte auf Null
	bool IsNull(); // Gibt true aus, wenn alle Tupelwerte auf Null sind

	CHVector Mid(CHVector & hvector); // ermittelt Vektor, der genau in der Mitte zwischen aktuellem und angegebenen Vektor liegt

	CHVector Min(CHVector & hvector); // erzeugt Vektor aus den jeweils kleineren Tupeln
	CHVector Max(CHVector & hvector); // erzeugt Vektor aus den jeweils größeren Tupeln
	CHVector Project(CHVector &hvector); // projiziert hVector auf this
	CHVector Reject(CHVector &hvector);

	CHVector Normal();	// erzeugt Normalenvektor
	void Norm();	// normiert Vektor 
	void Flip();	// dreht die Richtung des Vektors um
	float Length();	// gibt Betrag (=Länge) des Vektors als Skalar aus
	float LengthSquare();	// gibt den quadrierten Betrag aus
	void MakeDirection();	// macht aus einem Raumpunkt einen Richtungsvektor
	void MakePoint();		// macht aus einem Richtungsvektor einen Raumpunkt
	void Scale(CHVector & v);		// skaliert einen Verktor mit den Werten eines anderen Vectors
    float Dist(CHVector & v);       // berechnet die euklidische Distanz zwischen diesem Vector und einem anderen Vector


	void SetX(float f); // setzt X-Wert
	void SetY(float f); // setzt Y-Wert
	void SetZ(float f); // setzt Z-Wert
	void SetW(float f); // setzt homogenen Wert

	void SetXYZW(float f); // setzt alle Werte auf Wert f
	void SetXYZ(float f); // setzt XYZ-Werte auf Wert f
	void SetXYZ0(float f); // setzt XYZ-Werte auf Wert f, W-Wert auf 0
	void SetXYZ1(float f); // setzt XYZ-Werte auf Wert f, W-Wert auf 0
	void NormalX(); // setzt Vektor auf X-Normale (1,0,0,0)
	void NormalY(); // setzt Vektor auf Y-Normale (0,1,0,0)
	void NormalZ(); // setzt Vektor auf Z-Normale (0,0,1,0)


	float GetX(); // gibt aktuellen X-Wert aus
	float GetY(); // gibt aktuellen Y-Wert aus
	float GetZ(); // gibt aktuellen Z-Wert aus
	float GetW(); // gibt homogenen Wert aus

	float Angle(CHVector & v); // gibt Winkel im Bogenmaß aus, der sich zwischen dem bestehenden Vektor und dem Vector v befindet.
	float AngleXY(); // gibt auf die XY-Ebene projizierten Drehwinkel im Bogenmaß aus (Null entspricht X-Achse);
	float AngleZX(); // gibt auf die XZ-Ebene projizierten Drehwinkel im Bogenmaß aus (Null entspricht Z-Achse);
	float AngleYZ(); // gibt auf die YZ-Ebene projizierten Drehwinkel im Bogenmaß aus (Null entspricht Y-Achse);

	float AngleYX(); // gibt auf die XY-Ebene projizierten Drehwinkel im Bogenmaß aus (Null entspricht Z-Achse);
	float AngleXZ(); // gibt auf die XZ-Ebene projizierten Drehwinkel im Bogenmaß aus (Null entspricht X-Achse);
	float AngleZY(); // gibt auf die YZ-Ebene projizierten Drehwinkel im Bogenmaß aus (Null entspricht Z-Achse);


	union
	{
//		CVector3::h xyz;
		struct
		{
			float m_fx;
			float m_fy;
			float m_fz;
			float m_fw;
		};
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
};

}