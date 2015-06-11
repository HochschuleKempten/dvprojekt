#pragma once

#include "Nodes.h"

namespace Vektoria
{

class CGeoCube;
class CRoot;
class CPlacement;

#define TEXT_BUFFER 256

#define S_KINDDIMENSION_UNDEFINED 0
#define S_KINDDIMENSION_ROOT 1
#define S_KINDDIMENSION_2D 2
#define S_KINDDIMENSION_3D 3
#define S_KINDDIMENSION_HARDWARE 4


#define S_KINDSUB_UNDEFINED 0
#define S_KINDSUB_GEOWALL 1
#define S_KINDSUB_GEOWINDOW 2
#define S_KINDSUB_GEOWING 3
#define S_KINDSUB_GEOCYLINDER 4
#define S_KINDSUB_GEOSPHERE 5
#define S_KINDSUB_GEODOME 6
#define S_KINDSUB_GEOTUBE 7
#define S_KINDSUB_GEOSLICE 8
#define S_KINDSUB_GEOTETRAEDER 9
#define S_KINDSUB_GEOIKOSAEDER 10
#define S_KINDSUB_GEOCUBE 11
#define S_KINDSUB_GEOCONE 12
#define S_KINDSUB_GEOELLIPSOID 13
#define S_KINDSUB_GEOTRIANGLE 14
#define S_KINDSUB_GEOSKYBOX 30
#define S_KINDSUB_GEOELLIPSOIDTILED 53
#define S_KINDSUB_GEOSPHERETILED 55
#define S_KINDSUB_GEODOMETILED 56
#define S_KINDSUB_GEOARROW 60
#define S_KINDSUB_GEOINFOVERTEX 61
#define S_KINDSUB_GEOINFOGEO 62
#define S_KINDSUB_GEOFRUSTUM 63

#define S_KIND_UNDEFINED 0
#define S_KIND_AUDIO 10
#define S_KIND_BACKGROUND 20
#define S_KIND_CAMERA 30
#define S_KIND_DEVICEKEYBOARD 40
#define S_KIND_DEVICEMOUSE 41
#define S_KIND_DEVICECURSOR 42
#define S_KIND_DEVICEGAMECONTROLLER 43
#define S_KIND_EMITTER 50
#define S_KIND_FRAME 60
#define S_KIND_GEO_TRIANGLELIST 71
#define S_KIND_GEO_TRIANGLESTRIP 72
#define S_KIND_HARDWARE 80
#define S_KIND_IMAGE 90
#define S_KIND_J 100
#define S_KIND_KEYFRAME 110
#define S_KIND_LIGHT_PARALLEL 120
#define S_KIND_LIGHT_POINT 121
#define S_KIND_LIGHT_SPOT 122
#define S_KIND_MATERIAL 130
#define S_KIND_N 140
#define S_KIND_OVERLAY 150
#define S_KIND_PLACEMENT 160
#define S_KIND_PHYSICAL 161
#define S_KIND_Q 170
#define S_KIND_ROOT 180
#define S_KIND_SCENE 190
#define S_KIND_TEXTURE 200
#define S_KIND_U 210
#define S_KIND_VIEWPORT 220
#define S_KIND_WRITING 230
#define S_KIND_WRITINGCHAR 231
#define S_KIND_WRIBEL 232
#define S_KIND_X 240
#define S_KIND_Y 250
#define S_KIND_Z 260



static unsigned int g_id = 0; // Fortlaufende Zählung der Knotenobjekte, mir fällt leider keine besser Möglichkeit ein, als eine globale Variable

class CNode 
{
	friend class CNodes;
	friend class CCamera;
	friend class CEmitter;
	friend class CPlacements;
	friend class CPlacement;
	friend class CGeoWall;
	friend class CGeoWindow;
	friend class CGeoWindows;
	friend class CGeoWing;
	friend class CGeos;
	friend class CGeo;
	friend class CTriangleList;
	friend class CTriangleStrip;
	friend class CNode3D;
	friend class CSprites;
	friend class CSprite;
	friend class CScenes;
	friend class CScene;
	friend class CAudios;
	friend class CAudio;
	friend class CRoot;

protected:
	void SetRoot(CRoot* proot);
	CRoot*  m_proot;

	void AddParent(CNode* pnodeParent);
	void SubParent(CNode* pnodeParent);

	void AddChild(CNode* pnodeChild);
	void SubChild(CNode* pnodeChild);
	void Init();
	void Fini();



public:
	CNode(void);
	~CNode(void);
	virtual const char* ClassName(void) { return "CNode"; } //Gibt den Namen der Klasse zurück

	void Copy(CNode & pnode);
    unsigned int GetID(void); // Gibt die eindeutige ID des Knotens zurück
    
    void SetName(const char* a_acName); // Setzt einen benutzerdefinierten Namen für diesen Knoten (z.B. "RootPlacement") -> Methode für Vektoria Editor
    const char* GetName(void); // Gibt den benutzerdefinierten Namen des Knotens zurück
    
    bool IsPlacement(void); // Gibt true zurück, wenn es sich bei diesem Knoten um ein Placement handelt, ansonsten false
    bool IsTriangleList(void); // Gibt true zurück, wenn es sich bei diesem Knoten um eine TriangleList handelt, ansonsten false
    bool IsTriangleStrip(void); // Gibt true zurück, wenn es sich bei diesem Knoten um ein TriangleStrip handelt, ansonsten false
    bool IsGeo(void); //Gibt true zurück, wenn es sich bei diesem knoten um eine Geo handelt, ansonsten false
	bool IsSpotLight(void); //Gibt true zurück, wenn es sich bei diesem knoten um ein SpotLight handelt, ansonsten false

	bool IsNode2D(void); // Gibt true zurück, wenn es sich bei diesem Knoten um ein 2D-Knoten (Sprite) handelt, ansonsten false
	bool IsNode3D(void); // Gibt true zurück, wenn es sich bei diesem Knoten um ein 3D-Knoten handelt, ansonsten false
    
	CNodes  m_nodesParents;
	CNodes  m_nodesChildren;

	int     m_eKindDimension;
	int     m_eKind;
    int     m_eKindSub;

	void SwitchOn(); // Schaltet Knoten mitsamzt seiner Unterhierarchie ein
	void SwitchOff(); // Schaltet Knoten mitsamzt seiner Unterhierarchie aus
	bool IsOn(); // Gibt true zurück, wenn Knoten angeschaltet ist
	bool m_bSwitch;  // boolsches Flag, um Zweig des Graphen aus(false) bzw. an(true) zu schalten
	
	int GetCount(void); // Gibt die Anzahl an Kindern zurück
	bool TypeOf(int iKind); // Gibt true zurück, wenn es sich bei diesem Knoten um einen Knoten vom Typ iKind handelt, ansonsten false
	char* m_acName;
	unsigned int m_id;
};

}