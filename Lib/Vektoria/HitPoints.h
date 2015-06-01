#pragma once

#include "HitPoint.h"

//------------------------------------
// CHitPoints, Pluralklasse von CHitPoint
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{


	class CHitPoints
	{
	public:
		CHitPoints();
		~CHitPoints();
		CHitPoints operator=(CHitPoints hitpoints);

		void Init();
		void Fini();

		void Add(CHitPoint * phitpoint);
		bool Sub(CHitPoint * phitpoint);
		void Clear();

		// void AddOnce(CHitPoint * phitpoint);
				
		CHitPoint * GetNearest();


		CHitPoint * Make();
		bool Kill(CHitPoint * phitpoint);

		CHitPoint ** m_aphitpoint;
		int m_iHitPointAllocs;
		int m_iAllocBlock;
		int m_iHitPoints;
	};

}