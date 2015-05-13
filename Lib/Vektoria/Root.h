#pragma once
#include "Scenes.h"
#include "Hardwares.h"
#include "Geo.h"
#include "GeoQuad.h"
#include "GeoCube.h"
#include "GeoSkybox.h"
#include "GeoTube.h"
#include "GeoFrustum.h"
#include "GeoCone.h"
#include "GeoSweep.h"
#include "GeoSlice.h"
#include "GeoCylinder.h"
#include "GeoArrow.h"
#include "GeoInfoVertex.h"
#include "GeoInfoGeo.h"
#include "GeoTetraeder.h"
#include "GeoEllipsoid.h"
#include "GeoIkosaeder.h"
#include "GeoWall.h"
#include "GeoWindow.h"
#include "GeoWing.h"
#include "GeoSphere.h"
#include "GeoDome.h"
#include "ApiRender.h"
#include "Materials.h"
#include "Device.h"
#include "FileX3D.h"
#include "File3DS.h" // TODO funktioniert nicht => Matthias fragen
#include "FileBlender.h"
#include "FileWavefront.h"
#include "../VektoriaMath/Quaternion.h"
#include "Images.h"
#include "Wribel.h"
#include "Splash.h"
#include "GeoEllipsoidTiled.h"
#include "GeoSphereTiled.h"
#include "GeoDomeTiled.h"
#include "GeoTriangle.h"
#include "Physical.h"
#include "Placements.h"

#include "DistributedGlobal.h"
#include "ApiSound.h"
#include "UtilLogFile.h"

//---------------------------------------------------
// CRoot: Klasse für die Wurzel des Szenegrafen-Baumes
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2011-08-07
//---------------------------------------------------

namespace Vektoria
{

	class CApiRender;

	class CRoot : public CNode
	{
	private:
		// singleton: (geht nicht wegen Disfactory und DisfacRoot)
		// 	static CRoot* m_pRootInstance;
		// 	CRoot();
		// 	CRoot operator=(CRoot root);
		// 	void Copy(CRoot root);
#ifdef NETWORKMASTER
		unsigned int m_idId;
		int m_icId;
#endif
	public:
#ifdef NETWORKMASTER
		unsigned int GetidId();
#endif

		CRoot();
		~CRoot();
		CRoot operator=(CRoot root);
		void Copy(CRoot root);

		void Init(CSplash * psplash); // Initialisiert die Wurzel, muss Splashscreen übergeben bekommen, welches schon aufgerufen werden
		//		void Init(); // Initialisiert die Wurzel
		bool Tick(float & fTimeDelta); // Diese Methode muss jedes Frame aufgerufen werden
		void Fini(); // Finalisiert die Wurzel

		void AddScene(CScene * pscene);	// Hängt eine Szene an die Wurzel an
		bool SubScene(CScene * pscene);	// Hängt eine Szene von der Wurzel ab, gibt false aus, wenn die angegebene Szene nicht ein Kind der Wurzel ist oder überhaupt nicht existiert, bei Erfolg wird true ausgegeben 

		void AddFrameHere(CFrame * pframe);  // Hängt dem aktuellen Computer an die Wurzel an, und an diesen wiederum den angegebenen Frame

		void AddMaterial(CMaterial * pmaterial); //Fügt ein weiteres Material in die Materialliste der Wurzel hinzu
		bool SubMaterial(CMaterial * pmaterial); //Löscht ein Material aus der Materialliste der Wurzel, gibt true aus, wenn es funktioniert hat 
		bool SubAllMaterials();	// Löscht alle Materialien  aus der Materialliste der Wurzel (außer dem Defaultmaterial), bei Erfolg wird true ausgegeben. Diese Methode ist sinnvoll vor dem Laden eines neuen Levels mit komplett neuen Texturen 

		void ShowBar(float frProgress);
		void HideBar();

		void OpenSesamy(char * ac);
		int m_iArchitecture;
		float m_fTime;

		CMaterials m_materials;
		CScenes m_scenes;
		CHardwares m_hardwares;		// fremde Computer im LAN
		CHardware m_hardwareHere;	// dieser Computer

		CHMat m_m;
		CMaterial m_zmDefault; // Defaultmaterial "Weiß"
		bool m_bFirstTick; // true, wenn erster Tick, ansonsten false
		bool m_bTick;
		CApiSound * m_papisoundActual; // Wechselt, falls mehr als ein Frame vorhanden. Dies ist der dazugehörige Pointer
	private:
		CSplash * m_psplash;
		bool m_bSesamy;
	};


}