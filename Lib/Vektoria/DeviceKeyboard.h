#pragma once
#include "Placement.h"

namespace Vektoria
{

class CDeviceKeyboard
{
public:
	CDeviceKeyboard(void);
	~CDeviceKeyboard(void);

	bool KeyPressed(int iKey); // true, falls Taste iKey (Tastaturnummer gem�� DirectX) gedr�ckt wurde, ansonsten false
    int GetKey(void); // Gibt die gedr�ckte Tastaturnummer (gem�� DirectX) zur�ck.
    //int GetChar(void); // Gibt die gedr�ckte Tastaturnummer (gem�� DirectX) f�r Tasten, die einen char darstellen zur�ck. (Ohne Strg, Return, etc.)
    char GetChar(int ikey);

	void SetWASDLevelMin(float fyLevelMin); // Erzeugt Kameraminimalh�henlevel f�r die Erdsteuerung, die Kamera kann nie unter fyLevelMin untertauchen
	void SetWASDLevelMax(float fyLevelMax); // Erzeugt Kameramaximalh�henlevel f�r die Erdsteuerung, die Kamera kann nie �ber fyLevelMax steigen
	float GetWASDLevelMin(); // Holt Kameraminmalh�henlevel f�r die Erdsteuerung, die Kamera kann nie  �ber fyLevelMax dr�bersteigen
	float GetWASDLevelMax();// Erzeugt Kameramaximalh�henlevel f�r die Erdsteuerung, die Kamera kann nie unter fyLevelMin untertauchen
	virtual void SetWASDTranslationSensitivity(float fTranslationSensitivity); // Setzt die Empfindlichkeit (Schnelligkeit) bei den WASD-Tasten in Einheiten / Sekunde f�r PlaceWASD 
	virtual void SetWASDRotationSensitivity(float fRotationSensitivity); // Setzt die Empfindlichkeit (Schnelligkeit) bei den Pfeil-Tasten in Bogenma� / Sekunde f�r PlaceWASD
	virtual float GetWASDTranslationSensitivity();
	virtual float GetWASDRotationSensitivity();
	virtual bool PlaceWASD(CPlacement & placementCamera, float & fTimeDelta, bool bEarth = false); // Vollkomme WASD Steuerung, true, falls Space Taste gedr�ckt wurde
	virtual void GetMove(int &riAD, int &riSW, int &riFR, int &riLeftRight, int &riUpDown, int &riPageUpDown, bool &rbSpace);

	void * pkeyboard;
	int m_eApiInput;
};

}