//------------------------------------
// CSprite: Basisklasse für Backgrounds, Overlays und damit indirekt Writings und WritingChars
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

#pragma once
#include "Texture.h"
#include "../VektoriaMath/FloatRect.h"
#include "GeoQuad.h"
#include "image.h"


namespace Vektoria
{

#define SKINDSPRITE_N 0
#define SKINDSPRITE_B 1
#define SKINDSPRITE_O 2
#define SKINDSPRITE_W 3
#define SKINDSPRITE_WS 4


	class CSprite : public CNode
	{
	public:
		CSprite(void);
		~CSprite(void);

		void Copy(CSprite & sprite);

		void SetLayer(float fLayerDistance); // gibt den virtuellen "Abstand" des Layers vom Beobachter an
		float GetLayer(); // erfrägt den virtuellen "Abstand" des Layers vom Beobachter

		void Init(char * acPath, CFloatRect & floatrect, bool bChromaKeying = false);
		void Init(CImage * pimage, CFloatRect & floatrect, bool bChromaKeying = false);
		void Init(CMaterial * pmaterial, CFloatRect & floatrect);
		void InitFull(char * acPath, bool bChromaKeying = false);
		void InitFull(CImage * pimage, bool bChromaKeying = false);
		void InitFull(CMaterial * pmaterial);
		void Tick();
		void Fini();

		void SetViewport(CViewport * pviewport);
		void SetTransparency(float frTransparency);
		void SetMaterial(CMaterial * pmaterial);

		void SetRect(CFloatRect & floatrect);
		CFloatRect GetRect();


		void Rotate(float fa);


		CImage * m_pimage;
		CTexture * m_ptexture;
		CMaterial * m_pmaterial;

		CFloatRect m_floatrect;
		CViewport * m_pviewport;
		int m_eKindSprite;
		float m_fLayer; 
	protected:
		bool m_bRotate;
		SRenderObjectHandle m_handle;
		CGeoQuad m_geoquad;
		bool m_bMaterialAddedToRoot;
		bool m_bFirstTick;
		float m_fa;
		int m_iRenderKind;

	};

}