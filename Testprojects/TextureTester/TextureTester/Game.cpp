#include "StdAfx.h"
#include "Game.h"



CGame::CGame(void)
{
	// Hier eventuelle Vorinitialisierungen Deiner Vektoria-Objekte einfügen:
}

CGame::~CGame(void)
{
	// Hier eventuelle Nachinitialisierungen Deiner Vektoria-Objekte einfügen:
}

void CGame::Init(HWND hwnd, CSplash * psplash)
{
	// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
	// Root initialisieren
	m_root.Init(psplash);
	// Frame initialisieren
	m_frame.Init(hwnd, eApiRender_DirectX11_Shadermodel50);
	// Kamera initialisieren
	m_camera.Init();
	// Viewport initialisieren
	m_viewport.InitFull(&m_camera);
	// Beleuchtung initialisieren
	m_light.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));

	// Material einrichten
	m_quadMaterial.MakeTextureDiffuse("textures/diffuse.png");				//Diffuse
	m_quadMaterial.MakeTextureBump("textures/normal.png");					//Bump Map / Normal Map
	m_quadMaterial.MakeTextureGlow("textures/emissive.png");				//Emissive
	m_quadMaterial.MakeTextureSpecular("textures/specular.png");			//Specular Map
	//m_quadMaterial.MakeTextureHeight("textures/height.png");				//Height Map

	// Frame an Root anhängen
	m_root.AddFrameHere(&m_frame);
	// Viewport an den Frame anhängen
	m_frame.AddViewport(&m_viewport);
	// Szene an Root anhängen
	m_root.AddScene(&m_scene);

	// Placements und Beleuchtung zur Szene hinzufügen
	m_scene.AddPlacement(&m_placeQuad0);
	m_scene.AddPlacement(&m_placeQuad1);
	m_scene.AddPlacement(&m_placeQuad2);
	m_scene.AddPlacement(&m_placeQuad3);
	m_scene.AddPlacement(&m_placeQuad4);
	m_scene.AddPlacement(&m_placeQuad5);
	m_scene.AddPlacement(&m_placeQuad6);
	m_scene.AddPlacement(&m_placeQuad7);
	m_scene.AddPlacement(&m_placeQuad8);
	m_scene.AddPlacement(&m_placeCamera);
	m_scene.AddParallelLight(&m_light);

	// Kamera dem Placement hinzufügen
	m_placeCamera.AddCamera(&m_camera);

	// Quad einrichten und Material zuweisen
	m_quad.Init(1.0f, 1.0f, &m_quadMaterial);
	//m_sphere.Init(1.0f, &m_quadMaterial, 64, 64);

	// Quad-Placcement positionieren
	m_placeCamera.Translate(CHVector(0, 0, 3));

	// Quad dem Placement zuweisen
	m_placeQuad0.AddGeo(&m_quad);
	m_placeQuad1.AddGeo(&m_quad);
	m_placeQuad1.TranslateX(2.0F);
	m_placeQuad2.AddGeo(&m_quad);
	m_placeQuad2.TranslateX(-2.0F);
	m_placeQuad3.AddGeo(&m_quad);
	m_placeQuad3.TranslateY(2.0F);
	m_placeQuad4.AddGeo(&m_quad);
	m_placeQuad4.TranslateY(-2.0F);
	m_placeQuad5.AddGeo(&m_quad);
	m_placeQuad5.Translate(2.0F, 2.0F, 0);
	m_placeQuad6.AddGeo(&m_quad);
	m_placeQuad6.Translate(-2.0F, 2.0F, 0);
	m_placeQuad7.AddGeo(&m_quad);
	m_placeQuad7.Translate(2.0F, -2.0F, 0);
	m_placeQuad8.AddGeo(&m_quad);
	m_placeQuad8.Translate(-2.0F, -2.0F, 0);
	//m_placeQuad.AddGeo(&m_sphere);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Hier die Echtzeit-Veränderungen einfügen:
	// Psycho-Fade
	//m_camera.SetFov(1.221F + 0.872F*sin(fTime));
	//m_camera.SetFov(1.5F + 0.25F*sin(4*fTime));

	// Rotation des Quads
	//m_placeQuad.RotateX(sin(fTime));

	//Animate light source
	//m_light.m_vDirection.SetX(0.5F + 0.5F*sin(fTime));
	//m_light.m_vDirection.SetZ(0.5F + 0.5F*cos(fTime));

	// Tick im Root aufrufen
	m_root.Tick(fTimeDelta);
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	//m_frame.ReSize(iNewWidth, iNewHeight);
}

