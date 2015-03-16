#pragma once
#include "TriangleList.h"
#include "Vertex.h"
#include "Face.h"
#include "GeoWindow.h"

//---------------------------------------------------
// CGeoWall: Klasse, um beliebige Wandstrukturen zu erzeugen (mit Durchbr�chen, T�ren, Fenstern und Giebeln)
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte �nderung: 2012-11-07
//---------------------------------------------------

namespace Vektoria
{

struct SWallSection
{
	float fLeft;
	float fMid;
	float fRight;
	CGeoWindow ** m_apWindows;
};

struct SWallTile
{
	CFloatRect floatrect;
	SWallTile * pwalltileLeft;
	SWallTile * pwalltileRight;
	SWallTile * pwalltileTop;
	SWallTile * pwalltileBottom;
	bool bLeftEqual;
	bool bRightEqual;

	bool bLeft;
	bool bRight;
	bool bTop;
	bool bBottom;
	bool bFront;
	bool bBack;

	bool bOn;

	float fRight;
	float fBottom;
	float fLeft;
	float fTop;

	float fUVRight;
	float fUVBottom;
	float fUVLeft;
	float fUVTop;

	float fvLeftV;
	float fvRightV;
	bool bGableOverlap; // true, wenn sich die Gabeln an der R�ckseite �berlappen

	CHVector vPeak;
	CHVector vLeftUpFront;
	CHVector vRightUpFront;
	CHVector vLeftDownFront;
	CHVector vRightDownFront;
	CHVector vLeftUpBack;
	CHVector vRightUpBack;
	CHVector vLeftDownBack;
	CHVector vRightDownBack;
};


class CGeoWall  :
	public CTriangleList
{
public:
	CGeoWall(void);
	~CGeoWall(void);

	void Copy(CGeoWall &zgw); // Kopiert Werte aus zgw in aktuelle hinein, erzeugt Kopien jedes einzelnen Vertex
	float GetLeftGableWidth(float fry); // Gibt die Breitenschnittpunkt der linken Giebelschr�ge an dem relativen y-Punkt fry an  
	float GetRightGableWidth(float fry); // Gibt die H�he der rechten Giebelschr�ge an dem relativen y-Punkt fry an  
	float GetLeftGableHeight(float frx); // Gibt die H�he der linken Giebelschr�ge an dem relativen x-Punkt frx an  
	float GetRightGableHeight(float frx); // Gibt die H�he der rechten Giebelschr�ge an dem relativen x-Punkt frx an  
	

	void SetMiterLeft(float faLeft); // Gibt eine eventuelle linke Wandgehrung im Bogenma� an, muss vor Init aufgerufen werden
	void SetMiterRight(float faRight); // Gibt eine eventuelle linke Wandgehrung im Bogenma� an, muss vor Init aufgerufen werden
	void SetMiterTop(float faLeft); // Gibt eine eventuelle obere Wandgehrung im Bogenma� an, muss vor Init aufgerufen werden
	void SetMiterBottom(float faRight); // Gibt eine eventuelle untere Wandgehrung im Bogenma� an, muss vor Init aufgerufen werden
	void AvoidCracks(); // Versucht, Tiles so anzuordnen, dass sie auch f�r anschlie�endes Tapering, Bending und Twisting in Y-Richtung geeignet sind

	void SetTextureStart(float fxTextureStart = 0.0F, float fyTextureStart = 0.0F); // Verschiebt die UV-Koordinaten der Mauertextur
	void SetTextureRepeat(float fxTextureRepeat = 1.0F, float fyTextureRepeat = 1.0F); // Skaliert die UV-Koordinaten der Mauertextur

	void SetDeclinationZ(float fa, float fTranslationZ); // neigt die Wand um den Winkel fa nach hinten und verschiebt sie in Z-Richtung
	void SetRoundingX(float fa, float fLengthMax = 0.2f); // Gibt eine eventuelle Wandrundung in X-Richtung ein (z.B. um T�rme zu erzeugen)
	void SetRoundingY(float fa, float fLengthMax = 0.2f); // Gibt eine eventuelle Wandrundung in Y-Richtung ein (z.B. um Kuppeln zu erzeugen)

	void SetSpareAngleX(float fa); // Gibt den Aussparungswinkel um die Y-Achse f�r eine gebogene Wand Turm / Zylinder an.=> M�glichkeit f�r Anbauten, Erker Beit�rmchen etc.

	void SetKneeWallHeight(float frKneeWallHeightLeft, float frKneeWallHeightRight);  // Setzt Kniestockh�he links und rechts auf unterschiedliche H�he
	void SetKneeWallHeight(float frKneeWallHeight);  // Setzt Kniestockh�he links und rechts auf selbe H�he
	void SetKneeWallHeightLeft(float frKneeWallHeightLeft); // Setzt Kniestockh�he links
	void SetKneeWallHeightRight(float frKneeWallHeightRight);  // Setzt Kniestockh�he rechts

	void SetGable(float frCuspLeft, float frCuspRight); // Gibt den linken und den rechten Giebelpunkt an (z.B. 0.0 = an der linken Ecke der Mauer, 0.5 = Mauermitte, 1.0 = ganz rechts an der Mauer)
	void SetGable(float frCusp); // Gibt f�r Spitzgiebel den gemeinsamen Scheitelpunkt an (z.B. 0.0 = an der linken ecke der Mauer, 0.5 = Mauermitte, 1.0 = ganz rechts an der Mauer
	void SetGableLeft(float frCuspLeft); // Gibt f�r Spitzgiebel den linken Scheitelpunkt an (z.B. 0.0 = an der linken ecke der Mauer, 0.5 = Mauermitte, 1.0 = ganz rechts an der Mauer
	void SetGableRight(float frCuspRight); // Gibt f�r Spitzgiebel den rechten Scheitelpunkt an (z.B. 0.0 = an der linken ecke der Mauer, 0.5 = Mauermitte, 1.0 = ganz rechts an der Mauer

	void SetGableByAngle(float faGableLeft, float faGableRight); // Erzeugt Gabelpunkte, indem die Winkel ausgehend von den unteren Ecken angegeben werden
	float m_faGableLeft;
	float m_faGableRight;
	bool m_bGableLeftByAngle;
	bool m_bGableRightByAngle;

	void Init(float fWidth, float fHeight, float fThickness, CMaterial * pmaterial, bool bLeft = true, bool bRight = true, bool bBottom = true, bool bTop = true, bool bFront = true, bool bBack = true); // Initialisiert die Mauer fWidth ist die L�nge, fHeight die H�he, fThickness die Dicke, pmaterial das Material der Mauer, mit den boolschen Flages lassen sich die entsprechenden Seiten an- und ausschalten  

	void InitDome(float fRadius, float fThickness, CMaterial * pmaterial = 0, float fEdgeLengthMin = 0.5F, bool bBottom = true, bool bBack = true); // Erzeugt runde Kuppel mit Radius fRadius
	void InitDomeVersatile(float fRadius, float fHeight, float fThickness,  float fStrength = 0.0F, float fWave = 3.0F, CMaterial * pmaterial = 0, float fEdgeLengthMin = 0.2F,  bool bBottom = true, bool bBack = true);  // Erzeugt ein rundes, spitzes Dach mit eventueller Biegung
	void InitDomeOnion(float fRadius, float fHeight, float fThickness,  float fStrength = 0.7F, CMaterial * pmaterial = 0, float fEdgeLengthMin = 0.2F,  bool bBottom = true, bool bBack = true);  // Erzeugt allg�uer Zwiebelt�rmchen mit Radius fRadius und Spitzenh�he fSpike
	void InitDomeSpike(float fRadius, float fHeight, float fThickness, float fStrength = 0.7F, CMaterial * pmaterial = 0, float fEdgeLengthMin = 0.2F, bool bBottom = true, bool bBack = true);  // Erzeugt reingebogenes Spitzt�rmchen mit Radius fRadius und Spitzenh�he fSpike
	void InitDomeCone(float fRadius, float fHeight, float fThickness, CMaterial * pmaterial = 0, float fEdgeLengthMin = 0.5F, bool bBottom = true, bool bBack = true); // Erzeugt ein glattes Spitzdach f�r runde T�rme

	void InitTube(float fRadius, float fHeight, float fThickness, CMaterial * pmaterial = 0, float fEdgeLengthMin = 0.5F, bool bBottom = true, bool bTop = true, bool bBack = true); // Erzeugt eine Wand f�r einen runden Turm mit Radius fRadius und H�he fHeight
	void InitTubeWave(float fRadius, float fHeight, float fThickness, float fAmplitude = 1.0F, float fWavelength = 1.0F, CMaterial * pmaterial = 0, float fEdgeLengthMin = 0.5F, bool bBottom = true, bool bTop = true, bool bBack = true); // Erzeugt eine wellenf�rmige Wand f�r einen runden Turm mit Radius fRadius und H�he fHeight
	void InitTubeOriel(float fRadius, float fHeight, float fThickness, CMaterial * pmaterial = 0, float fEdgeLengthMin = 0.5F, bool bTop = true, bool bBack = true); // Erzeugt einen Erker f�r einen runden Turm mit Radius fRadius und H�he fHeight
	void InitTubeInterface(float fRadiusBottom, float fRadiusTop, float fHeight, float fThickness, CMaterial * pmaterial = 0, float fEdgeLengthMin = 0.5F, bool bBottom = true, bool bTop = true, bool bBack = true); // Erzeugt ein Wand-Interface (unterer Radius zu oberem Radius) f�r einen runden Turm mit H�he fHeight
	void InitTubeSine(float fRadiusBottom, float fRadiusTop, float fHeight, float fThickness, CMaterial * pmaterial = 0, float fEdgeLengthMin = 0.5F, bool bBottom = true, bool bTop = true, bool bBack = true); // Erzeugt ein gebogenes Wand-Interface (unterer Radius zu oberem Radius) f�r einen runden Turm mit H�he fHeight
	void InitTubeEnlargement(float fRadiusInner, float fRadiusOuter, float fHeight, float fThickness, CMaterial * pmaterial = 0, float fEdgeLengthMin = 0.5F, bool bBottom = true, bool bTop = true, bool bBack = true);
	void SetNrOfFloors(int iFloors); // gibt die zu einer Wand dazugeh�rige Stockwerksanzahl an, verbessert u.a. die Vorab-Allozierung von Tiles (diese muss dann nicht mehr auf den Maximalwert gesetzt werden), so dass auch nahezu beliebig gro�e W�nde m�glich sind.

	void Adjust(CGeoWall & geowallTop, bool bAdjustMapping = true); // Justiert die oberen Vertices so, dass sie zur Wand geowallTop passen

	void AddGeoWindow(CGeoWindow * pgeowindow); // Stanzt ein Fenster in die Mauer, welches durch pgeowindow definiert wurde 
	CGeoWindow * MakeGeoWindow(CFloatRect floatrect, EGeoWindowStyle eStyle = eGeoWindowStyle_Rect, bool bAbsolute = false, float frRadius = 0.5F, float frRectHeight = 0.0F, int iGranularity = 12); // Erzeugt ein Fenster
	void AddGeoWindows(CGeoWindow * pgeowindow, CFloatRect floatrect, int ixs, int iys); // Stanzt ixs*iys gleichartige Fenster rasterartig in den Mauerteil floatrect der Mauer, welches durch pgeowindow definiert wurde,  

	int m_iFloors;
	bool m_bRoundingX;
	bool m_bRoundingY;
	float m_faRoundingX;
	float m_faRoundingY;
	float m_fLengthMaxX;
	float m_fLengthMaxY;
	float m_faSpare;

	bool m_bAvoidCracks;
	float m_faDeclination;
	float m_fzTranslation; 
	bool m_bDecline;
	CGeoWindow ** m_apgeowindow;

	SWallSection * m_awallsection;
	int m_iWallSections;

	SWallTile * m_awalltile;
	int m_iWallTiles;
	
	float m_frKneeWallHeightLeft;
	float m_frKneeWallHeightRight;

	CVertex * m_avertex;
	int m_iAllocVertices;
	int m_iVertices;
	float m_fxTextureRepeat;
	float m_fyTextureRepeat;
	float m_fxTextureStart;
	float m_fyTextureStart;

	int m_iGeoWindowAllocs;
	int m_iAllocBlock;
	int m_iGeoWindows;

	float m_fWidth;
	float m_fHeight;

	bool m_bLeft;
	bool m_bRight;
	bool m_bBottom;
	bool m_bTop;
	bool m_bFront;
	bool m_bBack;


	bool m_bGable;
	bool m_bGableInverseLeft;
	bool m_bGableInverseRight;
	float m_frGableCuspLeft;
	float m_frGableCuspRight;
	SWallTile * m_pwalltileGableInverseLeft;
	SWallTile * m_pwalltileGableInverseRight;



	CHVector m_vNormalFront;
	CHVector m_vNormalBack;
	CHVector m_vNormalRight;
	CHVector m_vNormalLeft;
	CHVector m_vNormalBottom;
	CHVector m_vNormalTop;
	CHVector m_vNormalRightGable;
	CHVector m_vNormalLeftGable;

	CHVector m_vTangentFront;
	CHVector m_vTangentBack;
	CHVector m_vTangentRight;
	CHVector m_vTangentLeft;
	CHVector m_vTangentBottom;
	CHVector m_vTangentTop;
	CHVector m_vTangentRightGable;
	CHVector m_vTangentLeftGable;

	CHVector m_vBitangentFront;
	CHVector m_vBitangentBack;
	CHVector m_vBitangentRight;
	CHVector m_vBitangentLeft;
	CHVector m_vBitangentBottom;
	CHVector m_vBitangentTop;
	CHVector m_vBitangentRightGable;
	CHVector m_vBitangentLeftGable;


	float m_fZOffsetFront;
	float m_fZOffsetBack;
	float m_fXOffsetLeft;
	float m_fXOffsetRight;
	float m_fYOffsetBottom;
	float m_fYOffsetTop;

	float m_fThickness;
	float m_frThickness;
	float m_faMiterLeft;
	float m_faMiterRight;
	float m_faMiterBottom;
	float m_faMiterTop;
	bool m_bMiter;
	int m_iAllocTiles;

	CVertexs m_vertexsJunctionFrontBottom;
	CVertexs m_vertexsJunctionBackBottom;
	CVertexs m_vertexsJunctionFrontTop;
	CVertexs m_vertexsJunctionBackTop;

	// void Draw(CCamera * pcamera, float fDistanceToCameraSquare, CHMat & mGlobal, int & itFatherIsInFrustum); // �berladene Funktion wegen Subwindows
	void Draw(float fDistanceToCameraSquare, CHMat & mGlobal); // �berladene Funktion wegen Subwindows

	CHMat m_mLocal; 
	CHMat * m_amGeoWindow;
	void CalcMats();


	void CalcTile(SWallTile & walltile);

	void MakeVLeft(SWallTile & walltile);
	void MakeVRight(SWallTile & walltile);
	void MakeTriLeft(SWallTile & walltile);
	void MakeTriRight(SWallTile & walltile);
	void MakeRect(SWallTile & walltile);



	// Polymorph �berschriebene Methoden:
	void Transform(CHMat & m); // Transformiert alle Punkte der Geometrie mit der Transformationsmatrix m

	/*
	void Subdivide(float fLengthMax);  // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abh�ngig von der maximalen Kantenl�nge fLengthMax, polymorphe �berschreibung
	void SubdivideX(float fLengthMax); // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abh�ngig von der maximalen Kantenbreite fLengthMax in X-Richtung, polymorphe �berschreibung
	void SubdivideY(float fLengthMax); // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abh�ngig von der maximalen Kantenh�he fLengthMax in Y-Richtung, polymorphe �berschreibung
	void SubdivideZ(float fLengthMax); // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abh�ngig von der maximalen Kantentiefe fLengthMax in Z-Richtung, polymorphe �berschreibung

	void RippleY(float fAmplitude, int iHarmonics, float faPhase = 0.0F, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true); // Wellenriffeln um die Y-Achse, polymorphe �berschreibung
	void RippleYHard(float fAmplitude, int iHarmonics, float faPhase = 0.0F, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true); // Wellenriffeln um die Y-Achse, polymorphe �berschreibung

	void TwistX(float faStrength); // Twisting um die X-Achse, polymorphe �berschreibung
	void TwistY(float faStrength); // Twisting um die Y-Achse, polymorphe �berschreibung
	void TwistZ(float faStrength); // Twisting um die Z-Achse, polymorphe �berschreibung

	void BendX(float fRadius, float faSection); // Bending um die X-Achse, polymorphe �berschreibung
	void BendY(float fRadius, float faSection); // Bending um die Y-Achse, polymorphe �berschreibung
	void BendZ(float fRadius, float faSection); // Bending um die Z-Achse, polymorphe �berschreibung

	void TaperX(float fStrength, bool bInfluenceX=false, bool bInfluenceY=true, bool bInfluenceZ = true); // Tapering in Richtung der X-Achse, polymorphe �berschreibung
	void TaperY(float fStrength, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true); // Tapering in Richtung der Y-Achse, polymorphe �berschreibung
	void TaperZ(float fStrength, bool bInfluenceX=true, bool bInfluenceY=true, bool bInfluenceZ = false); // Tapering in Richtung der Z-Achse, polymorphe �berschreibung

	void WaveX(float fAmplitude, float fWavelength, float faPhase = 0.0F, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true); // Wellenform in Richtung der X-Achse, polymorphe �berschreibung
	void WaveY(float fAmplitude, float fWavelength, float faPhase = 0.0F, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true); // Wellenform in Richtung der Y-Achse, polymorphe �berschreibung
	void WaveZ(float fAmplitude, float fWavelength, float faPhase = 0.0F, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true); // Wellenform in Richtung der Z-Achse, polymorphe �berschreibung
	*/

	void GetUVBack(float frx, float fry, float & fu, float & fv); // Berechnet zu einer fraktionalen xy-Koordinate (frx, fry) die passenden UV-Koordinaten (fu, fv) auf der Vorderseite der Mauer
	void GetUVFront(float frx, float fry, float & fu, float & fv); // Berechnet zu einer fraktionalen xy-Koordinate (frx, fry) die passenden UV-Koordinaten (fu, fv) auf der R�ckseite der Mauer


protected:
	void ResetTiles();
	void SawTile(SWallTile & walltile);

	void CalcNormals();

	void SortWindows();
	void MergesortWindows(CGeoWindow ** ageowindow, unsigned int iStart, unsigned int iEnd, unsigned int eKind);
	void MakeSections();
	void MakeSectionsWithoutCracks();
	void OptimizeWallTiles();
	void CalcWallTileBorders();

	CGeoWindow ** m_apgeowindowSortedLeft;
	CGeoWindow ** m_apgeowindowSortedRight;
	CGeoWindow ** m_apgeowindowSortedTop;
	CGeoWindow ** m_apgeowindowSortedBottom;
	CGeoWindow ** m_apgeowindowHelp;
};

}