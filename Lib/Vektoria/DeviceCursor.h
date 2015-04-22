#pragma once
#include "windows.h"
#include "Geo.h"
#include "Placement.h"
#include "Overlay.h"

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
	
	CViewport * PickViewport(); // Gibt erstes sichtbares Viewport aus, welches unter dem Cursor liegt, falls kein Viewport gefunden wurde ist das Ergebnis NULL
	CViewport * PickViewport(float & frxViewport, float & fryViewport); // Gibt erstes sichtbares Viewport aus, welches unter dem Cursor liegt, falls kein Viewport gefunden wurde ist das Ergebnis NULL, dazu werden die passenden Bildschirmkoordinaten frxViewport und fryViewport des Picking-Punktes mit ausgegeben
	COverlay * PickOverlay(); // Gibt erstes sichtbares Overlay aus, welches unter dem Cursor liegt, falls kein Overlay gefunden wurde ist das Ergebnis NULL
	CCamera * PickCamera(); // Gibt die Kamera aus, die mit dem sichtbaren Viewport verbunden ist, welches unter dem Cursor liegt, falls kein Viewport gefunden wurde ist das Ergebnis NULL
	CScene * PickScene(); // Gibt die Szene aus, welche das sichtbare Viewport zeigt, welches unter dem Cursor liegt, falls keine Szene gefunden wurde ist das Ergebnis NULL
	CPlacement * PickPlacement(); // Gibt dasjenige näheste Placement mit der niedersten Hierarchiestufe aus, welches unter dem Cursor liegt, falls kein Placment gefunden wurde ist das Ergebnis NULL
	void PickPlacements(CPlacements * pzps); // Gibt alle Placements in pzps aus, welches unter dem Cursor liegen. Achtung zps muss muss ein Pointer auf ein instanzieertes Placement-Objekt sein. 
	CGeo * PickGeo(CHVector & vIntersection, float & fDistanceSquare); // Gibt dasjenige Geo mit der niedersten Hierarchiestufe aus, welches unter dem Cursor liegt, falls kein Geo gefunden wurde ist das Ergebnis NULL, vIntersection ist der genaue Schnittpunkt, fDistanceSquare ist das Quadrat der Entfernung zwischen Strahlursprung und Schnittpunkt, kann bei großen Geometrien einige Millisekunden dauern, ist dafür sehr exakt
	
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