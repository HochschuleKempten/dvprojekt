#pragma once
#include "Sprite.h"

//------------------------------------
// CBackground
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

	class CViewport;

	class CBackground : public CSprite
	{
		friend class CBackgrounds;

	public:
		CBackground();
		~CBackground();
		CBackground operator=(CBackground background);
	protected:
		void Tick(float & fTimeDelta);

	};

}