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

    bool KeyPressed(int iKey); // true, falls Taste iKey (Tastaturnummer gem�� DirectX) gedr�ckt wurde, ansonsten false
    int GetKey(void); // Gibt die gedr�ckte Tastaturnummer gem�� DirectX zur�ck
    char GetChar(int iKey);

	void SetWASDLevelMin(float fyLevelMin); // Erzeugt Kameramaximalh�henlevel f�r die Erdsteuerung, die Kamera kann nie �ber fyLevelMax steigen
	void SetWASDLevelMax(float fyLevelMax); // Erzeugt Kameraminimalh�henlevel f�r die Erdsteuerung, die Kamera kann nie unter fyLevelMin untertauchen
	float GetWASDLevelMin(); // Holt Kameraminmalh�henlevel f�r die Erdsteuerung, die Kamera kann nie  �ber fyLevelMax dr�bersteigen
	float GetWASDLevelMax();// Erzeugt Kameramaximalh�henlevel f�r die Erdsteuerung, die Kamera kann nie unter fyLevelMin untertauchen
	void SetWASDTranslationSensitivity(float fTranslationSensitivity); // Setzt die Empfindlichkeit (Schnelligkeit) bei den WASD-Tasten in Einheiten / Sekunde f�r PlaceWASD 
	void SetWASDRotationSensitivity(float fRotationSensitivity); // Setzt die Empfindlichkeit (Schnelligkeit) bei den Pfeil-Tasten in Bogenma� / Sekunde f�r PlaceWASD
	float GetWASDTranslationSensitivity();
	float GetWASDRotationSensitivity();
	bool PlaceWASD(CPlacement & placementCamera, float & fTimeDelta, bool bEarth = false); // Erzeugt eine WASD-Steuerung, gibt true aus, falls Space Taste gedr�ckt wurde
	bool PlaceWASDPan(CPlacement & placementCamera, CPlacement & placementCenter, float & fTimeDelta); // Erzeugt eine radiale WASD-Steuerung unm ein anderes Placement, gibt true aus, falls Space Taste gedr�ckt wurde
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