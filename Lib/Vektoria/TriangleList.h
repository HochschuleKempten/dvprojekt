#pragma once

#include "Geo.h"
#include "Light.h"

namespace Vektoria
{

class CTriangleList : public CGeo
{
	friend class CTriangleLists;
	friend class CGeoWalls;
	friend class CGeoWall;
	friend class CGeoWing;
	friend class CNode;
	friend class CNode3D;
	friend class CGeos;
	friend class CGeo;
private:
	void Tick(CHMat & m, bool & bTick);
//	void SetRoot(CRoot * proot);

public:
	CTriangleList();
	~CTriangleList();

	void Init();
	void Fini();

	void CopyVertices(CTriangleList & trianglelist); // Kopiert Vertices der übergebenen trianglelist in die aktuelle hinein (nur Pointerliste)
	void CopyHierarchy(CTriangleList & trianglelist); // Kopiert Parameter, Vertices und erzeugt dabei auch neue Kopien der Vertices

	void Flip();		// Vertauscht Vertexreihenfolge und dreht Normalen- und Tangentenvektor um 180 Grad
	void FlipSpin();	// Vertauscht Vertexreihenfolge, lässt aber anders als Flip den Normalen- und Tangentenvektor unbeeinflusst (wichtig für die korrekte Anzeige nach Spiegelungen)	CTriangleList * Subdivide(float fLengthMax);

	void FlattenFaces(); // Macht jedes Polygon flach, indem die Normalenvektoren senkrecht zur Fläche ausgerichtet werden

	void Subdivide(float fLengthMax);  // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abhängig von der maximalen Kantenlänge fLengthMax
	void SubdivideX(float fLengthMax); // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abhängig von der maximalen Kantenbreite fLengthMax in X-Richtung
	void SubdivideY(float fLengthMax); // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abhängig von der maximalen Kantenhöhe fLengthMax in Y-Richtung
	void SubdivideZ(float fLengthMax); // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abhängig von der maximalen Kantentiefe fLengthMax in Z-Richtung

	CTriangleList * ExtractSubdivition(float fLengthMax); // Extrahiert Subdivision-Mesh mit mehr Polygonen aus dem aktuellen Mesh, abhängig von der maximalen Kantenlänge fLengthMax
	CTriangleList * ExtractSubdivitionX(float fLengthMax);// Extrahiert Subdivision-Mesh mit mehr Polygonen aus dem aktuellen Mesh, abhängig von der maximalen Kantenbreite fLengthMax in X-Richtung
	CTriangleList * ExtractSubdivitionY(float fLengthMax);// Extrahiert Subdivision-Mesh mit mehr Polygonen aus dem aktuellen Mesh, abhängig von der maximalen Kantenhöhe fLengthMax in Y-Richtung
	CTriangleList * ExtractSubdivitionZ(float fLengthMax);// Extrahiert Subdivision-Mesh mit mehr Polygonen aus dem aktuellen Mesh,  abhängig von der maximalen Kantentiefe fLengthMax in Z-Richtung

	void EstimateTangentsAndBinormals(); // Versucht, die Tangenten und die Binormalen für das Bumpmapping aus den gegebenen UV-Koordianten zu erraten  

	bool m_bFirstDraw;
	int m_iRenderKind;

	bool Intersects(CRay & r, CHVector & vIntersection, float & fDistanceSquare); // berechnet, ob Strahl r ein Dreieck der Geometrie trifft, vIntersection ist dann der Schnittpunkt

	void Draw(float fDistanceToCameraSquare, CHMat & mGlobal); 
	void Update();

private:
	void TriSub(CTriangleList * ptrianglelist, CVertex * pvertex0, CVertex * pvertex1, CVertex * pvertex2, float fLengthMax, int eKind, int iRecursionDepth = 0);
	void TriSubDisplace(CTriangleList * ptrianglelist, CVertex * pvertex0, CVertex * pvertex1, CVertex * pvertex2, float fLengthMax, float fStrength, int iRecursionDepth = 0);
	float DistanceExt(CHVector vDist,  int eKind);
};

}