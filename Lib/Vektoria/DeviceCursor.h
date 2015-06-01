#pragma once
#include "windows.h"
#include "Geo.h"
#include "Placement.h"
#include "Overlay.h"
#include "Hitpoints.h"

namespace Vektoria
{
class CFrame; 

class CDeviceCursor
{
public:
	CDeviceCursor(void);
	~CDeviceCursor(void);

	void Tick();

	bool GetAbsolute(int & ix, int & iy, bool bHideCursor = false); // Gibt die Zeigerpositionskoordinaten bezüglich der linken oberen Ecke des Frames aus, gibt true aus, wenn Cursor sich innerhalb des Frames befindet 
	bool GetFractional(float & frx, float & fry, bool bHideCursor = false); // Gibt die fraktionalen Zeigerpositionskoordinaten (Wertebereich jeweils 0..1) bezüglich des Frames aus, gibt true aus, wenn Cursor sich innerhalb des Frames befindet

	bool ButtonPressed(int iButton); // true, falls Taste iButton gedrückt wurde, ansonsten false

	bool ButtonPressedLeft(); // true, falls linke Maustaste gedrückt wird, ansonsten false
	bool ButtonPressedRight(); // true, falls rechte Maustaste gedrückt wird, ansonsten false
	bool ButtonPressedMid(); // true, falls mittlere Maustaste gedrückt wird, ansonsten false

	void Hide(); // Macht Cursor unsichtbar
	void Show(); // Macht Cursor sichtbar
	bool IsHidden(); // true, wenn Cursor unsichtbar, ansonsten false
	
	// Picking-Routinen (Singular):
	CViewport * PickViewport(); // Gibt erstes sichtbares Viewport aus, welches unter dem Cursor liegt, falls kein Viewport gefunden wurde ist das Ergebnis NULL
	CViewport * PickViewport(float & frxViewport, float & fryViewport); // Gibt erstes sichtbares Viewport aus, welches unter dem Cursor liegt, falls kein Viewport gefunden wurde ist das Ergebnis NULL, dazu werden die passenden Bildschirmkoordinaten frxViewport und fryViewport des Picking-Punktes mit ausgegeben
	COverlay * PickOverlay(); // Gibt erstes sichtbares Overlay aus, welches unter dem Cursor liegt, falls kein Overlay gefunden wurde ist das Ergebnis NULL
	CCamera * PickCamera(); // Gibt die Kamera aus, die mit dem sichtbaren Viewport verbunden ist, welches unter dem Cursor liegt, falls kein Viewport gefunden wurde ist das Ergebnis NULL
	CScene * PickScene(); // Gibt die Szene aus, welche das sichtbare Viewport zeigt, welches unter dem Cursor liegt, falls keine Szene gefunden wurde ist das Ergebnis NULL
	CPlacement * PickPlacement(); // Gibt dasjenige näheste Placement mit der niedersten Hierarchiestufe aus, welches unter dem Cursor liegt, falls kein Placment gefunden wurde ist das Ergebnis NULL
	CGeo * PickGeo(); // Gibt dasjenige Geo mit der niedersten Hierarchiestufe aus, welches unter dem Cursor liegt, falls kein Geo gefunden wurde ist das Ergebnis NULL
	CGeo * PickGeo(CHVector & vIntersection, float & fDistanceSquare); // Gibt dasjenige Geo mit der niedersten Hierarchiestufe aus, welches unter dem Cursor liegt, falls kein Geo gefunden wurde ist das Ergebnis NULL, vIntersection ist der genaue Schnittpunkt, fDistanceSquare ist das Quadrat der Entfernung zwischen Strahlursprung und Schnittpunkt, kann bei großen Geometrien einige Millisekunden dauern, ist dafür sehr exakt // TODO: In V14 raus, da veraltet!
	CHitPoint * PickHitPoint(); // Gibt den nähesten HitPoint aus, der unter dem Cursor liegt, falls kein Geo gefunden wurde ist das Ergebnis NULL, vIntersection ist der genaue Schnittpunkt, fDistanceSquare ist das Quadrat der Entfernung zwischen Strahlursprung und Schnittpunkt, kann bei großen Geometrien einige Millisekunden dauern, ist dafür sehr exakt

	// Picking-Routinen (1 aus n):
	COverlay * PickOverlayPreselected(COverlays & zos); // Untersucht nur diejenigen Overlays, die in der Liste zos angegeben sind und pickt nur darus eine Geo aus, falls kein Geo gefunden wurde, ist das Ergebnis NULL. Diese Funktion kann das Picking stark beschleunigen
	CPlacement * PickPlacementPreselected(CPlacements & zps); // Untersucht nur diejenigen Placements, die in der Liste zps angegeben sind und pickt nur darus eine Geo aus, falls kein Geo gefunden wurde, ist das Ergebnis NULL. Diese Funktion kann das Picking stark beschleunigen
	CGeo * PickGeoPreselected(CGeos & zgs); // Untersucht nur diejenigen Geos, die in der Liste zgs angegeben sind und pickt nur darus eine Geo aus, falls kein Geo gefunden wurde, ist das Ergebnis NULL. Diese Funktion kann das Picking stark beschleunigen
	CHitPoint * PickHitPointPreselected(CGeos & zgs); // Untersucht nur diejenigen HitPoints, die durch die Liste zgs erzeugt werden können

	// Picking-Routinen (Plural)
	void PickOverlays(COverlays * pzos); // Gibt alle Overlays in pzos aus, welche unter dem Cursor liegen, unabhängig davon, ob sie eventuell von anderen Overlays verdeckt werden. Achtung, pzos muss muss ein Pointer auf ein instanziertes Geos-Objekt sein. 
	void PickPlacements(CPlacements * pzps, bool bPickOnlyPlacementsWithDirectGeos = false); // Gibt alle Placements in pzps aus, welches unter dem Cursor liegen. Achtung, pzps muss muss ein Pointer auf ein instanziertes Placement-Objekt sein. 
	void PickGeos(CGeos * pzgs, int iMaxVertices = INT_MAX); // Gibt alle Geos aus, welches unter dem Cursor liegen. Achtung, pzgs muss muss ein Pointer auf ein instanziertes Geos-Objekt sein. 
	void PickHitPoints(CHitPoints * phitpoints, int iMaxVertices = INT_MAX); // Gibt alle Geos mit Zusatzinformationen aus, welches unter dem Cursor liegen. Achtung, phitpoints muss muss ein Pointer auf ein instanziertes Hitpoints-Objekt sein. 



	void SetFrame(HWND & hwnd, int & ixFrameSize, int & iyFrameSize);
	HWND m_hwnd;
	int m_ixFrameSize;
	int m_iyFrameSize;
	float m_frxFrame;
	float m_fryFrame;
	bool m_bHidden;
	CFrame * m_pframe;
	POINT m_p;

};

}