#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"
#include "..\ApiDirectInput08\DIGameController.h"
#include "..\ApiDirectInput08\DIMouse.h"
#include "..\ApiDirectInput08\DIKeyboard.h"

#define MAX_NUM_GAMECONTROLLERS 16

namespace Vektoria
{

class CDevice
{
public:
	CDevice(void);
	~CDevice(void);

    CDIMouse* m_DIMouse; // System-Maus
    CDIKeyboard* m_DIKeyboard; // System-Tastatur
    CDIGameController* m_aDIGameControllers[MAX_NUM_GAMECONTROLLERS]; // Game Controller Geräte
	
	void ReSize(int iWidthWindow, int iHeightWindow);
	
	void AddKeyboard(CDIKeyboard * dikeyboard);
 	void AddMouse(CDIMouse * dimouse);
	void AddGameController(CDIGameController * digamecontroller);
	

    bool m_bDIInit; // Wurde Direct Input ergolgreich initialsiert
    bool m_bDIKeyboardInit; // Wurde die Tastatur erfolgreich initialsiert
	bool m_bDIMouseInit; // Wurde die Maus erfolgreich Initialisiert
    int m_iDIGameControllers; // Anzahl der Game Controller Geräte

    void Init(HWND hwnd, DWORD dwWidth, DWORD dwHeight); // Initialisiert Direct Input, die System-Tastatur und die System-Maus
	void Tick(void); // Wird automatisch aufgerufen (hoffentlich bald)
	void Fini(void); // Gibt alle Geräte wieder frei

    bool StartEnumeration(void); // Startet das Aufzählen der vorhandenen Geräte
    CDIKeyboard* GetKeyboard(void); // Gibt einen Pointer auf die System-Tastatur zurück
    CDIMouse* GetMouse(void); // Gibt einen Pointer auf die System-Maus zurück
private:
    HINSTANCE m_hInstance;
    HWND m_hwnd;

    DWORD m_dwScreenWidth; // Screenbreite
    DWORD m_dwScreenHeight; // Screenhöhe

    LPDIRECTINPUT8 m_lpDI; // Direct Input Interface

    bool InitDirectInput(void);

    static BOOL CALLBACK EnumDevsCallback(LPDIDEVICEINSTANCE lpddi, LPVOID pvRef); // Callback Funktion um die Geräte aufzuzählen
    void AddDeviceInfo(LPCDIDEVICEINSTANCE lpddi); // Fügt die Device Info dem Gerät hinzu
};

}