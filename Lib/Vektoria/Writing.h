#pragma once

#include "Sprite.h"
#include "WritingChars.h"
#include <stdio.h>
//--------------------------------------------------------------------------------------------
// CWriting: Klasse für Textfelder (spezielle Overlay-Sprites)
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2013-12-05
//--------------------------------------------------------------------------------------------


namespace Vektoria
{

class CWriting : public COverlay
{
	friend class CWritings;
	friend class COverlays;
protected:
	void Tick(float & fTimeDelta, CFloatRect & floatrectFather);// wird automatisch aufgefufen

public:
	CWriting(); // Konstruktor
	~CWriting(); // Destruktor
	CWriting operator=(CWriting & writing); // Kopieroperator
	void Copy(CWriting & writing); // Kopiermethode

	void Init(CFloatRect & floatrect, int ixChars, CWritingFont * pwritingfont); // Initialisiert ein Textfeldsprite, floatrect ist die 2D-Größe des Textfeldes,  ixChars die maximalanzahl der Buchstaben, pwritingfont ein ASCII-Schriftsatzmaterial 
	void Fini(); // Finalisiert das Textfeldsprite

	void SetFont(CWritingFont * pwritingfont); // Aktualisiert das ASCII-Schriftsatzmaterial
	void SetFont(CWritingFont * pwritingfont, int & iCharStart, int & iCharEnd); // Aktualisiert das ASCII-Schriftsatzmaterial im Buchstabenbereich iCharStart bis iCharStartEnd

	void SetViewport(CViewport * pviewport); // Wird automatisch aufgerufen

	void PrintF(LPCSTR szMsg, ...); // Äquivalent zu "printf" im Konsolenfenster

	void PrintInt(int i); // Schreibt eine Integerzahl 
	void PrintFloat(float f); // Schreibt eine Float-Gleitkommazahl 
	void PrintString(char * ac); // Schreibt einen Text


	char *m_ac;
	CWritingChars m_writingchars;
	int m_ixChars;
};

}