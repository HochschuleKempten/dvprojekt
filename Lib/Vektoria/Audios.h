#pragma once
#include "Audio.h"

//--------------------------------------------------------------------------------------------
//  CAudios:  Klasse für Soundlisten
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2011-08-07
//--------------------------------------------------------------------------------------------

namespace Vektoria
{

class CAudios
{
public:
	CAudios(void);
	~CAudios(void);

	CAudios operator=(CAudios & audios);

	void Init();
	bool Init(char *stringWavFile, int iAudios);
	void Tick(CHMat & m, float & fTimeDelta,bool & bTick);
	void Fini();
	
	void Start();
	void Loop();
	void Stop();

	void SetVolume(float frVolume);

	void Add(CAudio * paudio);
	bool Sub(CAudio * paudio);

	CAudio * Make(char *stringWavFile);
	bool Kill(CAudio * paudio);

	void PauseCauseLoD(int iAudio);
	void ContinueCauseLoD(int iAudio);

	void Listen(CHMat & mListener, int iAudio); // Positioniert den Zuhörer beim 3D-Audio mittels der globalen Matrix mListener

	CAudio ** m_apaudio;
	int m_iAudioAllocs;
	int m_iAllocBlock;
	int m_iAudios;
	int m_iAudio; // Akuelles Audio

//	void SetRoot(CRoot * proot);
//	CRoot * m_proot;

};

}