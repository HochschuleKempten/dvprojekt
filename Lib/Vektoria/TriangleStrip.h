#pragma once

#include "Geo.h"
#include "Light.h"
#include "TriangleList.h"

#define INDEX_INCREASE 1024

namespace Vektoria
{



class CTriangleStrip : public CGeo
{
	friend class CTriangleStrips;
	friend class CNode3D;

private:
//	void SetRoot(CRoot * proot);
	void Tick(CHMat & m, bool & bTick);

public:
	CTriangleStrip();
	~CTriangleStrip();

	void Init();
	void Fini();

	void Draw(float fDistanceToCameraSquare, CHMat & mGlobal);
	void Update();

	void AddIndex(int iIndex);

	int * m_aiIndex;
	int m_iIndices;
	int m_iIndicesAllocated;

	bool m_bFirstDraw;
	int m_iRenderKind;

	void Flip(); // Vertauscht Vertexreihenfolge und dreht Normalen- und Tangentenvektor um 180 Grad
	void FlipSpin(); // Vertauscht Vertexreihenfolge, lässt aber anders als Flip den Normalen- und Tangentenvektor unbeeinflusst (wichtig für die korrekte Anzeige nach Spiegelungen)

	CTriangleList * CopyToTriangleList(); // Gibt eine dem TriangleStrip äquivalente TriangleList aus
	void EstimateTangentsAndBinormals(); // Versucht, die Tangenten und die Binormalen für das Bumpmapping aus den gegebenen UV-Koordianten zu erraten  

	bool Intersects(CRay & r, CHVector & vIntersection, float & fDistanceSquare, int & iMatGlobal); // berechnet, ob Strahl r irgendein Dreieck der Geometrie trifft, vIntersection ist dann der Schnittpunkt (nicht unbedingt der Nächste nd nicht unbedingt derjenige der zum Betrachter zeigt!)
	CHitPoint * Intersects(CRay & r); // berechnet, ob Strahl r ein Dreieck der Geometrie trifft, CHitpoint ist dann der Schnittpunkt
	bool IsIntersecting(CRay & r); // berechnet, ob Strahl r ein Dreieck der Geometrie trifft, gibt true aus, wenn ja

private:
	void AddIndexFirst(int iIndex);
};

}