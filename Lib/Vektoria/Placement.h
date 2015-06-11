#pragma once
#include "../VektoriaMath/HMat.h"
#include "../VektoriaMath/Quaternion.h"
#include "Cameras.h"
#include "Emitters.h"
#include "Geos.h"
#include "Audios.h"
#include "PointLights.h"
#include "SpotLights.h"
#include "ApiRender.h"
#include "Nodes.h"
#include "GeoWall.h"
#include "GeoWindow.h"
#include "Node3D.h"
#include "Scenes.h"
#include "DistributedGlobal.h"



//---------------------------------------------------
// CPlacement: Klasse für eine Positionierungs-Instanz mit Lokaler Matrix für den Szenegrafen
//
// Autoren: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2014-05-27
//---------------------------------------------------

namespace Vektoria
{

class CCamera;
class CPlacements;
class CTriangleLists;
class CWribels;
class CWribel;
class CScenes;

class CPlacement : public CNode3D
{
	friend class CPlacements;
	friend class CPhysical;
	friend class CWribel;
	friend class CWribels;
	friend class CNode3D;
	friend class CScene;
private:
	void Tick(CHMat & m, float & fTimeDelta, bool & bTick, int & iInst);
	void SetScene(CScene * pscene);

	void DontDraw(bool &bTickTack); 
	void Draw(CCamera * pcamera, CHMat & mGlobalFather, int & itFatherIsInFrustum, bool & bTickTack);
	bool m_bTickTack;


public:
	CPlacement();
	~CPlacement();
	CPlacement operator=(CPlacement & placement);
	void Copy(CPlacement & placement);

	void Init();
	void Fini();


	void AddGeo(CGeo * pgeo);
	void AddEmitter(CEmitter * pemitter);
	void AddCamera(CCamera * pcamera);
	void AddPointLight(CPointLight * ppointlight);
	void AddSpotLight(CSpotLight * pspotlight);
	void AddPlacement(CPlacement * pplacement);
	void AddAudio(CAudio * paudio);
	void AddWribel(CWribel * pwribel);

	bool SubGeo(CGeo * pgeo); // Hängt die Geometrie wieder von dem aktuellen Placement ab, gibt true aus, wenns geklappt hat
	bool SubEmitter(CEmitter * pemitter);
	bool SubCamera(CCamera * pcamera); // Hängt die Kamera wieder von dem aktuellen Placement ab, gibt true aus, wenns geklappt hat
	bool SubSpotLight(CSpotLight * pspotlight); // Hängt das Scheinwerferlicht wieder von dem aktuellen Placement ab, gibt true aus, wenns geklappt hat
	bool SubPointLight(CPointLight * ppointlight); // Hängt das Punktlicht wieder von dem aktuellen Placement ab, gibt true aus, wenns geklappt hat
	bool SubPlacement(CPlacement * pplacement); // Hängt das Unterplacement wieder von dem aktuellen Placement ab, gibt true aus, wenns geklappt hat
	bool SubAudio(CAudio * paudio); // Hängt den 3D Sound wieder von dem aktuellen Placement ab, gibt true aus, wenns geklappt hat
	bool SubWribel(CWribel * pwribel); // Hängt den 3D Sound wieder von dem aktuellen Placement ab, gibt true aus, wenns geklappt hat


	void SetLoD(float fDistNear, float fDistFar);
	void SetBillboard(); 
	void SetBillboardX();
	void SetBillboardY();
	void SetBillboardZ();
	void SetBillboardScaling(float fx, float fy);
	void SetBillboardAngle(float fa);
	float GetBillboardAngle();
	float GetBillboardScalingX();
	float GetBillboardScalingY();
	void SetSky();
	void SetGround();
	void SetAppendage();

	void SetMat(CHMat & m); // Setztt die lokale Matrix
	void SetMatGlobal(CHMat & m); // Setzt die globalen Matrizen auf m und ignoriert lokale Matrix
	bool m_bIndependent;
	CHMat m_mLocal;


	void Unit();				// Generiert Einheitsmatrix für das Placement => Placement wird wieder auf Ursprungsposition transformiert
    void CopyRotationXDelta(float fa);
    void CopyRotationYDelta(float fa);
    void CopyRotationZDelta(float fa);
    void CopyTranslationX(float fx);
    void CopyTranslationY(float fy);
    void CopyTranslationZ(float fz);
    void CopyScaleX(float fx);
    void CopyScaleY(float fy);
    void CopyScaleZ(float fz);
	void RotateX(float fa);		// Generiert Rotationsmatrix um x-Achse mit Winkel fa für das Placement
	void RotateY(float fa);		// Generiert Rotationsmatrix um y-Achse mit Winkel fa für das Placement
	void RotateZ(float fa);		// Generiert Rotationsmatrix um z-Achse mit Winkel fa für das Placement
	void Rotate(float fx, float fy, float fz, float fa); // Generiert beliebige Rotationsmatrix um die Drehachse fx, fy, fz mit Winkel fa für das Placement
	void Rotate(CHVector & v, float fa); // Generiert beliebige Rotationsmatrix um die Drehachse v mit Winkel fa für das Placement
	void Rotate(CHVector & vTo, CHVector & vFrom); // erzeugt eine Rotationsmatrix, die Richtungsvektor vFrom genau in die Richtung des Richtungsvektors vTo rotiert für das Placement
	void Rotate(CQuaternion &q); // erzeugt eine Rotationsmatrix aus dem Rotationsquaternion q
	void Scale(CHVector & v);// Generiert Skalierungsmatrix mit drei verschiedenen Skalierungswerten für das Placement
	void Scale(float fx, float fy, float fz);// Generiert Skalierungsmatrix mit drei verschiedenen Skalierungswerten für das Placement
	void Scale(float f);		// Generiert uniforme Skalierungsmatrix für das Placement
	void ScaleX(float fx);		// Generiert uniforme Skalierungsmatrix für das Placement, bei dem nur X skaliert wird
	void ScaleY(float fy);		// Generiert uniforme Skalierungsmatrix für das Placement, bei dem nur X skaliert wird
	void ScaleZ(float fz);		// Generiert uniforme Skalierungsmatrix für das Placement, bei dem nur X skaliert wird
	void Translate(CHVector & v); // Generiert Verschiebungsmatrix für das Placement
	void Translate(float fx, float fy, float fz); // Generiert Verschiebungsmatrix für das Placement
	void TranslateX(float fx); // Generiert Verschiebungsmatrix in X-Richtung für das Placement
	void TranslateY(float fy); // Generiert Verschiebungsmatrix in Y-Richtung für das Placement
	void TranslateZ(float fz); // Generiert Verschiebungsmatrix in Z-Richtung für das Placement

    CHVector GetTranslation(void);
    CHVector GetScale(void);

	void RotateXDelta(float fa);		// Generiert Rotationsmatrix um x-Achse mit Winkel fa und multipliziert diese mit der bisherigen Matrix des Placements => Placement wird um Winkel fa um die X-Achse weitergedreht 
	void RotateYDelta(float fa);		// Generiert Rotationsmatrix um y-Achse mit Winkel fa und multipliziert diese mit der bisherigen Matrix des Placements => Placement wird um Winkel fa um die Y-Achse weitergedreht 
	void RotateZDelta(float fa);		// Generiert Rotationsmatrix um z-Achse mit Winkel fa und multipliziert diese mit der bisherigen Matrix des Placements => Placement wird um Winkel fa um die Z-Achse weitergedreht 
	void RotateDelta(float fx, float fy, float fz, float fa); // Generiert beliebige Rotationsmatrix um die Drehachse fx, fy, fz mit Winkel fa und multipliziert diese mit der bisherigen Matrix des Placements => Placement wird um Winkel fa um die DrehachseAchse weitergedreht 
	void RotateDelta(CHVector & v, float fa); // Generiert beliebige Rotationsmatrix um die Drehachse v mit Winkel fa und multipliziert diese mit der bisherigen Matrix des Placements => Placement wird um Winkel fa um die DrehachseAchse weitergedreht 
	void RotateDelta(CQuaternion &q); // erzeugt eine Rotationsmatrix aus dem Rotationsquaternion q und multipliziert diese mit der bisherigen Matrix des Placements
	void ScaleDelta(CHVector & v);	// Generiert Skalierungsmatrix mit drei verschiedenen Skalierungswerten und multipliziert diese mit der bisherigen Matrix des Placements => Placement wird um fx,fy un fz größer
	void ScaleDelta(float fx, float fy, float fz);// Generiert Skalierungsmatrix mit drei verschiedenen Skalierungswerten und multipliziert diese mit der bisherigen Matrix des Placements => Placement wird um fx,fy un fz größer
	void ScaleDelta(float f);		// Generiert uniforme Skalierungsmatrix und multipliziert diese mit der bisherigen Matrix des Placements => Placement wird um Fakto f größer
	void ScaleXDelta(float fx);		// Generiert uniforme Skalierungsmatrix für das Placement, bei dem nur X skaliert wird
	void ScaleYDelta(float fy);		// Generiert uniforme Skalierungsmatrix für das Placement, bei dem nur X skaliert wird
	void ScaleZDelta(float fz);		// Generiert uniforme Skalierungsmatrix für das Placement, bei dem nur X skaliert wird
	void TranslateDelta(float fx, float fy, float fz); // Generiert Verschiebungsmatrix für das Placement => Placement wandert um v weiter
	void TranslateDelta(CHVector & v); // Generiert Verschiebungsmatrix für das Placement => Placement wandert um v weiter
	void TranslateXDelta(float fx); // Generiert Verschiebungsmatrix in X-Richtung und multipliziert diese mit der bisherigen Matrix für das Placement
	void TranslateYDelta(float fy); // Generiert Verschiebungsmatrix in Y-Richtung und multipliziert diese mit der bisherigen Matrix für das Placement
	void TranslateZDelta(float fz); // Generiert Verschiebungsmatrix in Z-Richtung und multipliziert diese mit der bisherigen Matrix für das Placement

	void PlaceSphericalGlobal(float fRadius, float faAzimuth, float faAltitude, CPlacement * pzpCenter, int iGlobalInstance = 0); // Plaziert das Placment anhand Azimut, Elevation und Radiús global um ein anderes Zielplacement (gut, um Zielplacement von allen Seiten anzuschauen) 
	void PlaceSphericalLocal(float fRadius, float faAzimuth, float faAltitude, CPlacement * pzpCenter);// Plaziert das Placment anhand Azimut, Elevation und Radiús im lokalen Koordinatensystem um ein anderes Zielplacement (gut, um Zielplacement von allen Seiten anzuschauen, wenn beide Placements direkt an Szene hängen) 


	bool IsColliding(CPlacement * pzp); // Gibt true aus, wenn die beiden Bounding-Boxen der Placements kollidieren
	bool IsColliding(CPlacement * pzp, CScene *pzs); // Gibt true aus, wenn die beiden Bounding-Boxen der Placements innerhalb einer Szene kollidieren
	CPlacements * GetCollidingPlacements(CScene *pzs); // Gibt in einer Szene alle Placements aus, mit der das aktuelle Placement kollidiert 


	void FixDistance(float fDistance); // Fixiert die Distanz, die für die Z-Buffer-Sortierung verwendet wird, z.B. notwendig für ineinander geschachtelte semitransparente Skydomes 	
	bool m_bFixedDistance;
	float m_fDistanceToCameraSquare;

	void MakeStereoscopicCameras(CCamera *pcameraLeftEye, CCamera *pcameraRightEye, float fEyeDistance, float fFocusDistance, float faFov=2.0F, float fNearClipping=0.1F, float fFarClipping=1000.0F); //Erzeugt eine komplexe Struktur aus drei Placements und zwei Kameras für Stereoskopie
	void KillStereoscopicCameras(); // Eleminiert die aufgebaute Struktur für stereoskopische Kameras 
	void SetStereoscopicParameters(float fEyeDistance, float fFocusDistance); // Verändert die Parameter der stereoskopischen Struktur, wenn vorhanden
	bool GetStereoscopicParameters(float & fEyeDistance, float & fFocusDistance); // Gibt die Parameter der stereoskopischen Struktur zurück, gibt true aus wenn vorhanden

	void HierarchyToTriangleList();

	CPlacement ** m_applacementCamera;
	bool m_bStereoscopic;
	float m_fEyeDistance;
	float m_fFocusDistance;

	bool m_bFrustumCulling;
	bool m_bFrustumCullingEntry;
	void SetFrustumCullingOn();
	void SetFrustumCullingOff();
	void SetFrustumCullingByFather();

	bool m_bBVHExactCalculation;
	bool m_bBVHExactCalculationEntry;
	void SetBVHExactCalculationOn();
	void SetBVHExactCalculationOff();
	void SetBVHExactCalculationByFather();

	CPlacement * PickPlacement(CRay & r, float & fMin, float & fMax); // Schaut, ob Placement mit der irgendeiner Boundingbox der Unterhueirarchie kollidiert, fMin und fMax geben die Ausmaßdistanzen des gefundnen Placments aus 
	void PickPlacements(CRay & r, CPlacements * pzps, bool bPickOnlyPlacementsWithDirectGeos);
	bool IsIntersecting(CRay & r); // Schaut, ob Strahl r mit der BoundingBox irgendeiner Instanz dieses Placments kollidiert

	bool m_bBillboard;
	int m_eBillboardType;
	bool m_bBillboardModification;
	bool m_bAppendage;
	float m_faBillboard;
	float m_fxBillboardScale;
	float m_fyBillboardScale;
	CHMat m_mBillboardModification;

	bool m_bPointing;
	bool m_bPointingToVector;
	int m_iPointingInstance;
	CHVector * m_pvectorPointing;
	CPlacement * m_pplacementPointing;

	void SetPointing(CHVector * pvectorPointing); // macht, dass das Placement automatisch sich in Richtung des Raumpunkts orientiert, der durch pvectorPointing gegeben ist (u.a. wichitig für Kameras, die auf ein Punkt schauen sollen)
	void SetPointing(CPlacement * pplacementPointing, int iInstance = 0); // macht, dass das Placement automatisch sich in Richtung des Placements orientiert, der durch pplacement gegeben ist (ua.a. wichitig für Kameras, die auf ein objekt schauen sollen)
	void SetPointingOff(); 

	// Beschleunigungsroutinen, die sich auf das aktuelle Placement plus die gesamte angehängte Hierarchie auswirken, müssen NACH allen Add- und Init-Routinen einmal aufgerufen werden:
	void Fix(); // Sollte aufgerufen werden, wenn sicher ist, dass Placment und Unterplacements starr in der Gegend stehen => Beschleunigt das Rendering, da dann die Matrizen nicht immer wieder neu berechnet werden 
	void Unfix(); //Macht Fix rückgängig
	void Fasten(); // Sortiert nach Status-Calls, um CPUGPU-Traffic zu reduzieren und vereinigt Geometrien mit gleichem Material  => Beschleunigung (Achtung 1, die Rekalkulation dauert lange!, Achtung 2: Transparente Objekte funktonieren nicht mehr), erlaubt Beschleunigung der untergeortneten Hierarachie, das Placement kann im Gegensatz zu FixAndFasten trotzdem noch bewegt werden
	void Unfasten(); // Macht Fasten rückgängig (Achtung, dauert lange)
	void FixAndFasten(); // Sortiert nach Status-Calls, um CPUGPU-Traffic zu reduzieren und vereinigt Geometrien mit gleichem Material  => Beschleunigung (Achtung 1: Die Rekalkulation dauert lange!, Achtung 2: Objekt lösst sich nicht mehr bewegen, Achtung 3: Transparente Objekte funktonieren nicht mehr)
	void UnfixAndUnfasten(); // Macht FixAndFasten rückgängig (Achtung, dauert lange)

	bool m_bStateSorted;

	float m_fDistFarSquare;
	float m_fDistNearSquare;
	bool m_bLoD;
	bool m_bSky;

	CPlacements * m_pplacements;
	CSpotLights * m_pspotlights;
	CPointLights * m_ppointlights;
	CGeos * m_pgeos;
	CEmitters * m_pemitters;
	CCameras * m_pcameras;
	CAudios * m_paudios;
	CWribels * m_pwribels;

	CPlacement *m_pzpUnsorted; // Hier wird bei StateSorting die alte Unterhierarchie geparkt
	CPlacement *m_pzpSorted; // Hier wird bei UnstateSorting die state gesortete Unterhierarchie geparkt

	bool HasTransparent(); // Gibt true aus, wenn irgenein transparentes Objekt an das Placement angehangen wurde
	bool m_bTransparent;

    const char* ClassName() { return "CPlacement"; }

	void UpdateAABBsFromDirectChildrenUpwards(void); // Aktualisiert die AABB für diesen Node und seine gesamte Unterhierarchie
	void UpdateAABBHierarchyWithGeos(void);
	void UpdateAABBAnchestors();
	void UpdateAABBThisFromDirectChildren();
	void UpdateAABBsFromPlacementHierarchyUpwards();


	CScenes  m_scenesAnchestor;


#ifdef NETWORKMASTER
	unsigned int GetidId();
#endif
private:
	void HierarchyStateSort(bool bFix);
	void HierarchyToGeo(CHMat & m, CTriangleLists * ptrianglelists, bool bSon);
	void HierarchyToGeo();
	void HierarchyGeosToGeo(CTriangleLists * ptrianglelists, CGeos * pgeos, CHMat & mGlobal);
	void HierarchyGeoToGeo(CTriangleLists * ptrianglelists, CGeo * pgeo, CHMat & mGlobal);
	void HierarchyWing(CTriangleLists * ptrianglelists, CGeo * pgeo, CHMat & mGlobal);
	void HierarchyWall(CTriangleLists * ptrianglelists, CGeo * pgeo, CHMat & mGlobal);

	void CopyDownwards(); // Kopiert alle Eigenschaften des Placements rekursiv in der Hierarchie hinunter, belässt die Eigenschaften, wo ein Entry-Flag gesetzt wurde

	int m_iDraw;
	bool m_bLastInsideLoD;
	CHMat m_mGlobalIndependent; 
#ifdef NETWORKMASTER
	unsigned int m_idId;
	int m_icId;
#endif
};

}