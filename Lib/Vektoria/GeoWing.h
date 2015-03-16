#pragma once
#include "GeoWalls.h"
#include "Material.h"
#include "../VektoriaMath/HVectors.h"
#include "GeoWindows.h"
#include "../VektoriaMath/Plane.h"
//------------------------------------
// CGeoWing
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.08.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

enum EGeoWingPos
{
	eGeoWingPos_Main = 0,
	eGeoWingPos_Sub,
	eGeoWingPos_Corner,
	eGeoWingPos_Wall,
	eGeoWingPos_Roof
};


enum EGeoWingPart
{
	eGeoWingPart_Facade = 0,
	eGeoWingPart_Roof,
	eGeoWingPart_Ceiling,
	eGeoWingPart_Flat,
	eGeoWingParts
};


enum EGeoWingTowerRoof
{
	eGeoWingTowerRoof_Normal = 0,
	eGeoWingTowerRoof_Dome,
	eGeoWingTowerRoof_Onion,
	eGeoWingTowerRoof_Spike,
	eGeoWingTowerRoof_Flat
};

enum EGeoWingTowerFaccade
{
	eGeoWingTowerFaccade_Cylinder = 0,
	eGeoWingTowerFaccade_Based,
	eGeoWingTowerFaccade_BasedBubble,
	eGeoWingTowerFaccade_Wave,
};

enum EGeoWindowFunction
{
	eGeoWindowFunction_Door = 0,
	eGeoWindowFunction_Cellar,
	eGeoWindowFunction_Lowest,
	eGeoWindowFunction_Mid,
	eGeoWindowFunction_Highest,
	eGeoWindowFunction_Center,
	eGeoWindowFunction_Roof,
	eGeoWindowFunctions
};

struct SGeoWingWindow
{
	int iWall;
	EGeoWindowFunction eFunction;
	EGeoWingPart ePart;
	bool bPlural;
	CFloatRect floatrectPlural;
	int ixs;
	int iys;
	int ix;
	int iy;
};

struct SGeoWingCorner
{
	bool bOn;
	CHVector vDirFoot;
	CHVector vDirRoof;
	CHMat mFoot;
	CHMat mRoof;
	float faGableLeft;
	float faGableRight;
	float fHeightRoof;
	float fLengthRoof;
	float faXRoof;
	float faYRoof;
	float faYFoot;
	float fWidth;
	float fa;
	CPlane plane;
	CHVector vRoofBase;
	CHVector vRoof;
	bool bLeft;
	bool bRight;
	bool bLeftRoof;
	bool bRightRoof;
	bool bRoof;
};

struct SGeoWingPart
{
	bool bOn;
	bool bEntryUVMapping;
	float fxTextureStart;
	float fyTextureStart;
	float fxTextureRepeat;
	float fyTextureRepeat;
	bool bTexturePerUnit;
	CGeoWalls geowalls;
	bool bEntryMaterial;
	CMaterial * pzm;
};

struct SGeoWingSub
{
	EGeoWingPos geowingpos;
	int iCornerOrWall;
	float frx;
	float fry;
	float frz;
	CHMat mLocal;
};

struct SGeoWingBattlement
{
	float fHeight;
	float fWidth;
	float fWavelength;
	EGeoWindowStyle eStyle;
	int iGranularity;
};



class CGeoWings;

class CGeoWing : public CTriangleList
{
	friend class CGeoWings;
	friend class CTriangleLists;
	friend class CTriangleList;
	friend class CGeo;
	friend class CGeos;
private:
	bool m_bSesamy;
	void Tick(CHMat &mGlobal, bool & bTick);

public:
	CGeoWing();
	~CGeoWing();
	CGeoWing operator=(CGeoWing geowing);
	void Copy(CGeoWing geowing);

	// Parameter-Setzfunktionen:
	void OpenSesamy(char * ac);

	void SetRandom(unsigned int ixRandom, unsigned int iyRandom);
	unsigned int m_ixRandom;
	unsigned int m_iyRandom;
	bool m_bEntryRandom;

	void SetPolyCorners(int iPolyCorners);
	int m_iPolyCorners;
	bool m_bEntryPolyCorners;

	void SetHeightBalustrade(float fHeightBalustrade); // Setzt die Geländerhöhe für Flachdächer und Balkone
	float m_fHeightBalustrade;
	bool m_bEntryBalustrade;
	void SetThickness(float fThickness); // Setzt die Wanddicke
	void SetHeightRoof(float fHeightRoof); // Setzt die Ausmaße eines rechteckigen Standardgebäudeflügels
	float m_fHeightRoof;
	bool m_bEntryHeightRoof;

	void SetSizeRect(float fWidth, float fDepth, float fHeightFacade); // Setzt die Ausmaße eines rechteckigen Standardgebäudeflügels
	void SetSizeTower(float fRadius, float fHeightFacade); // Setzt die Ausmaße eines runden Turmes
	void SetSizePrint(float fDepth, float fHeightFacade); // setzt die Ausmaße für ein beliebiges Grundrissgebäude
	float m_fHeightFacade;
	float m_fHeightTotal;
	float m_fHeightFlat; 
	float m_fThickness;
	float m_fDepth;
	float m_fWidth;
	bool m_bRoundTower;

	void SetMaterials(CMaterial * pzmFacade, CMaterial * pzmRoof, CMaterial * pzmCeiling, CMaterial * pzmFloor, CMaterial * pzmFlat);
	void SetMaterialRoof(CMaterial * pzm);
	void SetMaterialCeiling(CMaterial * pzm);
	void SetMaterialFacade(CMaterial * pzm);
	void SetMaterialFlat(CMaterial * pzm);
	void SetTextureStart(float fxTextureStart = 0.0F, float fyTextureStart = 0.0F, EGeoWingPart ePart = eGeoWingParts); // Verschiebt die UV-Koordinaten der angegebenen Gebäudeteiltextur
	void SetTextureRepeat(float fxTextureRepeat = 1.0F, float fyTextureRepeat = 1.0F, EGeoWingPart ePart = eGeoWingParts); // Skaliert die UV-Koordinaten der angegebenen Gebäudeteiltextur
	void SetTexturePerUnit(EGeoWingPart ePart = eGeoWingParts); // UV-Koordinaten der angegebenen Gebäudeteiltextur werden automatisch auf dessen Größe skaliert

	void SetPrint(CHVectors * phvectorsPrint); // Legt Grundriss des Gebäudes fest
	CHVectors m_vsFoot;
	CHVectors m_vsRoof;

	void HideRoof(); // Versteckt das Dach
	void ShowLeft(); // Erzeugt und zeigt linken Mauerseiten, wirkt sich nur bei bOpen = true aus
	void ShowRight(); // Erzeugt und zeigt die rechten Mauerseiten, wirkt sich nur bei bOpen = true aus
	void ShowBottom(); // Erzeugt und zeigt den Boden der Mauer
	void HideTop(); // Versteckt die Oberseite der Mauer
	void ShowTop(); //Zeigt die Oberseite der Mauer

	void SetBattlement(float fHeight, float fWidth, float fWidthNext, EGeoWindowStyle eStyle, int iGranularity = 12); // fügt Zinnen hinzu, geht natürlich nur bei Flachdächern
	SGeoWingBattlement * m_pbattlement;

	void SetEdgeLengthMin(float fEdgeLengthMin);
	float m_fEdgeLengthMin;
	bool m_bEntryEdgeLengthMin;

	void SetDepthMans(float fDepthMans);
	float m_fDepthMans;
	bool m_bEntryDepthMans;

	void SetOverroof(float fOverroofDepth, float fOverroofHeight);
	float m_fOverroofDepth;
	float m_fOverroofHeight;
	bool m_bEntryOverroof;

	void SetInner(bool bInner);
	bool m_bInner;
	bool m_bEntryInner;
	bool m_bPrint;

	// Add-Funktionen:
	void AddGeoWindow(CGeoWindow * pgeowindow, int iWall, EGeoWingPart ePart = eGeoWingPart_Facade); // Stanzt ein einzelnes Fenster an die Wand mit der Nummer iWall
	void AddGeoWindows(CGeoWindow * pgeowindow, int iWall, CFloatRect floatrect, int ixs, int iys, EGeoWingPart ePart = eGeoWingPart_Facade); // Stanzt ixs mal iys Fenster in den Bereich der Wand mit der Nummer iWall, der mit floatrect angegeben ist
	void AddGeoWindowsRandom(CGeoWindow * pgeowindow, CGeoWindow * pgeowindowDoor, int iWallDoor); // Versucht, die Fanster automatisch zu platzieren
	void AddRandomDoor(CGeoWindow * pgeowindow, int iWallDoor); // Fügt eine Tür hinzu, die automatisch plaziert wird
	void AddRandomWindow(CGeoWindow * pgeowindow); // Fügt ein Fenster hinzu, das automatisch plaziert wird
	void AddRandomWindowHighest(CGeoWindow * pgeowindow); // Fügt ein Fenster hinzu, das automatisch in die oberste Fensterzeile plaziert wird
	void AddRandomWindowLowest(CGeoWindow * pgeowindow); // Fügt ein Fenster hinzu, das automatisch in die unterste Fensterzeile plaziert wird
	void AddRandomWindowMid(CGeoWindow * pgeowindow); // Fügt ein Fenstertyp hinzu, das automatisch in die mittleren Fensterzeilen plaziert wird
	void AddRandomWindowRoof(CGeoWindow * pgeowindow); // Fügt ein Fenstertyp hinzu, das automatisch auf die Dächer plaziert wird
	void AddRandomWindowCellar(CGeoWindow * pgeowindow); // Fügt ein Fenstertyp hinzu, die automatisch als Kellerfenster plaziert wird

//	void AddTowerToCorner(float fRadius, float fHeight, float fHeightBase, int iCorner, int eKind, int eKindCylinder);
//	void AddTowerToWall(float fRadius, float fHeight, float fHeightBase, int iWall, int eKindRoof, int eKindCylinder);

	void AddGeoWing(CGeoWing * pgeowing, CHMat & m); // fügt ein Untergebäudeteil dazu, die Poition wird durch die Matrix m gesetzt
	void AddGeoWingToCorner(CGeoWing * pgeowing, int iCorner); // fügt ein Untergebäudeteil an eine Ecke dazu
	void AddGeoWingToWall(CGeoWing * pgeowing, int iWall); // fügt ein Untergebäudeteil an eine Wand dazu
	void AddGeoWingToRoof(CGeoWing * pgeowing, float frx = 0.0F, float fry = 0.0F, float frz = 0.0F); // fügt ein Untergebäudeteil auf ein Dach hinzu, die relative Postion wird durch frx und fry ermittelt



	// Init-Funktionen:
	void InitRoundTower(EGeoWingTowerRoof eKind = eGeoWingTowerRoof_Normal);
	EGeoWingTowerRoof m_eGeoWingTowerRoof;

	void InitPrintTent(); // erzeugt Gebäude mit beliebigen Grundriss und Zeltdach 
	void InitPrintFlat(); // erzeugt Gebäude mit beliebigen Grundriss und Flachdach

	void InitYardRoof(); // erzeugt Gebäude mit beliebigen Grundriss, Satteldach und Innenhof
	void InitYardFlat(); // erzeugt Gebäude mit beliebigen Grundriss, Flachdach und Innenhof
	void InitYardRutsh(); // erzeugt Gebäude mit beliebigen Grundriss, Schrägdach und Innenhof

	void InitPolyFlat(); // erzeugt Gebäude mit n Kanten und Flachdach
	void InitPolyTent(); // erzeugt Gebäude mit n Kanten und Zeltdach
	bool m_bPoly;

	void InitRectFlat(); // erzeugt rechteckiges Gebäude mit Zeltdach
	void InitRectMans(); // erzeugt rechteckiges Gebäude mit Mansardendach
	void InitRectTent(); // erzeugt rechteckiges Gebäude mit Zeltdach
	void InitRectSaddle(); // erzeugt rechteckiges Gebäude mit Satteldach

	void Fini();


	CGeoWings * m_pgeowings;

	SGeoWingPart m_ageowingpart[eGeoWingParts];
	SGeoWingCorner * m_acorner;

	int GetNrOfWings(); // gibt die Anzahl der Untergebäudeflügel aus
	CGeoWing* GetWing(int iWing); 

	bool IsWallOn(int iWall);
	void SetWallOn(int iWall);
	void SetWallOff(int iWall);

	void Open();
	bool m_bOpen;



	int m_iWallDoor;

	bool m_bRoof;
	bool m_bLeft;
	bool m_bRight;
	bool m_bBottom;
	bool m_bTop;
	bool m_bFlatRoof;
	bool m_bWindowRandom;
	float m_fRadius;

	void SetAnnexAngle(float faAnnex); // Setzt expilzit den Öffnungswinkel des Anbaus (wird per Default automatisch abgeschätzt, diese Abschätzun g kann aber nicht bei verschiedenen Vaterhauptgebäuden funktionieren)
	float m_fAnnexHeight;
	bool m_bAnnexAngle;
	bool m_faAnnex;

	SGeoWingWindow * m_awingwindow;
	CGeoWindows m_geowindows;

	bool m_bEntryWindowSet;
	bool m_bEntryThickness;
	CGeoWindows m_ageowindows[eGeoWindowFunctions];
	
	SGeoWingSub * m_ageowingsub;

	void Draw(float fDistanceToCameraSquare, CHMat & mGlobal);

	// Polymorph überschriebene Methoden:
	void Transform(CHMat & m); // Transformiert alle Punkte der Geometrie mit der Transformationsmatrix m, polymorphe Überschreibung

	void Subdivide(float fLengthMax);  // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abhängig von der maximalen Kantenlänge fLengthMax, polymorphe Überschreibung
	void SubdivideX(float fLengthMax); // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abhängig von der maximalen Kantenbreite fLengthMax in X-Richtung, polymorphe Überschreibung
	void SubdivideY(float fLengthMax); // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abhängig von der maximalen Kantenhöhe fLengthMax in Y-Richtung, polymorphe Überschreibung
	void SubdivideZ(float fLengthMax); // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abhängig von der maximalen Kantentiefe fLengthMax in Z-Richtung, polymorphe Überschreibung

	void RippleY(float fAmplitude, int iHarmonics, float faPhase = 0.0F, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true); // Wellenriffeln um die Y-Achse, polymorphe Überschreibung
	void RippleYHard(float fAmplitude, int iHarmonics, float faPhase = 0.0F, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true); // Wellenriffeln um die Y-Achse, polymorphe Überschreibung

	void TwistX(float faStrength); // Twisting um die X-Achse, polymorphe Überschreibung
	void TwistY(float faStrength); // Twisting um die Y-Achse, polymorphe Überschreibung
	void TwistZ(float faStrength); // Twisting um die Z-Achse, polymorphe Überschreibung

	void BendX(float fRadius, float faSection); // Bending um die X-Achse, polymorphe Überschreibung
	void BendY(float fRadius, float faSection); // Bending um die Y-Achse, polymorphe Überschreibung
	void BendZ(float fRadius, float faSection); // Bending um die Z-Achse, polymorphe Überschreibung

	void TaperX(float fStrength, bool bInfluenceX=false, bool bInfluenceY=true, bool bInfluenceZ = true); // Tapering in Richtung der X-Achse, polymorphe Überschreibung
	void TaperY(float fStrength, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true); // Tapering in Richtung der Y-Achse, polymorphe Überschreibung
	void TaperZ(float fStrength, bool bInfluenceX=true, bool bInfluenceY=true, bool bInfluenceZ = false); // Tapering in Richtung der Z-Achse, polymorphe Überschreibung

	void WaveX(float fAmplitude, float fWavelength, float faPhase = 0.0F, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true); // Wellenform in Richtung der X-Achse, polymorphe Überschreibung
	void WaveY(float fAmplitude, float fWavelength, float faPhase = 0.0F, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true); // Wellenform in Richtung der Y-Achse, polymorphe Überschreibung
	void WaveZ(float fAmplitude, float fWavelength, float faPhase = 0.0F, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true); // Wellenform in Richtung der Z-Achse, polymorphe Überschreibung


private:
	bool CalcNewPrint();
	void CalcSize();
	void Init();
	void InitCorners();
	void CutHoleIfSubwing();

//	void UpdateAABB();

	int PlaceWindowsRandomly(); 
	void DistributeInRow(CGeoWindows & geowindows, int iy, int iys, CFloatRect floatrect, float fWidth, CGeoWall * pgeowall);
	void CalcUV(SGeoWingPart & geowingpart, float fHeight, int iWall);
	void CopyDownwards();
	void RealizeBattlement(CGeoWall * pgeowall, float fWidth, float fHeight);

	void AddGeoWing(CGeoWing * pgeowing);
	void DistributeSubWings();

};

}