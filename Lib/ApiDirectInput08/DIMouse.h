// DIMouse.h: interface for the CDIMouse class
//
//////////////////////////////////////////////////////////////////////
#pragma once
#include "DIDevice.h"
// #include "Placement.h"

//constants for mouse buttons
#define DIMOUSE_LEFTBUTTON   0
#define DIMOUSE_RIGHTBUTTON  1
#define DIMOUSE_MIDDLEBUTTON 2
#define DIMOUSE_4BUTTON      3
#define DIMOUSE_5BUTTON      4
#define DIMOUSE_6BUTTON      5
#define DIMOUSE_7BUTTON      6
#define DIMOUSE_8BUTTON      7

namespace Vektoria
{

class CDIMouse : public CDIDevice
{
public:
    CDIMouse(void);
//    CDIMouse(HINSTANCE hinst, HWND hwnd, LPDIRECTINPUT8 lpDI, DWORD dwWidth, DWORD dwHeight);
    ~CDIMouse(void);

    bool Init(HINSTANCE hinst, HWND hwnd, LPDIRECTINPUT8 lpDI, DWORD dwWidth, DWORD dwHeight); // Initialisiert die Maus
	void Tick(void); // Muss jeden Tick aufgerufen werden um den device state zu aktualisieren

    void SetSensitivity(float fSensitivity=0.0005f); // Setzt die Empfindlichkeit
    float GetSensitivity(void); // Gibt die Empfindlichkeit aus

    void SetInvertedYAxisOn(); // Y-Achse invertieren
    void SetInvertedYAxisOff(); // Y-Achse nicht invertieren

	float GetRelativeX(void); // Gibt relative Mausbewegung in X-Richtung aus
	float GetRelativeY(void); // Gibt relative Mausbewegung in Y-Richtung aus
	float GetRelativeZ(void); // Gibt relative Mausradbewegung (Z-Richtung) aus

    int GetAbsoluteX(); // Gibt die Zeigerposition auf der X-Achse aus
    int GetAbsoluteY(); // Gibt die Zeigerposition auf der Y-Achse aus


	bool ButtonPressed(int a_iButton); // true, falls Taste iButton (Tastennummer gemäß DirectX) gedrückt wurde, ansonsten false

	void ReSize(int iWidthWindow, int iHeightWindow);

    float GetFractionalX(); // Gibt die fraktionale Zeigerposition (0..1) bezüglich des übergeordneten Frames auf der X-Achse aus
    float GetFractionalY(); // Gibt die fraktionale Zeigerposition (0..1) bezüglich des übergeordneten Frames auf der Y-Achse aus


	DIMOUSESTATE2* GetJoystickStateInfo(void) {return &m_DIMouseState;};
private:
	DIMOUSESTATE2 m_DIMouseState; // device state information

    DWORD m_dwAxes; // number of axes 
    DWORD m_dwButtons; // number of buttons 
    DWORD m_dwScreenWidth; // screen width 
    DWORD m_dwScreenHeight; // screen height

    float m_fCursorX; // cursor position
    float m_fCursorY; // cursor position

	float m_fSensitivity; // game controller sensitivity
	bool m_bInvertedY; // inverted y axis
};

}