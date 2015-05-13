#pragma once
#include "HVector.h"

//------------------------------------------------------------------
// CHMat: Klasse für homogene 4*4-Matrizen
// Autor: Prof. Dr. Tobias Breiner 
// 
// Anmerkung: Aus Performanzgründen wurden keine Schleifen verwendet.
//-------------------------------------------------------------------

namespace Vektoria
{

class CHMat
{
public:
	CHMat();
	CHMat(float fx00, float fx01, float fx02, float fx03, 
		  float fx10, float fx11, float fx12, float fx13, 
	      float fx20, float fx21, float fx22, float fx23, 
	      float fx30, float fx31, float fx32, float fx33);

	CHMat operator=(CHMat & hmat); // Zuweisungsoperator
	void Copy(CHMat & hmat); // Kopiert eine Matrix

	void CopyRotation(CHMat & hmat); // Kopiert den Rotationsanteil von hmat, ansonsten werden die Werte mit Einheitsmatrix-Werten aufgefüllt
	void CopyRotationX(CHMat & hmat); // Kopiert den Rotationsanteil von hmat um die X-Achse, ansonsten werden die Werte mit Einheitsmatrix-Werten aufgefüllt
	void CopyRotationY(CHMat & hmat); // Kopiert den Rotationsanteil von hmat um die Y-Achse, ansonsten werden die Werte mit Einheitsmatrix-Werten aufgefüllt
	void CopyRotationZ(CHMat & hmat); // Kopiert den Rotationsanteil von hmat um die Z-Achse, ansonsten werden die Werte mit Einheitsmatrix-Werten aufgefüllt
    void CopyRotationX(float fa);// Setzt nur den Rotationsanteil um die X-Achse
    void CopyRotationY(float fa);// Setzt nur den Rotationsanteil um die Y-Achse
    void CopyRotationZ(float fa);// Setzt nur den Rotationsanteil um die Z-Achse

    void CopyRotationXDelta(float fa);
    void CopyRotationYDelta(float fa);
    void CopyRotationZDelta(float fa);


	void CopyTranslation(CHMat & hmat); // Kopiert den translativen Anteil von hmat, ansonsten werden die Werte mit Einheitsmatrix-Werten aufgefüllt
    
    void CopyTranslation(CHVector & v); // Setzt ausschließlich den translativen Anteil
    void CopyTranslationX(float fx);
    void CopyTranslationY(float fy);
    void CopyTranslationZ(float fz);

    void CopyScale(float f); // Setzt ausschließlich die Skalierung
    void CopyScaleX(float fx);
    void CopyScaleY(float fy);
    void CopyScaleZ(float fz);
    void CopyScaleDelta(float f); // Setzt ausschließlich die Skalierung
    void CopyScaleXDelta(float fx);
    void CopyScaleYDelta(float fy);
    void CopyScaleZDelta(float fz);

	CHMat operator*(CHMat & hmat); // Matrix-Matrix-Multiplikation 
	CHVector operator*(CHVector & v); // Matrix-Vector-Multiplikation 

	void operator*=(CHMat & hmat); // Matrix-Matrix-Multiplikation - Schnelloperator 

	CHMat operator+(CHMat & hmat); // Matrix-Matrix-Addition
	CHMat operator-(CHMat & hmat); // Matrix-Matrix-Subtraktion

	void Init();				// Initialisiert Matrix als Einheitsmatrix
	void Init(float fx00, float fx01, float fx02, float fx03, 
		      float fx10, float fx11, float fx12, float fx13, 
			  float fx20, float fx21, float fx22, float fx23, 
			  float fx30, float fx31, float fx32, float fx33); // Initialisiert Matrix mit gewünschten Werten

	void Unit();				// Generiert Einheitsmatrix
	void RotateX(float fa);		// Generiert Rotationsmatrix um x-Achse mit Winkel fa
	void RotateY(float fa);		// Generiert Rotationsmatrix um y-Achse mit Winkel fa
	void RotateZ(float fa);		// Generiert Rotationsmatrix um z-Achse mit Winkel fa
	void Rotate(EAxis eAxis, float fa);		// Generiert Rotationsmatrix um kartesische Achse eAxis mit Winkel fa
	void Rotate(float fx, float fy, float fz, float fa); // Generiert beliebige Rotationsmatrix um die Drehachse fx, fy, fz mit Winkel fa
	void Rotate(CHVector & v, float fa); // Generiert beliebige Rotationsmatrix um die Drehachse v mit Winkel fa
	void Rotate(CHVector & vTo, CHVector & vFrom); // erzeugt eine Rotationsmatrix, die Richtungsvektor vFrom genau in die Richtung des Richtungsvektors vTo rotiert
	void Scale(CHVector & v);	// Generiert Skalierungsmatrix mit drei verschiedenen Skalierungswerten
	void Scale(float fx,float fy,float fz);// Generiert Skalierungsmatrix mit drei verschiedenen Skalierungswerten
	void Scale(float f);		// Generiert uniforme Skalierungsmatrix
	void ScaleX(float fx);		// Generiert uniforme Skalierungsmatrix für die X-Achse
	void ScaleY(float fy);		// Generiert uniforme Skalierungsmatrix für die Y-Achse
	void ScaleZ(float fz);		// Generiert uniforme Skalierungsmatrix für die Z-Achse
	void Translate(CHVector & v); // Generiert Verschiebungsmatrix
	void Translate(float fx, float fy, float fz); // Generiert Verschiebungsmatrix
	void TranslateX(float fx); // Generiert Verschiebungsmatrix in X-Richtung
	void TranslateY(float fy); // Generiert Verschiebungsmatrix in Y-Richtung
	void TranslateZ(float fz); // Generiert Verschiebungsmatrix in Z-Richtung
	void Translate(EAxis eAxis, float f); // Generiert Verschiebungsmatrix in Axenrichtung, die durch eAxis festgelegt ist
	void ProjectionOrtho(float fWidth, float fHeight, float fNear, float fFar); // Generiert eine orthografische Projektionsmatrix 
	void ProjectionFov(float faFovHorizontal, float fRatio, float fNear, float fFar); // Generiert eine foveale Projektionsmatrix 
	void ProjectionFovOpenGL(float faFovHorizontal, float fRatio, float fNear, float fFar); // Generiert eine foveale Projektionsmatrix wie sie in OpenGl verwendet wird
	void ProjectionFovOld(float faFovHorizontal, float fRatio, float fNear, float fFar); // Generiert eine foveale Projektionsmatrix 
	void ProjectionFovMirror(float faFovHorizontal, float fRatio, float fNear, float fFar); // Generiert eine horizontal gespiegelte foveale Projektionsmatrix 



	void RotateXDelta(float fa);	// Generiert eine neue Rotationsmatrix um die X-Achse mit dem Winkel fa und multipliziert diese mit der aktuellen Matrix  
	void RotateYDelta(float fa);	// Generiert eine neue Rotationsmatrix um die Y-Achse mit dem Winkel fa und multipliziert diese mit der aktuellen Matrix  
	void RotateZDelta(float fa);	// Generiert eine neue Rotationsmatrix um die Z-Achse mit dem Winkel fa und multipliziert diese mit der aktuellen Matrix 
	void RotateDelta(float fx, float fy, float fz, float fa); // Generiert beliebige Rotationsmatrix um die Drehachse fx, fy, fz mit Winkel fa und multipliziert diese mit der aktuellen Matrix  
	void RotateDelta(CHVector & v, float fa); // Generiert beliebige Rotationsmatrix um die Drehachse v mit Winkel fa und multipliziert diese mit der aktuellen Matrix  
	void RotateDelta(EAxis eAxis, float fa); // Generiert beliebige Rotationsmatrix um die Drehachse eAxis mit Winkel fa und multipliziert diese mit der aktuellen Matrix  
	void RotateDelta(CHVector & vTo, CHVector & vFrom); // Generiert eine Rotationsmatrix, die Richtungsvektor vFrom genau in die Richtung des Richtungsvektors vTo rotiert und multipliziert diese mit der aktuellen Matrix  
	void ScaleDelta(CHVector & v);	// Generiert Skalierungsmatrix mit drei verschiedenen Skalierungswerten und multipliziert diese mit der aktuellen Matrix 
	void ScaleDelta(float fx, float fy, float fz);// Generiert Skalierungsmatrix mit drei verschiedenen Skalierungswerten und multipliziert diese mit der aktuellen Matrix  
	void ScaleDelta(float f);		// Generiert uniforme Skalierungsmatrix und multipliziert diese mit der aktuellen Matrix  
	void ScaleXDelta(float fx);		// Generiert uniforme Skalierungsmatrix für die X-Achse und multipliziert diese mit der aktuellen Matrix
	void ScaleYDelta(float fy);		// Generiert uniforme Skalierungsmatrix für die Y-Achse und multipliziert diese mit der aktuellen Matrix
	void ScaleZDelta(float fz);		// Generiert uniforme Skalierungsmatrix für die Z-Achse und multipliziert diese mit der aktuellen Matrix
	void TranslateDelta(float fx, float fy, float fz); // Generiert Verschiebungsmatrix und multipliziert diese mit der aktuellen Matrix
	void TranslateDelta(CHVector & v); // Generiert Verschiebungsmatrix und multipliziert diese mit der aktuellen Matrix 
	void TranslateXDelta(float fx); // Generiert Verschiebungsmatrix in X-Richtung und multipliziert diese mit der aktuellen Matrix 
	void TranslateYDelta(float fy); // Generiert Verschiebungsmatrix in Y-Richtung und multipliziert diese mit der aktuellen Matrix 
	void TranslateZDelta(float fz); // Generiert Verschiebungsmatrix in Z-Richtung und multipliziert diese mit der aktuellen Matrix 
	void TranslateDelta(EAxis eAxis, float f); // Generiert Verschiebungsmatrix in Axenrichtung, die durch eAxis festgelegt ist, und multipliziert diese mit der aktuellen Matrix 


	float Det();				// Berechnet Determinante der Matrix
	void Transpose();			// Transponiert Matrix 
	void Inverse();				// Invertiert Matrix 
	void Transpose(CHMat & m);	// Setzt aktuelle Matrix auf die Transponierte der Matrix m
	void Inverse(CHMat & m);	// Setzt aktuelle Matrix auf die Inverse der Matrix m
	void NormOne();				// Normiert die Matrix dahingehend, dass das letzte Element [3,3] gleich 1.0 ist

	CHVector GetTranslation();  // Spuckt die Translation als homogenen Vektor aus.	
    void GetRotation(float &fYaw, float &fPitch, float &fRoll); // Spuckt die Rotation als Yaw-, Pitch- und Roll-Winkel aus.
    CHVector GetScaleFactor(void); // Spuckt den Skalierungsfaktor für x, y und z als homogenen Vektor aus.
	CHVector GetPos();  // Spuckt die Position als homogenen Vektor der homogenenen Matrix aus (Matrix * Ursspung)	



	bool IsScaledToNull(); // gibt bei Nullskalierung true aus 

	float m_fx00;
	float m_fx01;
	float m_fx02;
	float m_fx03;
	float m_fx10;
	float m_fx11;
	float m_fx12;
	float m_fx13;
	float m_fx20;
	float m_fx21;
	float m_fx22;
	float m_fx23;
	float m_fx30;
	float m_fx31;
	float m_fx32;
	float m_fx33;
};

}