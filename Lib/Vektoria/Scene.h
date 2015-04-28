#pragma once
// #include "Placements.h"
#include "ApiRender.h"
#include "ParallelLights.h"
#include "Cameras.h"
#include "Node3D.h"
#include "Audios.h"

#include "DistributedGlobal.h"


//---------------------------------------------------
// CScene: Klasse für ein Szenenobjekt 
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2011-08-07
//---------------------------------------------------

namespace Vektoria
{

	class CPlacements; 

	class CScene : public CNode3D
	{
		friend class CScenes;
	private:
		void Tick(float & fTimeDelta, bool & bTick); // wird automatisch jedes Frame von Root aus aufgerufen

	public:
		CScene();
		~CScene();
		CScene operator=(CScene & scene);
		void Copy(CScene & scene);

		void Init(); // Initialisiert ein Szenenobjekt (Aufruf nicht unbedingt notwendig, da schon im Konstruktor aufgerufen)
		void Fini();  // Finaliisiert ein Szenenobjekt

		void AddPlacement(CPlacement * pplacement); // Hängt ein Placement an eine Szene an.
		void AddParallelLight(CParallelLight * pparallelLight);	// Hängt ein direktionales Licht an die Szene an.
		void AddAudio(CAudio * paudio); // Hängt ein Audio an eine Szene an.

		bool SubPlacement(CPlacement * pplacement); // Hängt ein Placement von einer Szene ab, gibt true aus, wenn es geklappt hat.
		bool SubParallelLight(CParallelLight * pparallelLight);	// Hängt ein direktionales Licht von der Szene ab, gibt true aus, wenn es geklappt hat.
		bool SubAudio(CAudio * paudio); // Hängt ein Audio von der Szene ab, gibt true aus, wenn es geklappt hat. Der Sound ist global hörbar.

		CHMat m_mGlobal;

		void SearchForCameras();
		bool HasCamera(CCamera * pcamera);
		void Draw(CCamera * pcamera, bool & bTickDraw);

		bool m_bFrustumCulling;
		void SetFrustumCullingOn();
		void SetFrustumCullingOff();

		bool m_bBVHExactCalculation;
		void SetBVHExactCalculationOn();
		void SetBVHExactCalculationOff();




		CPlacement * PickPlacement(CRay & r);
		void PickPlacements(CRay & r, CPlacements * zps);


		CPlacements * m_pplacements;
		CParallelLights m_parallelLights;
		CAudios m_audios;

		//	void SetRoot(CRoot * proot);
//		CRoot * m_proot;

		

#ifdef NETWORKMASTER
		unsigned int GetidId();
#endif
	private:
		void CopyDownwards();// Kopiert alle Eigenschaften des Placements rekursiv in der Hierarchie hinunter, belässt die Eigenschaften, wo ein Entry-Flag gesetzt wurde

		bool m_bFirstTick;
		CCameras m_cameras; // hier müssen alle Cameras verzeichnet sein, welche irgendwo die Szene betrachten
#ifdef NETWORKMASTER
		unsigned int m_idId;
		int m_icId;
#endif
	};

}