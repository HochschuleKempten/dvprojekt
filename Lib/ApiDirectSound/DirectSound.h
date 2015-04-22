#pragma once

//------------------------------------------------------------------
// DirectSound: Klasse zur DirectX-Anbindung
//
// Autor: Prof. Dr. Tobias Breiner 
// Letzte Änderung: 2012-06-05
//-------------------------------------------------------------------

#include "../Vektoria/ApiSound.h"

#include "windows.h" 
#include <mmsystem.h>
#include "dsound.h"
#include <stdio.h>


#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#ifdef WIN64
#define ASTRINGCAST (LPTSTR)
#else
#define ASTRINGCAST (PWSTR)
#endif

#define HAVETOSLACK 0
#define HAVETOLOOP 1 
#define HAVETOSTART 2 
#define HAVETOSTOP 3
#define ISLOOPING 4 
#define HASSTARTED 5


namespace Vektoria
{

	class CSingleSound
	{
	public:
		CSingleSound();

		void Init(IDirectSound8* m_lpDS);
		void Init3D(float & fRadius, IDirectSound8* m_lpDS);
		void Tick(CHMat & mAudio, float & fTimeDelta, bool & bTick);
		void Fini();

		void Start();	// Startet einen Klang, spielt ihn einmal ab
		void Loop();	// Startet einen Klang, spielt ihn immer wieder ab
		void Pause();	// Pausiert einen gestarteten Klang
		void Stop();	// Beendet einen gestarten Klang 

		void SetVolume(float & frVolume); // Modifiziert die Lautstärke (0.0F=aus 1.0F= volles Rohr) 
		void SetRadius(float & fRadius); // Modifiziert den Wirkradius in Units eines 3D-Klanges 
		void SetDoppler(float & fFactor); // fFactor=1.0: physikalisch richtiger Doppler-Effekt, fFactor=0.0: kein Doppler-Effekt; Default = 1.0F
		void SetFrequency(float & fFrequency); // Setzt die Frequenz in Hertz
		void SetPan(float & ftPan); // Stereoeinstellungen zwischen links und rechts (-1 = links, 0= Mitte, 1 = rechts) 
		void ResetFrequency(); // Setzt die Frequenz auf die originale Frequenz 

		void PauseCauseLoD(int & iAudio); // Pausiert den Zuhörer beim 3D-Audio wegen LoD 
		void ContinueCauseLoD(int & iAudio);  // Setzt den Zuhörer beim 3D-Audio nach LoD-Eintritt wieder fort 

		void Listen(CHMat & mListener, int & iAudio);





		IDirectSoundBuffer8** m_alpDSBSecondary;
		IDirectSound8* m_lpDS;

		IDirectSound3DBuffer8** m_alpDS3DBSecondary;
		int m_iSecondary3DBufferAllocs;
		int m_iSecondary3DBufferInits;

		int m_iMatGlobals;

		bool m_bDoppler; // true, wenn Doppler-Effekt berechnet werden soll
		float m_fRadius;  // Eingestellter Wirkradius in Units eines 3D-Klanges, Default = 1.0F 
		float m_frVolume; // eingestellte Lautstärke (0.0F=aus 1.0F= volles Rohr), Default = 1.0F 
		bool m_bHaveToLoop;
		bool m_bHaveToStart;
		bool m_bHaveToStop;

		bool m_bHaveToSetVolume;
		bool m_bHaveToSetFrequency;
		bool m_bHaveToSetPan;

		int * m_aeStatus; // 0 = not initialized, 1 = gestartet, 2 = looping, 3 = stopped, 4 = paused while started, 5 = paused  while looping

		IDirectSoundBuffer* m_lpDSB;
		long m_lVolume;
		long m_lFrequency;
		long m_lPan;

		bool CreateSecondaryBuffer(int iAudio);
		int  m_iAllocStep;
		// Neu für 3D audio: 
		bool m_b3D;
		IDirectSound3DListener8* m_lpListener;


	
		CHVector m_vListenerOld;
		CHVector m_vAudioOld;


		struct WaveHeaderType
		{
			char chunkId[4];
			unsigned long chunkSize;
			char format[4];
			char subChunkId[4];
			unsigned long subChunkSize;
			unsigned short audioFormat;
			unsigned short numChannels;
			unsigned long sampleRate;
			unsigned long bytesPerSecond;
			unsigned short blockAlign;
			unsigned short bitsPerSample;
			char dataChunkId[4];
			unsigned long dataSize;
		};

		bool LoadWave(char *stringWavFile);
		bool LoadWave3D(char *stringWavFile);
		float m_fTimeDelta;

		FILE * m_file;
		WaveHeaderType m_waveFileHeader;
		DSBUFFERDESC m_bufferdescPrimary;
		WAVEFORMATEX m_waveformatPrimary;
		DSBUFFERDESC m_bufferdescSecondary;
		WAVEFORMATEX m_waveformatSecondary;
		int m_iSampleRate;
		int m_iBitsPerSample;
		bool m_bTick;
		bool m_bInitialized;


	};

class CDirectSound : public CApiSound
{
public:
	CDirectSound(void);
	~CDirectSound(void);

	// Geburt, Leben und Sterben:
	bool Init(HWND & hwnd); // Initialisiert die Sound-Api
	void Fini(); // Finalisiert einen Klang, egal ob mit oder ohne 3D-Audio

	int AddSound(char *stringWavFile);  // Initialisiert einen Klang ohne 3D-Audio, dieser kann nicht in den Szenengraf eingebaut werden, die Funktion gibt true aus, falls die Initailisierung erfolgreich war, ansonsten false 
	int AddSound3D(char *stringWavFile, float & fRadius); // Initialisiert einen Klang mit 3D-Audio, die Funktion gibt true aus, falls die Initailisierung erfolgreich war, ansonsten false
	void PosSound(CHMat & mAudio, float & fTimeDelta, bool & bTick, int & idSound); //Updated einen Klang mit 3D-Audio, muss bei jeden Frame aufgerufen werden, mAudio ist die globale Matrix der Klangquelle, fTimeDelta ist die verstrichene Zeit seit dem letzten Tick 

	void Listen(CHMat & mListener, int & iAudio, int & idSound); // Positioniert den Zuhörer beim 3D-Audio mittels der globalen Matrix mListener


	void Start(int & idSound);	// Startet einen Klang, spielt ihn einmal ab
	void Loop(int & idSound);	// Startet einen Klang, spielt ihn immer wieder ab
	void Pause(int & idSound);	// Pausiert einen gestarteten Klang
	void Stop(int & idSound);	// Beendet einen gestarten Klang 

	void SetVolume(float & frVolume, int & idSound); // Modifiziert die Lautstärke (0.0F=aus 1.0F= volles Rohr) 
	void SetRadius(float & fRadius, int & idSound); // Modifiziert den Wirkradius in Units eines 3D-Klanges 
	void SetDoppler(float & fFactor, int & idSound); // fFactor=1.0: physikalisch richtiger Doppler-Effekt, fFactor=0.0: kein Doppler-Effekt; Default = 1.0F
	void SetFrequency(float & fFrequency, int & idSound); // Setzt die Frequenz in Herz
	void ResetFrequency(int & idSound); // Setzt die Frequenz auf die originale Frequenz 
	void SetPan(float & ftPan, int & idSound); // Setzt den Pan 

	void PauseCauseLoD(int & iAudio, int & idSound); // Pausiert den Zuhörer beim 3D-Audio wegen LoD 
	void ContinueCauseLoD(int & iAudio, int & idSound);  // Setzt den Zuhörer beim 3D-Audio nach LoD-Eintritt wieder fort 

	bool m_bFirstCommit;
	IDirectSound8* m_lpDS;

	int m_iSounds;
	int m_iSoundsAllocated;
	int m_iAllocStep;
	CSingleSound * m_asinglesound;

	bool m_bInitialized;
	HWND m_hwnd;


};

}