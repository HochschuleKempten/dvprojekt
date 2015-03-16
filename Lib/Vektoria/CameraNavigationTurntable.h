//---------------------------------------------------
// CCameraNavigationTurntable: Klasse, die eine 
// Orbitrotation, Zoom und WASD-Steuerung ermöglicht.
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
	//Übergebe initialisierte Kamera ,Szene, sowie Höhe und Breite des Fensters und ein Tastatur/Mouse/Cursor-Gerät
	//Constrainaxis schränkt die Bewegung der Kamera ein, sodass nicht unter den Boden oder Überkopf rotiert werden kann
	// ShowCenter zeigt weiße Kugel am Rotationspunkt
	void Init(CCamera& camera, CScene& scene, int iWindowWidth, int iWindowHeight, 
			  CDeviceKeyboard& zdk, CDeviceMouse& zdm, CDeviceCursor& zdc, bool bShowCenter = true,
			  bool bConstrainAxis = true);

	//Führe alle Eventhandler aus
	void Tick(float fTimeDelta);
	
	//Aktualisiere Fensterbreite/höhe (Nötig wenn sich die größe des Viewports ändert)
	void SetWindowWidth(int iWindowWidth);
	void SetWindowHeight(int iWindowHeight);
	
	int GetWindowHeight() const;
	int GetWindowWidth() const;	
	
	//Passe die Geschwindigkeit der WASD Bewegung an (Default = 2.0, größer ist langsamer)
	void SetMoveSpeed(float fSpeed);
	//Passe die Geschwindigkeit der Orbitrotation an (Default = 2.0, größer ist schneller)
	void SetRotateSpeed(float fSpeed);
	//Passe die Geschwindigkeit der Skalierung an (Default = 5.0 größer ist schneller)
	void SetScaleSpeed(float fSpeed);
	//Setze ein Limit für die minimale/maximale Entfernung der Camera zum Boden(in Einheitsvektorenlängen)
	//Default = 3.f / 40.f
	void SetMinMaxCameraDistance(float fMin, float fMax);
	//Passe die Geschwindigkeit der Pan - Bewegung an (Default = 9.0 größer ist schneller)
	void SetPanSpeed(float fSpeed);


	//////////////////////////////////////////////////////////////////////////
	//Optionale Methoden, die bereits in Tick() ausgeführt werden, aber auch 
	//von außen aufgerufen werden können

	//Rotiere um einen Punkt / Übergebe die absoluten Mauskoordinaten
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