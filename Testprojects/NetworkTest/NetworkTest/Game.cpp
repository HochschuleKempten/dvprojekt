#include "Game.h"
#include "StdAfx.h"
#include <boost\lexical_cast.hpp>

CGame::CGame(void) {
	// Hier eventuelle Vorinitialisierungen Deiner Vektoria-Objekte einfügen:
}

CGame::~CGame(void) {
	delete m_pComputer;
}

void CGame::Init(HWND hwnd, CSplash * psplash) {
	// init
	m_zr.Init(psplash);
	m_zf.Init(hwnd);
	m_zc.Init();
	m_zv.InitFull(&m_zc);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));
	m_zgCube.Init(CHVector(1.0f, 1.0f, 1.0f), &m_zmLogo);

	// material
	m_zmLogo.MakeTextureDiffuse("textures\\VektoriaLogo_400x400.bmp");
	m_zmBlackMaterial.MakeTextureDiffuse("textures\\black_image.jpg");
	m_zmWhiteMaterial.MakeTextureSprite("textures\\white_image.jpg");

	// font
	m_wfDefaultFont.Init("fonts\\default.jpeg", false);
	m_wfDefaultFont.SetTableSize(16, 6);
	m_wfDefaultFont.SetTableStartASCII(0);

	// writing
	m_zwLog.Init(CFloatRect(0, 0, 0.5f, 0.02f), 100, &m_wfDefaultFont);
	m_zv.AddWriting(&m_zwLog);

	// background
	m_zBackground.InitFull(&m_zmWhiteMaterial);
	m_zv.AddBackground(&m_zBackground);

	// placements
	m_zpCube.AddGeo(&m_zgCube);
	m_zpCube.Translate(CHVector(0, 0, -10));

	m_zpCamera.AddCamera(&m_zc);

	// fill scene
	m_zs.AddPlacement(&m_zpCube);
	m_zs.AddPlacement(&m_zpCamera);
	m_zs.AddParallelLight(&m_zl);

	// devices
	m_zf.AddDeviceKeyboard(&m_zdKeyboard);
	m_zf.AddDeviceMouse(&m_zdMouse);

	m_zdKeyboard.SetWASDTranslationSensitivity(2.0f);
	m_zdKeyboard.SetWASDRotationSensitivity(1.5f);

	m_zdMouse.SetSensitivity(0.001f);

	// add to root
	m_zf.AddViewport(&m_zv);
	m_zr.AddFrameHere(&m_zf);
	m_zr.AddScene(&m_zs);

	// init network
	m_fLastSendTime = 0;

	// change cout dest
	outFile = std::ofstream("cout.txt");
	std::cout.rdbuf(outFile.rdbuf());
}

void CGame::Tick(float fTime, float fTimeDelta) {
	m_zpCube.TranslateZ(-10.0f + 2.0f * sin(fTime));

	m_zdKeyboard.PlaceWASD(m_zpCamera, fTimeDelta, true);

	//m_zwLog.PrintF("abc123ABC");

	if (m_pComputer != 0) {
		if (m_pComputer->isConnected() && fTime - m_fLastSendTime > 1) {
			std::string text = "XY";
			text += boost::lexical_cast<std::string>(m_zpCube.GetTranslation().AngleXY());
			text += "XZ";
			text += boost::lexical_cast<std::string>(m_zpCube.GetTranslation().AngleXZ());
			text += "YX";
			text += boost::lexical_cast<std::string>(m_zpCube.GetTranslation().AngleYX());
			text += "YZ";
			text += boost::lexical_cast<std::string>(m_zpCube.GetTranslation().AngleYZ());
			text += "ZX";
			text += boost::lexical_cast<std::string>(m_zpCube.GetTranslation().AngleZX());
			text += "ZY";
			text += boost::lexical_cast<std::string>(m_zpCube.GetTranslation().AngleZY());

			m_pComputer->write(CMessage(text.data()));
			m_fLastSendTime = fTime;
		}
	} else {
		if (m_zdKeyboard.GetKey() == 0x1F) { // "S"
			m_pComputer = new CServer(1234);
			m_pComputer->start();
			//m_pComputer->setConsole(&m_zwLog);
		} else if (m_zdKeyboard.GetKey() == 0x2E) { // "C"
			m_pComputer = new CClient("localhost", "1234");
			m_pComputer->start();
			//m_pComputer->setConsole(&m_zwLog);
		}
	}
	
	m_zr.Tick(fTimeDelta);
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:

}
