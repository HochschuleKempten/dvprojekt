#pragma once

namespace Vektoria
{

class CIntRect
{
public:
	CIntRect();
	CIntRect operator=(CIntRect intrect);
	void Copy(CIntRect intrect);

	void Init(int ixPos, int iyPos, int ixSize, int iySize);
	void Tick(float & fTimeDelta);
	void Fini();

	void CommitSuicide(float fTimeToKill);
	bool m_bArrrgh;
	bool m_bCommitSuicide;
	float m_fTimeToKill;

	CIntRect * m_pintrectPrev;
	CIntRect * m_pintrectNext;
	int m_ixPos;
	int m_iyPos;
	int m_ixSize;
	int m_iySize;
};

}