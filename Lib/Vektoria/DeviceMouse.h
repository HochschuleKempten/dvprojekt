#pragma once

namespace Vektoria
{

class CDeviceMouse
{
public:
	CDeviceMouse(void);
	~CDeviceMouse(void);

    void SetSensitivity(float fSensitivity=0.0005f); // Setzt die Empfindlichkeit für die relativen Abfragemethoden
    float GetSensitivity(void); // Gibt die Empfindlichkeit der relativen Abfragemethoden aus

    void SetInvertedYAxisOn(); // Y-Achse invertieren
    void SetInvertedYAxisOff(); // Y-Achse nicht invertieren

	float GetRelativeX(void); // Gibt relative Mausbewegung in X-Richtung aus
	float GetRelativeY(void); // Gibt relative Mausbewegung in Y-Richtung aus
	float GetRelativeZ(void); // Gibt relative Mausradbewegung (Z-Richtung) aus

    int GetAbsoluteX(); // Gibt absoluze Mausbewegung in X-Richtung aus (in Mickeys)
    int GetAbsoluteY(); // Gibt absoluze Mausbewegung in X-Richtung aus (in Mickeys)


	bool ButtonPressed(int a_iButton); // true, falls Taste iButton (Tastennummer gemäß DirectX) gedrückt wurde, ansonsten false (synchrone Mausklickabfragemethode)
	bool ButtonPressedLeft(); // true, falls linke Maustaste gedrückt wurde, ansonsten false (synchrone Mausklickabfragemethode)
	bool ButtonPressedMid(); // true, falls mittlere Maustaste gedrückt wurde, ansonsten false (synchrone Mausklickabfragemethode)
	bool ButtonPressedRight();// true, falls rechte Maustaste gedrückt wurde, ansonsten false (synchrone Mausklickabfragemethode)

	void ReSize(int iWidthWindow, int iHeightWindow);

	void * pmouse;
	int m_eApiInput;


};

}