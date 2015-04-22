#pragma once

class CTextSprite
{
public:
	CTextSprite();
	~CTextSprite();
	CTextSprite operator=(CTextSprite textsprite);
	void Copy(CTextSprite textsprite);

	void Init(char * ac);
	void Tick(float & fTimeDelta);
	void Fini();

	void CommitSuicide(float fTimeToKill);
	bool m_bArrrgh;
	bool m_bCommitSuicide;
	float m_fTimeToKill;

	CTextSprite * m_ptextspritePrev;
	CTextSprite * m_ptextspriteNext;
	char m_ac[265];
};
