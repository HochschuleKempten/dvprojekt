// DIGameController.h: interface for the CDIGameController class
//
//////////////////////////////////////////////////////////////////////
#pragma once
#include "DIDevice.h"

namespace Vektoria
{

class CDIGameController : public CDIDevice
{
public:
	CDIGameController(void);
//	CDIGameController(HINSTANCE hinst, HWND hwnd, LPDIRECTINPUT8 lpDI);
	~CDIGameController(void);

	bool Init(HINSTANCE hinst, HWND hwnd, LPDIRECTINPUT8 lpDI); // Initialisiert den Game Controller
    //bool Init(GUID *GUID_GameController);
	void Tick(void); // Muss jeden Tick aufgerufen werden um den device state zu aktualisieren

	//void SetPreferredDevice(GUID* pguid); // Set the current GUID for game controller device

	void SetSensitivity(float fSensitivity=0.0005f); // Setzt die Empfindlichkeit
    float GetSensitivity(void); // Gibt die Empfindlichkeit aus

    void SetInvertedYAxisOn(void); // Y-Achse invertieren
    void SetInvertedYAxisOff(void); // Y-Achse nicht invertieren

	float GetRelativeX(void);
	float GetRelativeY(void);
	float GetRelativeZ(void);

	bool ButtonPressed(int a_iButton); // true, falls Taste iButton (Tastennummer gemäß DirectX) gedrückt wurde, ansonsten false

	DIJOYSTATE2* GetJoystickStateInfo(void) {return &m_DIJoyState;};
private:
	DIJOYSTATE2 m_DIJoyState; // Holds Game Controller State Information

	float m_fSensitivity; // game controller sensitivity
	bool m_bInvertedY; // inverted y axis

	//////////////////////////////////////////////////////////////////////
	// Used for Force Feed Back, Not Yet Implemented
	//////////////////////////////////////////////////////////////////////
	LPDIRECTINPUTEFFECT  m_lpTriggerEffect; // For Force Feedback Effects
	LPDIRECTINPUTEFFECT  m_lpStickyEffect; // For Force Feedback Effects
	LPDIRECTINPUTEFFECT  m_lpResistEffect; // For Force Feedback Effects
	bool m_TriggerOK;
	BOOL m_FFAvailable;	// Is device Force Feedback Compatible?
	GUID m_TriggerGuid;	// GUID For Force Feed Back Device?
};

}