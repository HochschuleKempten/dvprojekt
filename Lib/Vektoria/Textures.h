#pragma once

#include "Texture.h"

//------------------------------------
// CTextures, Pluralklasse von CTexture
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CTextures
{
public:
	CTextures();
	~CTextures();
	CTextures operator=(CTextures textures);

	void Init();
	void Tick(float & fTimeDelta);
	void Fini();

	void Add(CTexture * ptexture);
	bool Sub(CTexture * ptexture);

	CTexture * Make(CImage * pimage);
	bool Kill(CTexture * ptexture);

	CTexture ** m_aptexture;
	int m_iTextureAllocs;
	int m_iAllocBlock;
	int m_iTextures;
};

}