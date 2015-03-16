#pragma once
#include "GeoSweep.h"


namespace Vektoria
{

	class CGeoArrow :
		public CGeoSweep
	{
	public:
		CGeoArrow();
		~CGeoArrow();

		void Init(CHVector & v, float fRadiusBottom, float fRadiusHead, float fLengthHead, CMaterial * pmaterial, int iLongitude = 7, bool bLengthHeadIsRelative = true, bool bHasBottom = true); // Erzeugt Pfeil-Geometrie, v gibt Richtung und Betrag des Pfeiles als Vektor an, fRadiusBottom den Radius des Pfeilschaftes, fRadiusHead  den Radius des Pfeilkopfes, pmaterial ist ein Pointer auf das Material, iLongitude ist die Anzahl der Vertices radial gesehen, bLengthHeadIsRelative ist True, wenn Auﬂmaﬂe des Kopfes relativ gemessen werden sollen, bHasBottom gibt an, ob der Pfeil einen Unterboden haben soll 
	};

}