#pragma once
#include "Placement.h"

namespace Vektoria
{


	class CPhysical :
		public CPlacement
	{
	public:
		CPhysical();
		~CPhysical();

		void Init(float fMass, float fCW, bool bSolid);
		void Tick(CHMat & m, float & fTimeDelta, bool & bTick);

		void ApplyTorque(CHVector vDistToCenter, CHVector vForce); // Appliziert einen Drehmoment auf den Partikel, kann mehrfach angewendet werden
		void ApplyForce(CHVector v); // Appliziert eine Kraft auf den Partikel, kann mehrfach angewendet werden
		void ApplyGravity(); // Applziert die normale Gravitationskraft auf das Partikel

		void SetTimeToCome(float fTimeToCome);
		void SetTimeToStay(float fTimeToStay);
		void SetTimeToFade(float fTimeToFade);
		void CalcTimeOfLife();

		float GetVelocity();

		float m_fCW;    // CW-Wert (Luftwiderstandwert)
		float m_fMass;	// Masse des Partikels
		bool m_bSolid;  // Ist er fest (true) oder gasförmig/flüssig (false)

		CHVector m_vForceTotal;	  // Gesamtkraft, die auf das Teilchen einwirkt 
		CHVector m_vVelocity;     // Geschwindigkeit
		CHVector m_vAcceleration; // Beschleunigung

		CQuaternion m_qTorqueTotal;  // Gesamtdrehmoment, das auf das Teilchen einwirkt 
		CQuaternion m_qTorqueVelocity;  // Gesamtdrehgeschwindigkeit 
		CQuaternion m_qTorqueAcceleration;  // Gesamtdrehgeschwindigkeit 

		bool m_bMortal;      // Ist der Partikel sterblich? Falls ja, werden die nachfolgenden Parameter gebraucht:  
		float m_fTime;		 // Zeitspanne, die das Partikel schon lebt
		float m_fTimeToCome; // Zeitspanne, die Partikel braucht, um heranzuwachsen
		float m_fTimeToStay; // Zeitspanne, die Partikel in voller Pracht lebt
		float m_fTimeToFade; // Zeitspanne zum Krepieren des Partikels
		float m_fTimeOfLife; // Zeitspanne, die das Partikel imsgeamt lebt
		float m_frLifeEnergy; 
		bool m_bCommitSuicide; // True, wenn Partikel keine Lebenslust mehr hat
		
	};

}
