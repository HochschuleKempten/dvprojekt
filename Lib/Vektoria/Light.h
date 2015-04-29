#pragma once
#include "Node3D.h"
#include "../VektoriaMath/Color.h"
#include "ApiRender.h"
#include "Geo.h"

//---------------------------------------------------
// CLight: Klasse für Lichter
//
// Autoren: Prof. Dr. Tobias Breiner, Florian Schnell
// Letzte Änderung: 2012-06-05
//---------------------------------------------------

// specifies the maximum of lightsources that can be created
#define LIGHTS_MAX 100

namespace Vektoria
{


struct SShadowParameter
{
	float fPointBlurSize; // default 2.5f
	float fPointShadowBias; // default 10.f
	float fSpotShadowBias; // default 1.2f

	SShadowParameter() :
		fPointBlurSize(2.5f),
		fPointShadowBias(100.f),
		fSpotShadowBias(12.f)
	{}
};

struct SVPLParameter
{
	float fVPLSpotStrength; // default 80
	float fVPLPointStrength; // default 20
	float fVPLSpotRadius; // default 10
	float fVPLPointRadius; // default 10
	float fVPLColorThreshold; // default 70
	float fVPLBrightnessCutoff; // default 18
	float fVPLBackFaceContribution; // default 50

	SVPLParameter() :
		fVPLSpotStrength(30),
		fVPLPointStrength(30),
		fVPLSpotRadius(15),
		fVPLPointRadius(10.f),
		fVPLColorThreshold(70),
		fVPLBrightnessCutoff(18),
		fVPLBackFaceContribution(99)
	{}
};

class CLight : public CNode3D
{
	friend class CLights;
	friend class CParallelLights;
	friend class CPointLights;
	friend class CSpotLights;
protected: 
	void Tick(CHMat & m, float & fTimeDelta, bool & bTick);



public:
	static unsigned int s_iLightCount;
	static CLight **s_ppLights;
	static void FindLights(CGeo *geo);
 
	CLight();
	~CLight();
	CLight operator=(CLight light);
	void Copy(CLight light);

	void Init(CColor pcolor);
	void Fini();

	virtual void UpdateAABB();


	// parameters every light should have
	CColor m_color;
	bool m_bActivated;
	float m_fAttenuationConstant;
	float m_fAttenuationLinear;
	float m_fAttenuationQuadratic;

	// shadow casting
	bool m_bCauseShadow;
	CHMat m_mProjection;
	CHMat m_mView;
	void SetShadowMapResolution(int iPixelsWidth, int iPixelsHeight);
	int m_iShadowMapWidth;
	int m_iShadowMapHeight;

	SRenderObjectHandle m_handle;

private:
  static int FindLights(CHVector &vPosition, CLight **apLightsAffect);
};

}