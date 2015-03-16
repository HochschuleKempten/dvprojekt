#pragma once

#include "Sprite.h"
#include "Overlay.h"
#include "WritingFont.h"

//--------------------------------------------------------------------------------------------
// CWritingChar: Klasse für Zeichenfelder (spezielle Overlay-Sprites)
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2013-12-05
//--------------------------------------------------------------------------------------------


namespace Vektoria
{

	class CWritingChar : public COverlay
	{
		friend class CWritingChars;
		friend class CWriting;
	protected:
		void Tick(float & fTimeDelta, CFloatRect & floatrectFather); // Wird automatisch jeden Tick aufgerufen, der Programmierer braucht sich normalerweise um diese Methode nicht zu kümmern

	public:
		CWritingChar(); // Konstruktor
		~CWritingChar(); // Destruktor
		CWritingChar operator=(CWritingChar & writing); // Kopieroperator
		void Copy(CWritingChar & writing); // Kopiermethode

		void Init(CFloatRect & floatrect, CWritingFont * pwritingfont); // Initialisiert ein Zeichensprite, floatrect ist die 2D-Größe des Zeichenfeldes,  pwritingfont ein ASCII-Schriftsatzmaterial 
		void Fini(); // Finalisiert Zeichensprite

		void SetChar(char c); // Aktualisiert Zeichensprite
		void SetFont(CWritingFont * pwritingfont); // Aktualisiert Font

		void Draw(); // Wird automatisch aufgerufen

		CWritingFont * m_pwritingfont;
		CApiRender * m_papirender;
		char m_c;
		bool m_bChanged;
	};

}