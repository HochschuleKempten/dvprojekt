// DIKeyboard.h: interface for the CDIKeyboard class
//
//////////////////////////////////////////////////////////////////////
#pragma once
#include "DIDevice.h"
#include "..\Vektoria\Placement.h"
//#include "DeviceKeyboard.h"

#define KEYBOARD_BUFFERSIZE 256

namespace Vektoria
{

// class CDIKeyboard : public CDIDevice, public CDeviceKeyboard
class CDIKeyboard : public CDIDevice
{
public:
    CDIKeyboard(void);
    ~CDIKeyboard(void);

    bool Init(HINSTANCE hinst, HWND hwnd, LPDIRECTINPUT8 lpDI); // Initialisiert die Tastatur
	void Tick(void); // Muss jeden Tick aufgerufen werden um den device state zu aktualisieren

    bool KeyPressed(int iKey); // true, falls Taste iKey (Tastaturnummer gemäß DirectX) gedrückt wurde, ansonsten false
    int GetKey(void); // Gibt die gedrückte Tastaturnummer gemäß DirectX zurück
    char GetChar(int iKey);

	void SetWASDLevelMin(float fyLevelMin); // Erzeugt Kameramaximalhöhenlevel für die Erdsteuerung, die Kamera kann nie über fyLevelMax steigen
	void SetWASDLevelMax(float fyLevelMax); // Erzeugt Kameraminimalhöhenlevel für die Erdsteuerung, die Kamera kann nie unter fyLevelMin untertauchen
	float GetWASDLevelMin(); // Holt Kameraminmalhöhenlevel für die Erdsteuerung, die Kamera kann nie  über fyLevelMax drübersteigen
	float GetWASDLevelMax();// Erzeugt Kameramaximalhöhenlevel für die Erdsteuerung, die Kamera kann nie unter fyLevelMin untertauchen
	void SetWASDTranslationSensitivity(float fTranslationSensitivity); // Setzt die Empfindlichkeit (Schnelligkeit) bei den WASD-Tasten in Einheiten / Sekunde für PlaceWASD 
	void SetWASDRotationSensitivity(float fRotationSensitivity); // Setzt die Empfindlichkeit (Schnelligkeit) bei den Pfeil-Tasten in Bogenmaß / Sekunde für PlaceWASD
	float GetWASDTranslationSensitivity();
	float GetWASDRotationSensitivity();
	bool PlaceWASD(CPlacement & placementCamera, float & fTimeDelta, bool bEarth = false); // Erzeugt eine WASD-Steuerung, gibt true aus, falls Space Taste gedrückt wurde
	bool PlaceWASDPan(CPlacement & placementCamera, CPlacement & placementCenter, float & fTimeDelta); // Erzeugt eine radiale WASD-Steuerung unm ein anderes Placement, gibt true aus, falls Space Taste gedrückt wurde
	void SetWASDAltitude(float fa); // Setzt den Anfangswinkel bei einer WASD-PAN-Steuerung
	void SetWASDPanRadius(float fRadius); // Setzt den Anfangswinkel bei einer WASD-PAN-Steuerung


	void GetMove(int &riAD, int &riSW, int &riFR, int &riLeftRight, int &riUpDown, int &riPageUpDown, bool &rbSpace);
	float m_fTranslationSensitivity;
	float m_fRotationSensitivity;
	float m_fyWASDLevelMin;
	float m_fyWASDLevelMax;
	float m_faWASDAzimuth;
	float m_faWASDAltitude;
	float m_fWASDRadius;
private:
    BYTE m_abyte[KEYBOARD_BUFFERSIZE];
};

}