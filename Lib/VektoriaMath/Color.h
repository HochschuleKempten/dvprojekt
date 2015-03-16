#pragma once

//---------------------------------------------------
// CColor: Klasse für RGB-Farben mit Alpha-Anteil
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2011-08-07
//---------------------------------------------------

namespace Vektoria
{

class CColor
{
public:
	CColor(); // Konstruktor, initialisiert die Farbe schwarz
	CColor(float frR, float frG, float frB); // Konstruktor zur Initialisierung einer Farbe im RGB-System, Alphakanal wird automatisch auf 0 (opak) gesetzt.
	CColor(float frR, float frG, float frB, float frA); // Konstruktor zur Initialisierung einer Farbe im RGB-System

	CColor operator=(CColor & color); // Kopieroperation
	void Copy(CColor & color); // Kopiert eine Farbe
	void CopyWithoutAlpha(CColor & color); // Kopiert eine Farbe, belässt aber den Alpha-Wert

	void Init(float frR, float frG, float frB, float frA);		// Initalisiert die Farbe im RGB+Alpha-System
	void Fini(); // Finalisiert die Farbe (macht noch nicht, nur der Vollständigkeit halber)

	void Invert();												// Invertiert die Farbe
	void Interpol(CColor & colorFrom, CColor & colorTo, float fr);  // interpoliert 2 Farben, fr ist der Laufparameter, der von 0 bis 1 geht
	void GetHSV(float & frH, float & frS, float & frV);			// RGB -> HSV ; gibt die Farbe im HSV-System aus 
	void SetHSV(float frH, float frS, float frV);				// HSV -> RGB ; Setzt die Farbe durch HSV-Systemwerte 
	void GetCMY(float & frC, float & frM, float & frY);			// RGB -> CMY ; gibt die Farbe im CMY-System aus 
	void SetCMY(float frC, float frM, float frY);				// CMY -> RGB ; Setzt die Farbe durch CMY-Systemwerte 

	float m_frR; // Rotanteil 0..1
	float m_frG; // Grünanteil 0..1
	float m_frB; // Blauanteil 0..1
	float m_frA; // Alpha-Anteil 0..1 0=opak, 1=transparent
};

}