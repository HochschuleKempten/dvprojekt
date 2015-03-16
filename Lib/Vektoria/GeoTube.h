#pragma once
#include "trianglestrip.h"
#include "GeoSweep.h"
#include "Face.h"

namespace Vektoria
{

class CGeoTube :
	public CGeoSweep
{
public:
	CGeoTube(void);
	~CGeoTube(void);

	void InitStraight(float fRadiusInner, float fRadiusOuter, float fLength, CMaterial * pmaterial, int iLongitude = 24, bool bInner = true); // Initialisiert eine Röhren-Geometrie, fRadiusInner = innerer Röhrenradius, fRadiusOuter = äußerer Röhrenradius, fLength = Länge der Röhre, pmaterial = Materialpointer, iLongitude = Anzahl der radialen Vertices, bInner = true, wenn Innenleben des Rohres erzeugt werden soll
	void InitArc(float fRadiusInner, float fRadiusOuter, float fRadiusArc,  float faArc,  CMaterial * pmaterial, int iLongitude = 24, int iLattitude = 24, bool bInner = true); // Initialisiert eine Rohrbogen-Geometrie, fRadiusInner = innerer Röhrenradius, fRadiusOuter = äußerer Röhrenradius, fRadiusArc = Gesamtradius des Rohrbogens, faArc = zu zeichnender Öffnungswinkel des Rohrbogens im Bogenmß, iLongitude = Anzahl der radialen Vertexunterteilungen, pmaterial = Materialpointer, iLattitude = Anzahl der Vertexunterteilungen entlang des Rohres, bInner = true, wenn Innenleben des Rohres erzeugt werden soll   


};

}