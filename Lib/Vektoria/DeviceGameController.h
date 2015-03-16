#pragma once

namespace Vektoria
{

class CDeviceGameController
{
public:
	CDeviceGameController(void);
	~CDeviceGameController(void);

	void SetSensitivity(float fSensitivity=0.0005f); // Setzt die Empfindlichkeit
    float GetSensitivity(void); // Gibt die Empfindlichkeit aus

    void SetInvertedYAxisOn(void); // Y-Achse invertieren
    void SetInvertedYAxisOff(void); // Y-Achse nicht invertieren

	float GetRelativeX(void);
	float GetRelativeY(void);
	float GetRelativeZ(void);

	bool ButtonPressed(int a_iButton); // true, falls Taste iButton (Tastennummer gemäß DirectX) gedrückt wurde, ansonsten false

	void * pgamecontroller;
	int m_eApiInput;

};

}