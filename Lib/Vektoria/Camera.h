#pragma once
#include "Node3D.h"
#include "../VektoriaMath/HMat.h"
#include "../VektoriaMath/Frustum.h"
#include "DistributedGlobal.h"


//------------------------------------------------------------------
// CCamera: Klasse für eine Kamera
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2014-05-21
//-------------------------------------------------------------------

namespace Vektoria
{

class CPlacement;

class CCamera : public CNode3D
{
	friend class CCameras;
protected:
	void Tick(CHMat & m, bool & bTick); // Wird automatisch jedes Frame aufgerufen
public:
	CCamera();
	~CCamera();
	CCamera operator=(CCamera & camera); // Zuweisungsoperator
	void Copy(CCamera & camera); // Kopiert eine Kamera

	void Init(float faFovHorizontal=2.0F, float fNearClipping=0.1F, float fFarClipping=1000.0F);  // Initalisiert eine Kamera
	void Fini(); // Finalisiert die Kamera

	virtual void UpdateAABB();

	void CalcMat(); // Rechnet die homogene Projektionsmatrix der Kamera aus, wird automatisch aufgerufen, wenn notwendig
	void SetMirrorOn(); // Schaltet spiegelverkehrte Aufnahme an
	void SetMirrorOff(); // Schaltet spiegelverkehrte Aufnahme wieder aus

	bool m_bMirror; // Boolsches Flag, das anzeigt, ob Camera die Szene spiegelverkehrt anzeigen soll

	void SetFov(float faFovHorizontal); // Setzt den horizontalen Kameraöffnungswinkel (vertikaler wird daraus automatisch berechnet). Falls die Kamera in Ortho-Modus sein sollte, swird in in den Fov-Modus zurückgeschaltet
	void SetOrtho(float fOrthoScalingHorizontal); // Schaltet Kamera in Othogonalprojektionsmodus und gibt gleich den horizontalen Skalierungsfaktor an
	void SetOrthoScaling(float fOrthoScalingHorizontal); // Setzt den horizontalen Skalierungsfaktor bei orthogonalen Kameras (vertikaler wird daraus automatisch berechnet), bei Fov-Kamera ohne Wirkung
	float GetOrthoScaling(); // Gibt den orthogonalen Skalierungsfaktor aus
	void SetNearClipping(float fNearClipping); // Setzt den Kameraabstand der vorderen Schnittebene des Sichtpyramidenstumpfes
	void SetFarClipping(float fFarClipping); // Setzt den Kameraabstand der hinteren Schnittebene des Sichtpyramidenstumpfes
	void SetOrthoOn(); // Schaltet Kamera in Othogonalprojektionsmodus
	void SetOrthoOff(); // Schaltet Kamera wieder in normalen fovealen Projektionsmodus (default)

	float GetFov(); // Gibt den horizontalen Kameraöffnungswinkel aus
	float GetNearClipping(); // Gibt den Kameraabstand der vorderen Schnittebene des Sichtpyramidenstumpfes aus
	float GetFarClipping(); // Gibt den Kameraabstand der hinteren Schnittebene des Sichtpyramidenstumpfes aus

	CHMat m_matProjection;  // Projektionsmatrix der Kamera
	float m_faFovHorizontal; // horizontaler Kameraöffnungswinkel (vertikaler wird aus horizontaler Kameraöffnungswinkel7Verzerrungsverhältnis berechnet), bei orthogonaler Kamera ist es der horizontale Skalierungsfaktor
	float m_fNearClipping;  // Abstand zwischen der Kamera und der vorderen Schnittebene des Sichtpyramidenstumpfes
	float m_fFarClipping;   // Abstand zwischen der Kamera und der hinteren Schnittebene des Sichtpyramidenstumpfes
	float m_fViewportAspectRatio; // Verzerrungsverhältnis zwischen Breite und Höhe
	bool m_bOrtho; // true, wenn es sich um eine orthogonale Kamera handelt, ansonsten ist es eine normale Fov-Projektionskamera 
	float  m_fOrthoScalingHorizontal; // Horizontaler Skalierungsfaktor bei orthogonalen Kameras


 	void CalcRay(float frx, float fry, CRay & r); // Erzeugt Sichtstrahl im View Frustum
	void CalcFrustum();

	CFrustum m_frustum; // TODO: ES muss eigentlich für jede Kamerainstanz ein eigenes Frustum geben!!!!!!!!

	CScene * GetScene(); // Gibt die angezeigte Szene aus
	CScene * m_pscene; // Die von der Kamera angezeigte Szene

#ifdef NETWORKMASTER
	unsigned int GetidId();
private:
	unsigned int m_idId;
	int m_icId;
#endif
};

}
