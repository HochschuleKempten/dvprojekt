#pragma once
#include "Placement.h"

namespace Vektoria
{

class CDeviceKeyboard
{
public:
	CDeviceKeyboard(void);
	~CDeviceKeyboard(void);

	bool KeyPressed(int iKey); // true, falls Taste iKey (Tastaturnummer gemäß DirectX) gedrückt wurde, ansonsten false
    int GetKey(void); // Gibt die gedrückte Tastaturnummer (gemäß DirectX) zurück.
    //int GetChar(void); // Gibt die gedrückte Tastaturnummer (gemäß DirectX) für Tasten, die einen char darstellen zurück. (Ohne Strg, Return, etc.)
    char GetChar(int ikey);

	void SetWASDLevelMin(float fyLevelMin); // Erzeugt Kameraminimalhöhenlevel für die Erdsteuerung, die Kamera kann nie unter fyLevelMin untertauchen
	void SetWASDLevelMax(float fyLevelMax); // Erzeugt Kameramaximalhöhenlevel für die Erdsteuerung, die Kamera kann nie über fyLevelMax steigen
	float GetWASDLevelMin(); // Holt Kameraminmalhöhenlevel für die Erdsteuerung, die Kamera kann nie  über fyLevelMax drübersteigen
	float GetWASDLevelMax();// Erzeugt Kameramaximalhöhenlevel für die Erdsteuerung, die Kamera kann nie unter fyLevelMin untertauchen
	virtual void SetWASDTranslationSensitivity(float fTranslationSensitivity); // Setzt die Empfindlichkeit (Schnelligkeit) bei den WASD-Tasten in Einheiten / Sekunde für PlaceWASD 
	virtual void SetWASDRotationSensitivity(float fRotationSensitivity); // Setzt die Empfindlichkeit (Schnelligkeit) bei den Pfeil-Tasten in Bogenmaß / Sekunde für PlaceWASD
	virtual float GetWASDTranslationSensitivity();
	virtual float GetWASDRotationSensitivity();
	virtual bool PlaceWASD(CPlacement & placementCamera, float & fTimeDelta, bool bEarth = false); // Vollkomme WASD Steuerung, true, falls Space Taste gedrückt wurde
	virtual void GetMove(int &riAD, int &riSW, int &riFR, int &riLeftRight, int &riUpDown, int &riPageUpDown, bool &rbSpace);

	void * pkeyboard;
	int m_eApiInput;
};

}