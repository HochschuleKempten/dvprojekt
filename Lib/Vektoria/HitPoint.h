#pragma once
#include "Geo.h"


//------------------------------------
// CHitPoint
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.05.2015
// Copyright: Moyzelle Vektoria
//------------------------------------
namespace Vektoria
{


	class CHitPoint
	{
	public:
		CHitPoint();
		~CHitPoint();
		CHitPoint operator=(CHitPoint & hitpoint);
		void Copy(CHitPoint & hitpoint);

		void Init();
		void Fini();


		CGeo * m_pzg;
		int m_iMatGlobal;
		CHVector m_vPos;
		CHVector m_vNormal;
		float m_fDistanceSquare;

	};

}