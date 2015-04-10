#include "Vektoria\Root.h"
#include "VektoriaMath\Util.h"

using namespace Vektoria;

class CTextureTester
{
public:
	CTextureTester(void);
	~CTextureTester(void);

	void Init(CScene *m_pScene);

private:
	CGeoWall m_zgWall1;
	CGeoWall m_zgWall2;
	CGeoWall m_zgWall3;
	CGeoWall m_zgWall4;

	CMaterial m_zmWall;
	CPlacement m_zpWall1;
	CPlacement m_zpWall2;
	CPlacement m_zpWall3;
	CPlacement m_zpWall4;
};