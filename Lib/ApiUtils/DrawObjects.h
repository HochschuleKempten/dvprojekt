#pragma once

#include "DrawObject.h"

//------------------------------------
// CDrawObjects, Pluralklasse von CDrawObject ACHTUNG! Diese Pluralklasse muzss sich anders verhalten, als die anderen, da sie ständig überschrieben wird, Objekte werden zusätzlich als Instanzen verwaltet 
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{



	class CDrawObjects
	{
	public:
		CDrawObjects();  
		~CDrawObjects();
		CDrawObjects operator=(CDrawObjects & drawobjects);

		void Init(bool bSortable);
		void Tick(float & fTimeDelta);
		void Fini();

	//	void Add(CDrawObject * pdrawobject);
		void AddOver(SRenderObjectHandle & handle, int & idTexture, float & fDistanceToCameraSquare, CHMat & mGlobal, unsigned int * aiLightsAffectIndices, unsigned int & iLightsAffectCount);
// 		bool Sub(CDrawObject * pdrawobject);

		void Sort();
//		void Draw(bool bWithMaterials);


		CDrawObject ** m_apdrawobject;
		CDrawObject ** m_apdrawobjectHelp;

		int m_iDrawObjectAllocs;
		int m_iAllocBlock;
		int m_iDrawObjects;

		bool m_bSortable;

	private:
		CDrawObject * m_adrawobject; // sollte private sein, da man nur viw apdrawobject zugreifen sollte
	//	CDrawObject m_adrawobject[50000]; // sollte private sein, da man nur viw apdrawobject zugreifen sollte
		void Mergesort(CDrawObject * adrawobject, unsigned int iStart, unsigned int iEnd); // urspüngliches Mergesort
		void MergesortAddress(CDrawObject ** apdrawobject, unsigned int iStart, unsigned int iEnd); // Test mit reiner Adresssortierung

	};

}