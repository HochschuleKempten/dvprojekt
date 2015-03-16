#pragma once

#include "Material.h"

//--------------------------------------------------------------------------------------------
// CWritingFont: Klasse f�r Schriftarten (Spezielles Bot-Material mit ASCII-Sortierung)
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte �nderung: 2013-12-05
//--------------------------------------------------------------------------------------------


namespace Vektoria
{

class CWritingFont : public CMaterial 
{
public:
	CWritingFont(); // Konstruktor
	~CWritingFont(); // Destruktor
	CWritingFont operator=(CWritingFont & writing); // Kopieroperator
	void Copy(CWritingFont & writing); // Kopiermethode

	void Init(char * acPath, bool bChromaKeying); // Initialisiert SchriftartMaterial durch Pfadangabe, bChromaKeying setzt chromatischen Farbschl�ssel (Pixel 0,0)
	void Fini(); // Finalisiert Schriftart

	void SetTableSize(int ixTable, int iyTable); // Setzt die Feldgr��e in Buchstaben im �bergebenen ASCII-Feld
	void SetTableStartASCII(int iTableStartASCII); // Setzt den Anfang des �bergebenen ASCII-Feldes

	int m_ixTable;
	int m_iyTable;
	int m_iTableStartASCII;
	bool m_bChromaKeying;
	char m_c;
};

}