#pragma once
#include "TriangleStrip.h"
#include "../VektoriaMath/HMats.h"
#include "../VektoriaMath/HVectors.h"


namespace Vektoria
{

class CGeoSweep :
	public CTriangleStrip
{
public:
	CGeoSweep(void);
	~CGeoSweep(void);
    virtual const char* ClassName(void) { return "CGeoSweep"; }

	void SetTextureStart(float fuTextureStart, float fvTextureStart); // Setzt die Anfangs-UV-Koordinaten (Default = 0.0)
	void SetTextureRepeat(float fuTextureRepeat, float fvTextureRepeat); // Bestimmt, wie oft die Textur wiederholt werden soll in U und V-Richtung (Default = 1.0)

	void SetAxis(EAxis m_eAxis); // Setzt Extruding-Achse
	void InitRadial(CHVector vSize, CMaterial * pmaterial, int iLongitude, int iLattitude, float * afrRadius, float * afrDistance, bool bFlip =false); // Initialisiert eine extrudierte Geometrie, vSize=allgemeine Skalierung, iLongitude = Anzahl radialer Vertices, iLattitude= Anzahl vetrices entlang des Pfades, afRadius  = Array von iLattitude Radien, afrDistance = Array von iLattitude Abständen zum Anfang des Pfades  
	void InitCircle(CMaterial * pmaterial, int iLongitude, CHMats & matsPath); // Initialisiert eine extrudierte Geometrie,  iLongitude = Anzahl radialer Vertices, CHMats = hommogene Matrizen zum Plazieren, Skalieren und Rotieren des Pfades
	void Init(CHVector vSize, CMaterial * pmaterial, CHMats & matsPath, CHVectors & vs); // Initialisiert eine extrudierte Geometrie auf sehr komplexe Weise: matsPath gibt den Pfad als Liste homogener Matrizen an, vs die Punkte des Querschnitts 
	void SetPlanarMappingBottomOn(); // Erzeugt planares Mapping an der Basisreihe, muß vor Init aufgerufen werden
	void SetPlanarMappingTopOn(); // Erzeugt planares Mapping an der Kopfreihe, muß vor Init aufgerufen werden


	CVertex * m_avertex;
	float m_fuTextureStart;
	float m_fvTextureStart;
	float m_fuTextureRepeat; 
	float m_fvTextureRepeat;

	bool m_bPlanarMappingBottom; 
	bool m_bPlanarMappingTop; 
	EAxis m_eAxis;
protected:
	int GetVertexIndex(int iLo, int iLa);
	
	CHVector m_vSize;

	int m_iLongitude; // Anzahl Vertices radial um die Röhre
	int m_iLattitude; // Anzahl Vertices in Richtung der Röhre
};

}