//---------------------------------------------------
// CCameraNavigationTurntable: Klasse, die eine 
// Orbitrotation, Zoom und WASD-Steuerung erm�glicht.
// 
// Orbitrotation: Rechte Maustaste
// Zoom: Mausrad (Alternativ: , zoom out / . zoom in)
// Bewegung: WASD
// Pan Bewegung: Links Alt + linke Maustaste
//
// Autor: Patrick Fleischmann
//---------------------------------------------------

#pragma once

#include "Root.h"

namespace Vektoria
{

class CCameraNavigationTurntable
{
public:
	CCameraNavigationTurntable();
	//�bergebe initialisierte Kamera ,Szene, sowie H�he und Breite des Fensters und ein Tastatur/Mouse/Cursor-Ger�t
	//Constrainaxis schr�nkt die Bewegung der Kamera ein, sodass nicht unter den Boden oder �berkopf rotiert werden kann
	// ShowCenter zeigt wei�e Kugel am Rotationspunkt
	void Init(CCamera& camera, CScene& scene, int iWindowWidth, int iWindowHeight, 
			  CDeviceKeyboard& zdk, CDeviceMouse& zdm, CDeviceCursor& zdc, bool bShowCenter = true,
			  bool bConstrainAxis = true);

	//F�hre alle Eventhandler aus
	void Tick(float fTimeDelta);
	
	//Aktualisiere Fensterbreite/h�he (N�tig wenn sich die gr��e des Viewports �ndert)
	void SetWindowWidth(int iWindowWidth);
	void SetWindowHeight(int iWindowHeight);
	
	int GetWindowHeight() const;
	int GetWindowWidth() const;	
	
	//Passe die Geschwindigkeit der WASD Bewegung an (Default = 2.0, gr��er ist langsamer)
	void SetMoveSpeed(float fSpeed);
	//Passe die Geschwindigkeit der Orbitrotation an (Default = 2.0, gr��er ist schneller)
	void SetRotateSpeed(float fSpeed);
	//Passe die Geschwindigkeit der Skalierung an (Default = 5.0 gr��er ist schneller)
	void SetScaleSpeed(float fSpeed);
	//Setze ein Limit f�r die minimale/maximale Entfernung der Camera zum Boden(in Einheitsvektorenl�ngen)
	//Default = 3.f / 40.f
	void SetMinMaxCameraDistance(float fMin, float fMax);
	//Passe die Geschwindigkeit der Pan - Bewegung an (Default = 9.0 gr��er ist schneller)
	void SetPanSpeed(float fSpeed);


	//////////////////////////////////////////////////////////////////////////
	//Optionale Methoden, die bereits in Tick() ausgef�hrt werden, aber auch 
	//von au�en aufgerufen werden k�nnen

	//Rotiere um einen Punkt / �bergebe die absoluten Mauskoordinaten
	void OrbitRotation(float fAbsoluteX, float fAbsoluteY, float fTimeDelta);
	//Skaliere(Zoom) mit dem Mausrad
	void Scale(float fMouseWheel, float fTimeDelta);
	//Bewegung entlang einer, zur Kamera senkrechten, 2D Ebene im Raum
	void Pan(float fAbsoluteX, float fAbsoluteY, float fTimeDelta);
	
	//Bewegung in einer Richtung parallel zur z-Achse  
	void MoveAhead(float fTimeDelta);
	void MoveBack(float fTimeDelta);
	void MoveLeft(float fTimeDelta);
	void MoveRight(float fTimeDelta);

	//Bewege die Kamera um einen beliebigen Vektor
	void Move(CHVector v);

/*private:*/

	void SetLastMouseX(float fLastX);
	void SetLastMouseY(float fLastY);

	float GetLastMouseX() const;
	float GetLastMouseY() const;

	CPlacement m_zpCameraRotation;
	CPlacement m_zpCameraDistance;
	CPlacement m_zpCameraPosition;

	int m_iWindowHeight;
	int m_iWindowWidth;

	CDeviceKeyboard* m_pzdk;
	CDeviceMouse* m_pzdm;
	CDeviceCursor* m_pzdc;

	float m_fMoveSpeed;
	float m_fRotateSpeed;
	float m_fScaleSpeed;
	float m_fMinCamDistance;
	float m_fMaxCamDistance;
	float m_fPanSpeed;
	bool m_bConstrainAxis;
	float m_fLastMouseX;
	float m_fLastMouseY;

	CGeoSphere m_zgCenter;
	CPlacement m_zpxAxis;
	CPlacement m_zpyAxis;
	CPlacement m_zpzAxis;
	CGeoCylinder m_zgxAxis;
	CGeoCylinder m_zgyAxis;
	CGeoCylinder m_zgzAxis;
	CMaterial m_zmCenter;
};

}