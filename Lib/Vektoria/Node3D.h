////////////////////////////////////////////////////
/// Klasse: Node3D.h
/// Autor: Tobias Breiner
/// Last change: 2014-05-25
/// Copyright: (c) Vektoria 
////////////////////////////////////////////////////
#pragma once

#include "Intersectable.h"
#include "../VektoriaMath/AABB.h"
#include "Vertex.h"
#include "../VektoriaMath/HMat.h"
#include "Node.h"
#include "../VektoriaMath/HVector.h"

namespace Vektoria
{

class CGeoCube;
class CRoot;
class CPlacement;

class CNode3D : public CNode , public CIntersectable
{
	friend class CNodes;
	friend class CCamera;
	friend class CEmitter;
	friend class CPlacements;
	friend class CPlacement;
	friend class CGeoWall;
	friend class CGeoWindow;
	friend class CGeoWing;
	friend class CGeos;
	friend class CGeo;
	friend class CScene;
	friend class CTriangleList;
	friend class CTriangleStrip;
protected:
	int Tick(CHMat & m, bool & bTick);

public:
	CNode3D(void);
	~CNode3D(void);
	void Copy(CNode3D & pnode3D);

	// Standard Methods
	void Init(void);
	void Fini(void);

	// Multipfadvariablen:
	CHMat * m_amGlobal;		// Liste globaler Matrizen
	CAABB * m_aaabb;		// Axis Aligned Bounding Boxes
	int m_iMatGlobal;
	int m_iMatGlobals;
	int m_iMatGlobalAllocs;
	int m_iAllocStep;
	bool m_bTick;

	// Bounding Boxes

	bool m_bAABBOn; // Boolsches Flag, um die AABB des Knotens aus (false) bzw. an (true) zu schalten
//    bool m_bVisualHelpersEnabled; // Boolsches Flag, um die Visualisierung der AABB aus (false) bzw. an (true) zu schalten
	bool m_bAABBUpdateNeeded;  // true, wenn die AABB neu berechnet werden muss
	bool m_bClearUpdateAABB; 
	bool m_bFixed;
	bool m_bFirstTick;

    CAABB * GetAABB(void);

	void ClearAABB();

    void EnableAABBs(void); // Schaltet AABBs für diesen Node und seine gesamte Unterhierarchie an
    void DisableAABBs(void); // Schaltet AABBs für diesen Node und seine gesamte Unterhierarchie aus

	/*
    void EnableVisualHelper(void); // Schaltet die Visualisierung der AABB nur für diesen Node an
    void DisableVisualHelper(void); // Schaltet die Visualisierung der AABB nur für diesen Node aus
    void EnableVisualHelpers(void); // Schaltet die Visualisierung der AABBs für diesen Node und seine gesamte Überhierarchie an
    void DisableVisualHelpers(void); // Schaltet die Visualisierung der AABBs für diesen Node und seine gesamte Überhierarchie aus
	*/

    // Picking (Ray/AABB Intersection: Schnitt mit Bounding Box)
	bool Intersects(CHVector &vOrigin, CHVector &vRayDirection, CIntersectable** pFound, float* fDistance); // Führt eine Ray/AABB Intersection für diesen Node und seine gesamte Unterhierarchy durch und gibt bei erfolgreicher Intersection den Knoten der zuerst gefunden wurde über r_pFound zurück.
	bool Intersects(CHVector &vOrigin, CHVector &vRayDirection, float* fDistance); // Führt eine Ray/AABB Intersection nur für diesen Knoten durch

//	CGeoCube* m_pgeocubeVisualHelper;
//	CPlacement* m_pzpVisualHelper;
//	bool m_bIsVisualHelper;

private:
//	void DrawVisualHelper(float fDistanceToCameraSquare, CHMat & mGlobal); //Zeichnet die AABB des Knotenobjektes, wenn m_bVisualHelpersEnabled auf true gestellt wurde
};

}