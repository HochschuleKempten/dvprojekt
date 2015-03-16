#pragma once
#include "Util.h"
#include "TriangleStrip.h"
#include "renderapi.h"
#include "math.h"

// Terrain.h: interface for the CTerrain class
// This class will encapsulate all the functionality and information needed to generate the terrain from a RAW file and a texture.
//
// Written and Developed by Matthias Sommer
// E-Mail:   8bitblip@googlemail.com
//
//////////////////////////////////////////////////////////////////////

class CTerrain : public CTriangleStrip
{
public:
    CTerrain(void);
    ~CTerrain(void);

    void Init(int iWidth, int iHeight, CMaterial* pMaterial, CRenderApi* pRenderApi, float fRoughness);
private:
    CVertex* m_aVertex;
    float m_fDisplacement;
    float m_fRoughness;
    int m_iWidth;
    int m_iHeight;
    int m_iSize;

    /* diamond Square algorithm */
    float** DiamondSquare(int iWidth, int iHeight, float fRoughness); // Erzeugt eine Heightmap mit Hilfe des Diamond Square Algorithmus
    void DiamondStep(float** aHeightMap, int iPosX, int iPosY, int iWidth, int iHeight, float fDisplacement); // Diamant-Schritt des Diamond Square Algorithmus
    // Quadrat-Schritt des Diamond Square Algorithmus
    // float** aHeightMap: Zweidimensionale Heightmap
    // int iPosX = Offset auf der X-Achse
    // int iPosY = Offset auf der Y-Achse
    // int iWidth = Breite des Gitters
    // int iHeight = Höhe des Gitters
    void SquareStep(float** aHeightMap, int iPosX, int iPosY, int iWidth, int iHeight, float fDisplacement);
    float RandomDisplacement(float fDisplacement);
};
