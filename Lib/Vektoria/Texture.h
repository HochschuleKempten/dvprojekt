#pragma once
#include "Image.h"
#include "Node.h"

//--------------------------------------------------------------------------------------------
// CTexture: Klasse für Texturen
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2011-08-07
//--------------------------------------------------------------------------------------------


#define S_TEXTURE_DIFFUSE 0
#define S_TEXTURE_GLOW 1
#define S_TEXTURE_SPECULAR 2
#define S_TEXTURE_BUMP 3
#define S_TEXTURE_HEIGHT 4
#define S_TEXTURE_ENVIROMENTAL 5
#define S_TEXTURE_LIGHT 6
#define S_TEXTURE_THICKNESS 7

namespace Vektoria
{

class CTexture : public CNode
{
	friend class CTextures;
protected:
	void Tick(float & fTimeDelta);

public:
	CTexture();
	~CTexture();
	CTexture operator=(CTexture & texture);
	void Copy(CTexture & texture);

	void Init(CImage * pimage, int eKind = 0);
	void Fini();

	int m_eKind;
	CImage * m_pimage;
};

}