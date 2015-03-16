#pragma once
#include "TriangleStrip.h"
#include "HMats.h"
#include "HVectors.h"

class CGeoExtruded :
	public CTriangleStrip
{
public:
	CGeoExtruded(void);
	~CGeoExtruded(void);


	void Init(CHVector vSize, CMaterial * pmaterial, int iLongitude, int iLattitude, float * afrRadius, float * afrDistance, bool bFlip =false); // Initialisiert eine extrudierte Geometrie, vSize=allgemeine Skalierung, iLongitude = Anzahl radialer Vertices, iLattitude= Anzahl vetrices entlang des Pfades, afRadius  = Array von iLattitude Radien, afrDistance = Array von iLattitude Abständen zum Anfang des Pfades  
	void Init(CMaterial * pmaterial, int iLongitude, CHMats & matsPath); // Initialisiert eine extrudierte Geometrie,  iLongitude = Anzahl radialer Vertices, CHMats = hommogene Matrizen zum Plazieren, Skalieren und Rotieren des Pfades
	void Init(CHVector vSize, CMaterial * pmaterial, CHMats & matsPath, CHVectors & vs); // Initialisiert eine extrudierte Geometrie auf sehr komplexe Weise: matsPath gibt den Pfad als Liste homogener Matrizen an, vs die Punkte des Querschnitts 
	CHVector * m_av;

protected:
	int GetVertexIndex(int iLo, int iLa);
	void InitMesh();
	
	CHVector m_vSize;
	CVertex * m_avertex;
	CVertex * m_avertexBack;

	int m_iLongitude; // Anzahl Vertices radial um die Röhre
	int m_iLattitude; // Anzahl Vertices in Richtung der Röhre
};

