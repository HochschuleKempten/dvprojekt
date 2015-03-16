#pragma once

#include "Image.h"

//------------------------------------
// CImages, Pluralklasse von CImage
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CImages
{
public:
	CImages();
	~CImages();
	CImages operator=(CImages & images);

	void Init();
	void Tick(float & fTimeDelta);
	void Fini();

	void Add(CImage * pimage);
	bool Sub(CImage * pimage);

	CImage * Make(char * acPath);
	bool Kill(CImage * pimage);

	CImage ** m_apimage;
	int m_iImageAllocs;
	int m_iAllocBlock;
	int m_iImages;
};

}