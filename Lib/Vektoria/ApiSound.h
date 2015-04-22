#pragma once
#include <Windows.h>
#include "../VektoriaMath/HMat.h"

//---------------------------------------------------
// CApiSound
//
// Autoren: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2015-01-28
//---------------------------------------------------




namespace Vektoria
{

	// Sound-API - Möglichkeiten:
	enum EApiSound
	{
		eApiSound_Null,
		eApiSound_DirectSound,
		eApiSound_DirectAudio,
		eApiSound_OpenAL
	};

class CApiSound
{
public:
	// Konstruktor und Destruktor:
	CApiSound(void);
	~CApiSound(void);

	// Geburt, Leben und Sterben:
	virtual bool Init(HWND & hwnd) = 0;  // Initialisiert die Sound-Api
	virtual void Fini() = 0;

	// Wird jedes Frame Aufgerufen (Äquivalent zu Draw-Aufrufen beim Renderer):
	virtual void PosSound(CHMat & mAudio, float & fTimeDelta, bool & bTick, int & idSound) = 0; //Updated einen Klang mit 3D-Audio, muss bei jeden Frame aufgerufen werden, mAudio ist die globale Matrix der Klangquelle, fTimeDelta ist die verstrichene Zeit seit dem letzten Tick 
	virtual void Listen(CHMat & mListener, int & iAudio, int & idSound) = 0; // Positioniert den Zuhörer beim 3D-Audio mittels der globalen Matrix mListener

	virtual int AddSound(char *stringWavFile) = 0;  // Initialisiert einen Klang ohne 3D-Audio, dieser kann nicht in den Szenengraf eingebaut werden, die Funktion gibt die ID aus, falls die Initailisierung erfolgreich war, ansonsten -1 
	virtual int AddSound3D(char *stringWavFile, float & fRadius) = 0; // Initialisiert einen Klang mit 3D-Audio, die Funktion gibt die ID aus, falls die Initailisierung erfolgreich war, ansonsten -1



	// Schaltfunktionen:
	virtual void Start(int & idSound) = 0;	// Startet einen Klang, spielt ihn einmal ab
	virtual void Loop(int & idSound) = 0;	// Startet einen Klang, spielt ihn immer wieder ab
	virtual void Pause(int & idSound) = 0;	// Pausiert einen gestarteten Klang
	virtual void Stop(int & idSound) = 0;	// Beendet einen gestarten Klang 

	// Parametrisierungsfunktionen:
	virtual void SetVolume(float & frVolume, int & idSound) = 0; // Modifiziert die Lautstärke (0.0F=aus 1.0F= volles Rohr) 
	virtual void SetRadius(float & fRadius, int & idSound) = 0; // Modifiziert den Wirkradius in Units eines 3D-Klanges 
	virtual void SetDoppler(float & fFactor, int & idSound) = 0; // fFactor=1.0: physikalisch richtiger Doppler-Effekt, fFactor=0.0: kein Doppler-Effekt; Default = 1.0F
	virtual void SetFrequency(float & fFrequency, int & idSound) = 0;  // Setzt die Frequenz in Hertz
	virtual void SetPan(float & fPan, int & idSound) = 0; // Stereoballanceeinstellungen zwischen links und rechts (-1 = links, 0= Mitte, 1 = rechts) 
	virtual void ResetFrequency(int & idSound) = 0;  // Setzt die Frequenz zurück auf die originale Einstellung des Soundfiles

	// Sound-LoD-Funktionen:
	virtual void PauseCauseLoD(int & iAudio, int & idSound) = 0; // Pausiert den Zuhörer beim 3D-Audio wegen LoD 
	virtual void ContinueCauseLoD(int & iAudio, int & idSound) = 0;  // Setzt den Zuhörer beim 3D-Audio nach LoD-Eintritt wieder fort 

};

}