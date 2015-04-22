#pragma once
#include "TextSprite.h"

class CTextSprites
{
public:
	CTextSprites();
	~CTextSprites();
	CTextSprites operator=(CTextSprites textsprites);

	void Init();
	void Tick(float & fTimeDelta);
	void Fini();

	CTextSprite * Make(char * ac);
	void Kill(CTextSprite * ptextsprite);

	CTextSprite * m_ptextspriteFirst;
	CTextSprite * m_ptextspriteLast;
	int m_iTextSprites;
};
