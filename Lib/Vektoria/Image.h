#pragma once

//---------------------------------------------------
// CImage: Klasse für Pixel-Images
//
// Autoren: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2011-08-07
//---------------------------------------------------

namespace Vektoria
{

class CImage
{
	friend class CImages;
private:
	void Tick(float & fTimeDelta);

public:
	CImage();
	~CImage();
	CImage operator=(CImage image);
	void Copy(CImage image);

	void Init(char * acPath);
	void Fini();



	char m_acPath[256];


};

}