#pragma once
#include "Sprite.h"
#include "../VektoriaMath/FloatRect.h"

//------------------------------------
// COverlay
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

	class CViewport;
	class COverlays;
	class CWriting;
	class CWritingChar;

	class COverlay : public CSprite
	{
		friend class COverlays;
		friend class CWriting;
		friend class CWritingChar;
		friend class CWritings;
	protected:
		void Tick(float & fTimeDelta, CFloatRect & floatrectFather); // wird automatisch jeden Tick aufgerufen, der Programmierer braucht sich normalerweise um diese Methode nicht zu kümmern

	public:
		COverlay();
		~COverlay();
		COverlay operator=(COverlay & overlay);

		void Fini();

		void AddOverlay(COverlay * poverlay); // Hängt Kind-Overlay an Hierarchie an
		bool SubOverlay(COverlay * poverlay); // Hängt Kind-Overlay von Hierarchie ab, gibt true aus, wenn's geklappt hat

		void AddWriting(CWriting * pwriting); // Hängt ein Unter-Writing-Textfeld an den Overlay an
		bool SubWriting(CWriting * pwriting); // Hängt ein vorhandenes Unter-Writing-Textfeld vom Overlay ab, gibt true aus, wenn's geklappt hat

		void AddWritingChar(CWritingChar * pwritingchar); // Hängt ein Unter-Writing-Buchstabenfeld an den Overlay an
		bool SubWritingChar(CWritingChar * pwritingchar); // Hängt ein vorhandenes Unter-Writing-Buchstabenfeld vom Overlay ab, gibt true aus, wenn's geklappt hat


		void SetBehindOn(); // lässt Overlay hinter Vateroverlay erscheinen
		void SetBehindOff();  // lässt Overlay vor Vateroverlay erscheinen (Default)
		void SetInnerOn(); // lässt Overlay innerhalb vom Vateroverlay erscheinen
		void SetInnerOff();  // lässt Overlay außerhalb vom Vateroverlay (aber trotzdem ausgerichtet an Vaterkoordinaten) erscheinen (Default)


		CApiRender * GetApiRender();
		COverlays * m_poverlays;
		bool m_bBehind;
		bool m_bInner;
		CFloatRect m_floatrectGlobal;
		void SetViewport(CViewport * pviewport);
		CHMat m_mLocal;
		CHMat m_mGlobal;


	};

}