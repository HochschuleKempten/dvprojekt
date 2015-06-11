#pragma once

#include "Placement.h"
#include <stdio.h>

//--------------------------------------------------------------------------------------------
// CWribel: Klasse für Textlabels (WRIBEL = WRIting + LaBEL)
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2013-12-05
//--------------------------------------------------------------------------------------------


namespace Vektoria
{
	class CWritingFont;

	class CWribel : public CPlacement
	{
		friend class CWribels;
	private:
		void Tick(CHMat & mGlobalFather, float & fTimeDelta, bool & bTick, int & iInst);// Wird automatisch aufgefufen

	public:
		CWribel(); // Konstruktor
		~CWribel(); // Destruktor
		CWribel operator=(CWribel & writing); // Kopieroperator
		void Copy(CWribel & writing); // Kopiermethode

		void Init(CFloatRect & floatrect, int ixChars, CWritingFont * pwritingfont, float fzOffset = 0.0F); // Initialisiert ein Textfeldsprite, floatrect ist die 2D-Größe des Textfeldes,  ixChars die Maximalanzahl der Buchstaben, pwritingfont ein ASCII-Schriftsatzmaterial 
		void Fini(); // Finalisiert das Textfeldsprite

		void SetFont(CWritingFont * pwritingfont); // Aktualisiert das ASCII-Schriftsatzmaterial
		void SetFont(CWritingFont * pwritingfont, int & iCharStart, int & iCharEnd); // Aktualisiert das ASCII-Schriftsatzmaterial im Buchstabenbereich iCharStart bis iCharStartEnd

		void PrintF(LPCSTR szMsg, ...); // Äquivalent zu "printf" im Konsolenfenster

		void PrintInt(int i); // Schreibt eine Integerzahl 
		void PrintFloat(float f); // Schreibt eine Float-Gleichtkommazahl 
		void PrintString(char * ac); // Schreibt einen Text


		char *m_ac;
		int m_ixChars;
		CWritingFont * m_pwritingfont;
	};

}