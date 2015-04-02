#include "Game.h"
#include "StdAfx.h"
#include <boost\lexical_cast.hpp>

CGame::CGame(void) {
	// Hier eventuelle Vorinitialisierungen Deiner Vektoria-Objekte einfügen:
}

CGame::~CGame(void) {
	delete m_pClient;
	delete m_pIOService;
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
	m_pIOService = new io_service;

	ip::tcp::resolver resolver(*m_pIOService);
	ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve({ "localhost", "1234" });

	m_pClient = new CClient(*m_pIOService);
	m_pClient->do_connect(endpoint_iterator);

	m_threadClient = boost::thread([this]() {
		m_pIOService->run();
	});

	m_fTimeSinceLastSend = 0;
}

void CGame::Tick(float fTime, float fTimeDelta) {
	m_zpCube.TranslateZ(-10.0f + 2.0f * sin(fTime));

	m_zdKeyboard.PlaceWASD(m_zpCamera, fTimeDelta, true);

	if (m_fTimeSinceLastSend > 1) {
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

		m_pClient->write(CMessage(text.data()));
		m_fTimeSinceLastSend = 0;
	} else {
		m_fTimeSinceLastSend += fTimeDelta;
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
