#pragma once

namespace Vektoria
{

class CFloatRect
{
public:
	CFloatRect();
	CFloatRect(float fxPos, float fyPos, float fxSize, float fySize); // Konstuktor mit fxPos = linker x-Wert, fyPos = oberer y-Wert, fxSize = Breite, fy-Size = Höhe 
	CFloatRect operator=(CFloatRect & floatrect);
	void Copy(CFloatRect & floatrect);


	/*
	CFloatRect operator+(float f); // Addition
	CFloatRect operator-(float f); // Subtraktion
	CFloatRect operator+=(float f); // Addition -Schnelloperator
	CFloatRect operator-=(float f); // Subtraktion -Schnelloperator
	float operator*(float f); // Skalarprodukt
	float operator/(float f); // Skalardivision
	*/

	CFloatRect operator*(CFloatRect & floatrect); // Produkt

	void Init(float fxPos, float fyPos, float fxSize, float fySize); // Re-Initialisierung mit fxPos = linker x-Wert, fyPos = oberer y-Wert, fxSize = Breite, fy-Size = Höhe 
	void Fini();

	bool IsBetweenX(float fx); // gibt true aus, falls sich fx zwischen linker und rechter Kante befindet (ausschleißlich Kante)
	bool IsBetweenY(float fy); // gibt true aus, falls sich fy zwischen oberer und unterer Kante befindet (ausschleißlich Kante)
	bool IsBetween(float fx, float fy); // Gibt true aus, wenn der Punkt P=(fx,fy) im Rechteck ist, ansonsten false (ausschleißlich Kante)
	bool IsInnerX(float fx); // gibt true aus, falls sich fx zwischen linker und rechter Kante befindet (einschleißlich Kante)
	bool IsInnerY(float fy); // gibt true aus, falls sich fy zwischen oberer und unterer Kante befindet (einschleißlich Kante)
	bool IsInner(float fx, float fy); // Gibt true aus, wenn der Punkt P=(fx,fy) im Rechteck ist, ansonsten false (einschleißlich Kante)

	float GetDistLeft(CFloatRect & floatrect); // gibt Zwischendistanz des Parameter-Floatrects von der linken Kante aus
	float GetDistRight(CFloatRect & floatrect); // gibt Zwischenddistanz des Parameter-Floatrects von der rechten Kante aus
	float GetDistTop(CFloatRect & floatrect); // gibt Zwischenddistanz des Parameter-Floatrects von der oberen Kante aus
	float GetDistBottom(CFloatRect & floatrect); // gibt Zwischenddistanz des Parameter-Floatrects von der unteren Kante aus

	bool Collides(CFloatRect & floatrect);

	bool TouchesLeft(CFloatRect & floatrect); // gibt true aus, falls Parameter-Floatrect das Klassenfloatrect von links berührt (kann mit Komma-Ungenauigkeiten umgehen)
	bool TouchesRight(CFloatRect & floatrect); // gibt true aus, falls Parameter-Floatrect das Klassenfloatrect von rechts berührt (kann mit Komma-Ungenauigkeiten umgehen)
	bool TouchesTop(CFloatRect & floatrect); // gibt true aus, falls Parameter-Floatrect das Klassenfloatrect von oben berührt (kann mit Komma-Ungenauigkeiten umgehen)
	bool TouchesBottom(CFloatRect & floatrect); // gibt true aus, falls Parameter-Floatrect das Klassenfloatrect von unten berührt (kann mit Komma-Ungenauigkeiten umgehen)


	void Clip(); // Schneidet Ränder des Rechtecks dergestalt ab, dass sie alle zwischen Null und Eins liegen

	void SetXPos(float fxPos); // Setzt linken X-Wert
	void SetYPos(float fyPos);  // Setzt linken Y-Wert
	void SetXSize(float fxSize); // Setzt Breite
	void SetYSize(float fySize);  // Setzt Höhe

	float GetXPos(); // Holt linken X-Wert
	float GetYPos();  // Holt linken Y-Wert
	float GetXMid(); // Gibt die Mitte in X-Richtung aus
	float GetYMid();  // Gibt die Mitte in X-Richtung aus
	float GetXSize(); // Holt Breite
	float GetYSize();  // Holt Höhe
	float GetRight(); // gibt die rechte X-Position aus
	float GetBottom(); // gibt die untere Y-Position aus
	float GetRatio(); // gibt das Verhältnis zwischen Breite und Höhe aus

	void Scale(float f); // Skaliert Rechteck ausgehend vom Ursprung um den Betrag f in x- und y-Reichtung
	void ScaleFromBottom(float f); // Skaliert Rechteck um den Betrag f in x- und y-Reichtung, aber lässt untere Kante auf gleichem Level (Rechteck wird hochgezogen)
	void Scale(float fx, float fy); // Skaliert Rechteck ausgehend vom Ursprung
	void ScaleFromBottom(float fx, float fy); // Skaliert Rechteck, aber lässt untere Kante auf gleichem Level (Rechteck wird hochgezogen)
	void Translate(float fx, float fy); // Verschiebt Rechteck um den Vektor(fx,fy)

	float m_fxPos;
	float m_fyPos;
	float m_fxSize;
	float m_fySize;
};

}