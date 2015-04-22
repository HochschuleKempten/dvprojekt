#pragma once

#include "Node3D.h"
#include "windows.h" 
#include <stdio.h>
#include "ApiSound.h"

//---------------------------------------------------
// CAudio: Klasse für 3D-Raumklang
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2011-08-07
//---------------------------------------------------


#define HAVETOSLACK 0
#define HAVETOLOOP 1 
#define HAVETOSTART 2 
#define HAVETOSTOP 3
#define ISLOOPING 4 
#define HASSTARTED 5

namespace Vektoria
{

class CAudio: public CNode3D
{
	friend class CAudios;
protected: 
	void Tick(CHMat & mAudio, float & fTimeDelta, bool & bTick); //Updated einen Klang mit 3D-Audio, muss bei jeden Frame aufgerufen werden, mAudio ist die globale Matrix der Klangquelle, fTimeDelta ist die verstrichene Zeit seit dem letzten Tick 
public:
	CAudio(void);
	~CAudio(void);

	void Init(char *stringWavFile);  // Initialisiert einen Klang ohne 3D-Audio, dieser kann nicht in den Szenengraf eingebaut werden, die Funktion gibt true aus, falls die Initailisierung erfolgreich war, ansonsten false 
	void Init3D(char *stringWavFile, float fRadius); // Initialisiert einen Klang mit 3D-Audio, die Funktion gibt true aus, falls die Initailisierung erfolgreich war, ansonsten false
	void Fini(); // Finalisiert einen Klang, egal ob mit oder ohne 3D-Audio


	virtual void UpdateAABB();

	void Listen(CHMat & mListener, int iAudio); // Positioniert den Zuhörer beim 3D-Audio mittels der globalen Matrix mListener


	void Start();	// Startet einen Klang, spielt ihn einmal ab
	void Loop();	// Startet einen Klang, spielt ihn immer wieder ab
	void Pause();	// Pausiert einen gestarteten Klang
	void Stop();	// Beendet einen gestarten Klang 

	void SetVolume(float frVolume); // Modifiziert die Lautstärke (0.0F=aus 1.0F= volles Rohr) 
	void SetRadius(float fRadius); // Modifiziert den Wirkradius in Units eines 3D-Klanges 
	void SetDoppler(float fFactor); // fFactor=1.0: physikalisch richtiger Doppler-Effekt, fFactor=0.0: kein Doppler-Effekt; Default = 1.0F
	void SetFrequency(float fFrequency); // Setzt die Frequenz in Hertz, wenn nicht aufgerufen wird die originale Frequenz des Samples genommen
	void SetPan(float ftPan); // Stereoeinstellungen zwischen links und rechts (-1 = links, 0= Mitte, 1 = rechts) 
	void ResetFrequency(); // Setzt die Frequenz wieder auf die originale Frequenz des Samples

	bool Is3D(); // Gibt true aus, wenn 3D-Audio, ansonsten false 

	bool m_bDoppler; // true, wenn Doppler-Effekt berechnet werden soll
	float m_fRadius;  // Eingestellter Wirkradius in Units eines 3D-Klanges, Default = 1.0F 
	float m_frVolume; // eingestellte Lautstärke (0.0F=aus 1.0F= volles Rohr), Default = 1.0F 
	float m_fFrequency; // Frequenz in Herz, wenn nicht aufgerufen wird die originale Frequenz des Samples genommen
	float m_ftPan;	// eingestellte Stereoballance (-1.0F=links, 0.0= normal bzw. Mitte, 1.0F= rechts), Default = 1.0F 
	float m_fDopplerFactor;

	bool m_bHaveToLoop;
	bool m_bHaveToStart;
	bool m_bHaveToStop;
	bool m_bHaveToPause;
	bool m_bHaveToSetDoppler;
	bool m_bHaveToSetRadius;
	bool m_bHaveToSetVolume;
	bool m_bHaveToSetPan;
	bool m_bHaveToSetFrequency;
	void PauseCauseLoD(int iAudio); // Pausiert den Zuhörer beim 3D-Audio wegen LoD 
	void ContinueCauseLoD(int iAudio);  // Setzt den Zuhörer beim 3D-Audio nach LoD-Eintritt wieder fort 


	CHVector m_vListenerOld;
	CHVector m_vAudioOld;
	bool m_b3D;
	bool m_bInitialized;
	bool m_bFirstCommit;
	bool m_bFirstTick;

	int m_idSound;

	char m_acWavFile[MAX_PATH];
protected:
// 	CApiSound * m_papisound;
//	void SetRoot(CRoot * proot);
//	CRoot * m_proot;
};

}