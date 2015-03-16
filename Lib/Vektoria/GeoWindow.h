#pragma once

#include "Node.h"
#include "../VektoriaMath/Util.h"
#include "../VektoriaMath/FloatRect.h"
#include "Vertex.h"
//---------------------------------------------------
// CGeoWindow: Klasse, um Fenster und Türen in CGeoWall zu definieren
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2012-11-07
//---------------------------------------------------

namespace Vektoria
{

class CGeoWalls;



enum EGeoWindowStyle
{
	eGeoWindowStyle_Rect = 0,

	eGeoWindowStyle_Tri,
	eGeoWindowStyle_TriLeft,
	eGeoWindowStyle_TriRight,

	eGeoWindowStyle_V,
	eGeoWindowStyle_VLeft,
	eGeoWindowStyle_VRight,

	eGeoWindowStyle_TriRect,
	eGeoWindowStyle_TriRectLeft,
	eGeoWindowStyle_TriRectRight,

	eGeoWindowStyle_Roman,
	eGeoWindowStyle_RomanLeft,
	eGeoWindowStyle_RomanRight,

	eGeoWindowStyle_Gothic,
	eGeoWindowStyle_GothicLeft,
	eGeoWindowStyle_GothicRight,

	eGeoWindowStyle_Arcade,
	eGeoWindowStyle_ArcadeLeft,
	eGeoWindowStyle_ArcadeRight,

	eGeoWindowStyle_Eyebrow,
	eGeoWindowStyle_EyebrowLeft,
	eGeoWindowStyle_EyebrowRight,

	eGeoWindowStyle_Oval,
	eGeoWindowStyle_OvalLeft,
	eGeoWindowStyle_OvalRight,

	eGeoWindowStyle_OvalArc,
	eGeoWindowStyle_OvalArcLeft,
	eGeoWindowStyle_OvalArcRight,

	eGeoWindowStyle_OvalU,
	eGeoWindowStyle_OvalULeft,
	eGeoWindowStyle_OvalURight,


	eGeoWindowStyle_U,				
	eGeoWindowStyle_ULeft,			
	eGeoWindowStyle_URight,			

	eGeoWindowStyle_Bicircle,
	eGeoWindowStyle_BicircleLeft,
	eGeoWindowStyle_BicircleRight,

	eGeoWindowStyle_RectBeveled,
	eGeoWindowStyle_RectBeveledLeft,
	eGeoWindowStyle_RectBeveledRight,

	eGeoWindowStyle_Hexagon, // TODO: bottom und top sind noch durchgängig
	eGeoWindowStyle_HexagonLeft,
	eGeoWindowStyle_HexagonRight,

	eGeoWindowStyle_Octagon,
	eGeoWindowStyle_OctagonLeft,
	eGeoWindowStyle_OctagonRight
};

class CGeoWall;

class CGeoWindow : public CNode
{
public:
	CGeoWindow(void);
	~CGeoWindow(void);

	virtual void UpdateAABB();


	void Copy(CGeoWindow & geowindow);

	void SetInverseCurveAll();
	void SetInverseCurveLeftUpper();
	void SetInverseCurveLeftLower();
	void SetInverseCurveRightUpper();
	void SetInverseCurveRightLower();

	void Init(CFloatRect floatrect, EGeoWindowStyle eStyle = eGeoWindowStyle_Rect, bool bAbsolute = false, float frRadius = 0.5F, float fryHeightSection = 0.0F, int iGranularity = 12); 
	void Init(CFloatRect floatrect, EGeoWindowStyle eStyle = eGeoWindowStyle_Rect, bool bAbsolute = false, float frRadius = 0.5F, float fryHeightSection = 0.0F, float frBevelStrength = 0.25F, int iGranularity = 12); 

	void InitRect(CFloatRect floatrect, bool bAbsolute = false); 

	void InitTri(CFloatRect floatrect, bool bAbsolute = false); 
	void InitTriLeft(CFloatRect floatrect, bool bAbsolute = false); 
	void InitTriRight(CFloatRect floatrect, bool bAbsolute = false); 

	void InitV(CFloatRect floatrect, bool bAbsolute = false); 
	void InitVLeft(CFloatRect floatrect, bool bAbsolute = false); 
	void InitVRight(CFloatRect floatrect, bool bAbsolute = false); 

	void InitTriRect(CFloatRect floatrect, bool bAbsolute = false, float fryHeightSection = INV_PHI);
	void InitTriRectLeft(CFloatRect floatrect, bool bAbsolute = false, float fryHeightSection = INV_PHI);
	void InitTriRectRight(CFloatRect floatrect, bool bAbsolute = false, float fryHeightSection = INV_PHI);

	void InitRoman(CFloatRect floatrect, bool bAbsolute = false, int iGranularity = 12); 
	void InitRomanLeft(CFloatRect floatrect, bool bAbsolute = false, int iGranularity = 12); 
	void InitRomanRight(CFloatRect floatrect, bool bAbsolute = false, int iGranularity = 12); 

	void InitGothic(CFloatRect floatrect, bool bAbsolute = false, float fryHeightSection = 0.2F, int iGranularity = 12); 
	void InitGothicLeft(CFloatRect floatrect, bool bAbsolute = false, float fryHeightSection = 0.2F, int iGranularity = 12); 
	void InitGothicRight(CFloatRect floatrect, bool bAbsolute = false, float fryHeightSection = 0.2F, int iGranularity = 12); 

	void InitArcade(CFloatRect floatrect, bool bAbsolute = false, float frRadius = 1.2F, float fryHeightSection = 0.2F, int iGranularity = 12); 
	void InitArcadeLeft(CFloatRect floatrect, bool bAbsolute = false, float frRadius = 1.2F, float fryHeightSection = 0.2F, int iGranularity = 12); 
	void InitArcadeRight(CFloatRect floatrect, bool bAbsolute = false, float frRadius = 1.2F, float fryHeightSection = 0.2F, int iGranularity = 12); 

	void InitEyebrow(CFloatRect floatrect, bool bAbsolute = false, float fryHeightSection = 0.8F, int iGranularity = 12); 
	void InitEyebrowLeft(CFloatRect floatrect, bool bAbsolute = false, float fryHeightSection = 0.8F, int iGranularity = 12); 
	void InitEyebrowRight(CFloatRect floatrect, bool bAbsolute = false, float fryHeightSection = 0.8F, int iGranularity = 12); 

	void InitOvalArc(CFloatRect floatrect, bool bAbsolute, int iGranularity = 12);
	void InitOvalArcLeft(CFloatRect floatrect, bool bAbsolute, int iGranularity = 12);
	void InitOvalArcRight(CFloatRect floatrect, bool bAbsolute, int iGranularity = 12);

	void InitOvalU(CFloatRect floatrect, bool bAbsolute, int iGranularity = 12);
	void InitOvalULeft(CFloatRect floatrect, bool bAbsolute, int iGranularity = 12);
	void InitOvalURight(CFloatRect floatrect, bool bAbsolute, int iGranularity = 12);

	void InitU(CFloatRect floatrect, bool bAbsolute = false, int iGranularity = 12); 
	void InitURight(CFloatRect floatrect, bool bAbsolute = false, int iGranularity = 12); 
	void InitULeft(CFloatRect floatrect, bool bAbsolute = false, int iGranularity = 12); 

	void InitBicircle(CFloatRect floatrect, bool bAbsolute = false, int iGranularity = 12); 
	void InitBicircleLeft(CFloatRect floatrect, bool bAbsolute = false, int iGranularity = 12); 
	void InitBicircleRight(CFloatRect floatrect, bool bAbsolute = false, int iGranularity = 12); 

	void InitRectBeveled(CFloatRect floatrect, bool bAbsolute = false, float frBevelStrength = 0.25F, int iGranularity = 12); 
	void InitRectBeveledLeft(CFloatRect floatrect, bool bAbsolute = false, float frBevelStrength = 0.25F, int iGranularity = 12); 
	void InitRectBeveledRight(CFloatRect floatrect, bool bAbsolute = false, float frBevelStrength = 0.25F, int iGranularity = 12); 

	void InitHexagon(CFloatRect floatrect, bool bAbsolute);
	void InitHexagonLeft(CFloatRect floatrect, bool bAbsolute);
	void InitHexagonRight(CFloatRect floatrect, bool bAbsolute);

	void InitOctagon(CFloatRect floatrect, bool bAbsolute);
	void InitOctagonLeft(CFloatRect floatrect, bool bAbsolute);
	void InitOctagonRight(CFloatRect floatrect, bool bAbsolute);

	void InitOval(CFloatRect floatrect, bool bAbsolute, int iGranularity = 12);
	void InitOvalLeft(CFloatRect floatrect, bool bAbsolute, int iGranularity = 12);
	void InitOvalRight(CFloatRect floatrect, bool bAbsolute, int iGranularity = 12);

	void HideLeft();
	void HideLeftUpper();
	void HideLeftLower();
	void HideRight();
	void HideRightUpper();
	void HideRightLower();
	void HideBottom();
	void HideTop();

	void CalcRectRelative(CGeoWall * pgeowall);

	void AddGeoWall(CGeoWall * pgeowall);
	bool SubGeoWall(CGeoWall * pgeowall);
//	void Draw(CCamera * pcamera, float fDistanceToCameraSquare, CHMat & mGlobal, int & itFatherIsInFrustum, CGeoWall * pgeowall);
	void Draw(float fDistanceToCameraSquare, CHMat & mGlobal, CGeoWall * pgeowall);

	void TransformWalls(CHMat & m);
	void Saw(CGeoWall * pgeowall);

	bool IsStyleRight();
	bool IsStyleLeft();
	bool IsStyleSym();

	bool Collides(CGeoWindow &geowindow);

	int GetNrOfWalls();
	CGeoWall * GetWall(int iWall);
	CGeoWalls * GetWalls();

	CFloatRect m_floatrect;
	CFloatRect m_floatrectAbsolute;
	int m_eStyle;
	bool m_bAbsolute;
	float m_frRadius;
	float m_fryHeightSection;
	int m_iGranularity;
	float m_bOval;



	bool m_bLeft;
	bool m_bLeftUpper;
	bool m_bLeftLower;
	bool m_bRight;
	bool m_bRightUpper;
	bool m_bRightLower;
	bool m_bBottom;
	bool m_bTop;

	bool m_bStyleHasLeft;
	bool m_bStyleHasRight;
	bool m_bStyleHasBottom;
	bool m_bStyleHasTop;

	bool m_bInverseCurveLeftUpper;
	bool m_bInverseCurveRightUpper;
	bool m_bInverseCurveLeftLower;
	bool m_bInverseCurveRightLower;

	CGeoWall * m_pgeowall;
	CGeoWalls * m_pgeowalls;

	CHMat m_mLocal;
	CHMat m_mRelative;
	void CalcMatRelative();


private:

	CVertex * m_pvertexInterLeftFront;
	CVertex * m_pvertexInterLeftBack;
	CVertex * m_pvertexInterRightFront;
	CVertex * m_pvertexInterRightBack;
	void SawHelp(CGeoWall * pgeowall, float fryHeightSectionLower = 0.5F, float fryHeightSectionUpper = 0.5F, float frTopLeft = 0.5F, float frTopRight = 0.5F, float frRadius = 0.5F, bool bCalcRectHeight = false, bool bUpper = true, bool bLower = false);
	void CalcCoords();
};

}