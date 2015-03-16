#pragma once
#include "Backgrounds.h"
#include "Overlays.h"
#include "Writings.h"
#include "WritingChar.h"
#include "Camera.h"
#include "../VektoriaMath/Color.h"
#include "Placement.h"
#include <windows.h>

#include "DistributedGlobal.h"


//--------------------------------------------------------------------------------------------
// CVieport: Klasse für einen Bildschirmausschnitt zum Rendern
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2012-04-19
//--------------------------------------------------------------------------------------------

#define	S_STYLE_NORMAL 0x0
#define	S_STYLE_COLOR 0x01
#define	S_STYLE_HALFTRANSPARENT 0x02
#define	S_STYLE_POPART 0x04
#define	S_STYLE_OUTLINING 0x08
#define	S_STYLE_FOG 0x10
#define	S_STYLE_MONOCHROME 0x10
#define	S_STYLE_OWN 0x20

#define PP_GAUSSIAN_BLUR 1
#define PP_NOGAUSSIAN_BLUR 0
#define PP_ENHANCED_EDGES 1
#define PP_NOENHANCED_EDGES 0
#define PP_MEAN_FILTER 1
#define PP_NOMEAN_FILTER 0
#define PP_FXAA 1
#define PP_NOFXAA 0

namespace Vektoria
{

	class CRoot;
	class CFrame;

	struct SShadowParameter;
	struct SVPLParameter;

	struct SBloomParameter
	{
		float fOriginalIntensity;
		float fOriginalSaturation;
		float fBloomIntensity;
		float fBloomSaturation;
		float fBlurDistance;

		SBloomParameter()
			: fOriginalIntensity(1.f),
			  fOriginalSaturation(1.f),
			  fBloomIntensity(1.3f),
			  fBloomSaturation(1.3f),
			  fBlurDistance(0.0005f)
		{}
	};

	struct SGodRayParameter
	{
		float fExposure;
		float fDecay;
		float fDensity;
		float fWeight;
		CHVector vLightPos;

		SGodRayParameter()
			: fExposure(0.0024f),
			  fDecay(1.f),
			  fDensity(0.5f),
			  fWeight(8.f),
			  vLightPos(0.f, 0.f, 0.f, 1.f)
		{}
	};

	class CViewport : public CNode
	{

		friend class CViewports;
	private:
		void Tick(float & fTimeDelta, bool & bTickTack);
		bool m_bFirstTick;

	public:
		CViewport();
		~CViewport();
		CViewport operator=(CViewport & viewport);
		void Copy(CViewport & viewport);


		void InitFull(CCamera * pcamera); // Initialisiert Viewport, so dass er das gaze Frame ausfüllt
		void Init(CCamera * pcamera, float frx, float fry, float frWidth, float frHeight); // Initialisiert Viewport mit relativen Maßen zum Frame
		void Init(CCamera * pcamera, CFloatRect floatrect); // Initialisiert Viewport mit relativen Maßen zum Frame
		void Fini();

		void ReSize(float frx, float fry, float frWidth, float frHeight); // Verändert relative Größe des Viewports zum Frame
		void ReSize(); // Verändert Größe des Viewports bei veränderung der Größe des Frames
		void CalcSize(); // Berechnet absolute Ausmaße des Viewports

		void SetBackfaceCullingOn(); // Schaltet Backfaceculling an (Default: an) 
		void SetBackfaceCullingOff(); // Schaltet Backfaceculling aus(Default: an) 
		void SetAntialiasingOn(); // Schaltet Antialiasing an (funktioniert nur, wenn Grafikkarte dies unterstützt, Default: an) 
		void SetAntialiasingOff(); // Schaltet Antialiasing aus (Default: an) 
		void SetWireframeOff(); // Schaltet Drahtgittermodellmodus an (Default: aus) 
		void SetWireframeOn(); // Schaltet Drahtgittermodellmodus aus (Default: aus) 

		void SetShadowRenderingOn(); // Schaltet Schatten für den Viewport an (Default: an) 
		void SetShadowRenderingOff(); // Schaltet Schatten für den Viewport aus (Default: an) 
		void SetPointLightRenderingOn(); // Schaltet Punktlichter für den Viewport an (Default: an) 
		void SetPointLightRenderingOff(); // Schaltet Punktlichter für den Viewport aus (Default: an) 
		void SetParallelLightRenderingOn(); // Schaltet Parallellichter für den Viewport an (Default: an) 
		void SetParallelLightRenderingOff(); // Schaltet Parallellichter für den Viewport aus (Default: an) 
		void SetSpotLightRenderingOn(); // Schaltet Schweinwerferlichter für den Viewport an (Default: an) 
		void SetSpotLightRenderingOff(); // Schaltet Scheinwerferlichter für den Viewport aus (Default: an) 

		void SetFogOn(); // Schaltet Nebel an
		void SetFogOff(); // Schaltet Nebel aus
		void SetFogStrength(float fFogStrength); // Gibt Nebelstärke an, Default = 0.01 
		float m_fFogStrengthInv;

		void SetStyle(int eStyle); // Schaltet bestimmten Rendering-Stil an, die Stile sind kombinierbar 
		void SetStyleOutlineTheshold(float frStyleOutlineThreshold); // Gibt den fraktionalen Grenzwert für das Outlining an, default = 0.5
		void SetColorOutline(CColor & colorOutline); // Setzt die Konturfarbe, zur Parametrisierung eines Renderingstiles

		CCamera * GetCamera(); // Holt die mit dem Viewport assoziierte Kamera
		CScene * GetScene(); // Holt die mit dem Viewport assoziierte Szene

		void StyleOwn(); // Schaltet denjenigen Teil, den man selbst im Shader verändern kann, an
		void StylePopArt(); // Schaltet auf Pop-Style-Anmutung
		void StyleCartoon(); // Schaltet auf Cartoon-Anmutung
		void StyleOutlining(); // Schaltet Konturierung an
		void StyleMonochrome(CColor c); // Schaltet Monochrome-Anmutung an, c gibt die Färbung an
		void StyleSepia(); // Schaltet Sepia-Anmutung an
		void StylePurpleHaze(); // Schaltet auf PurpleHaze-Anmutung
		void StyleBlueDream(); // Schaltet BlueDream-Anmutung an
		void StyleBlackWhite(); // Schaltet Schwarzweiß-Anmutung an
		void StyleContrast(float fr); // Erhöht Kontrast (Werte>0) bzw. vermindert Kontrast (Werte<0)
		void StyleContrast(CColor c); // Erhöht Kontrast (Werte>0) bzw. vermindert Kontrast (Werte<0) jeweils getrennt nach RGB-Werten 
		void StyleBrightness(float fr); // Erhöht Helligkeit (Werte>1), vermindert Helligkeit (Werte 0..1), invertiert Farbe (Wert<0) 
		void StyleBrightness(CColor c); // Erhöht Helligkeit (Werte>1), vermindert helligkeit (Werte 0..1), invertiert Farbe (Wert<0) jeweils getrennt nach RGB-Werten 
		void StyleRotateHue(float faHue); // Rotiert Farbwert um den Winkel fa im Bogenmaß
		void StyleInverse(); // Invertiert alle Farben
		void StyleOff(); // Schaltet alle Stile aus

		void SetPostProcessingGeo(CTriangleList* pgeo); // Setzt alternative Postprocessing-Geometrie
		void SetGaussianBlur(float fRadius); // Unschärfefilter mit Radius
		void SetGaussianBlurOff();
		void SetEnhancedEdgesOn(); // Schärfere Kanten und höhere Kontraste mit horizontalen und vertikalen Sobel-Operatoren
		void SetEnhancedEdgesOff();
		void SetMeanFilterOn(); // Filter mit gleichverteilter Unschärfe
		void SetMeanFilterOff();
		void SetFXAAOn();
		void SetFXAAOff();
		void SetBloomOn();
		void SetBloomOff();
		void SetGoodRaysOn();
		void SetGoodRaysOff();
	// 	void SetShadowRenderingOn();
	// 	void SetShadowRenderingOff();
		void SetVPLsOn();
		void SetVPLsOff();


		/*
		void GaussianBlur(float fRadius); // Unschärfefilter mit Radius
		void GaussianBlurOff(); 
		void EnhancedEdges(); // Schärfere Kanten und höhere Kontraste mit horizontalen und vertikalen Sobel-Operatoren
		void EnhancedEdgesOff();  
		void MeanFilter(); // Filter mit gleichverteilter Unschärfe
		void MeanFilterOff();
		void EnableFXAA();
		void DisableFXAA();
		void EnableBloom();
		void DisableBloom();
		void EnableGoodRays();
		void DisableGoodRays();

		void EnableShadowRendering();
		void EnableVPLs();
		*/
		void SetMSAASamples(int iSamples); // 1, 2 oder 4

		void FixedSpotLightShadow(); // Schatten werden nicht neu berechnet
		void FixedPointLightShadow();  // Schatten werden nicht neu berechnet
		void DynamicSpotLightShadow();  // Schatten werden pro Tick neu berechnet
		void DynamicPointLightShadow(); // Schatten werden pro Tick neu berechnet
		void SetPointShadowRes(unsigned uShadowRes); // Auflösung der Punktlichtschatten
		void SetSpotShadowRes(unsigned uShadowRes); // Auflösung der Spotlichtschatten
		void SetShadowBiasSpot(float fBias);
		void SetShadowBiasPoint(float fBias);

		void AddOverlay(COverlay * poverlay); // Hängt ein 2D-Sprite an den Viewport an
		bool SubOverlay(COverlay * poverlay); // Hängt ein vorhandenes 2D-Sprite vom Viewport ab, gibt true aus, wenn's geklappt hat

		void AddBackground(CBackground * pbackground); // Hängt einen 2D-Hintergrund an den Viewport an
		bool SubBackground(CBackground * pbackground); // Hängt ein vorhandenes 2D-Background vom Viewport ab, gibt true aus, wenn's geklappt hat

		void AddWriting(CWriting * pwriting); // Hängt ein Writing-Textfeld an den Viewport an
		bool SubWriting(CWriting * pwriting); // Hängt ein vorhandenes Writing-Textfeld vom Viewport ab, gibt true aus, wenn's geklappt hat

		void AddWritingChar(CWritingChar * pwritingchar); // Hängt ein Writing-Buchstabenfeld an den Viewport an
		bool SubWritingChar(CWritingChar * pwritingchar); // Hängt ein vorhandenes Writing-Buchstabenfeld vom Viewport ab, gibt true aus, wenn's geklappt hat

		void SetAmbientColor(CColor colorAmbientUp, CColor colorAmbientDown);

		bool FrameToViewportCoord(float & frx, float & fry); // Übersetzt die Koordinaten des Frames in Koordinaten des Viewports, gibt true aus, wenn Cursor innerhalb des Viewports liegt

		COverlays m_overlays;
		CBackgrounds m_backgrounds;
		CWritings m_writings;

		void SetNewVPLParams(SVPLParameter* pVplParams);
		void SetNewShadowParams(SShadowParameter* pShadowparams);
		void SetNewBloomParams(SBloomParameter* pBloomParams);
		void SetNewGodRayParams(SGodRayParameter* pGodRayParams);

		int m_ix;
		int m_iy;
		int m_iWidth;
		int m_iHeight;

		float m_frx;
		float m_fry;
		float m_frWidth;
		float m_frHeight;

		bool m_bBackfaceCulling;
		bool m_bAntialiasing;
		bool m_bWireframe;
		bool m_bParallelLightRendering;
		bool m_bSpotLightRendering;
		bool m_bPointLightRendering;
		bool m_bShadowRendering;

		float m_fAspectRatio;
		CCamera * m_pcamera;
		CFrame * m_pframe;
		bool m_bInit;
		int m_i;
		int m_eStyle;

		unsigned int m_uiPP_GaussianBlur;
		float m_fGaussianBlurRadius;
		unsigned int m_uiPP_EnhancedEdges;
		unsigned int m_uiPP_MeanFilter;
		unsigned int m_uiPP_FXAA;

		CHMat m_mColorModification;

		CColor m_colorOutline;
		void SetFrame(CFrame * pframe);
		void SetRoot(CRoot * proot);
		CRoot * m_proot;

		CTriangleList* m_pgPostProcessing;
		SRenderObjectHandle m_PostProcessingRHND;
		bool m_bFirstPPDraw;
		bool m_bPPGeoIsSet;

		bool m_bMSAAEnabled;
		bool m_bShadowsEnabled;
		bool m_bVPLSEnabled;
		int m_iMSAASamples;
		bool m_bFixedSpotShadows;
		bool m_bFixedPointShadows;
		unsigned m_uSpotShadowRes;
		unsigned m_uPointShadowRes;
		bool m_bBloom;
		bool m_bGodRays;
		bool m_bDoF;
		float m_fTimeDelta;
		CHVector m_vDofParams;

		CColor m_colorAmbientUp;
		CColor m_colorAmbientDown;

		SVPLParameter m_vplParams;
		SShadowParameter m_shadowParams;
		SBloomParameter m_bloomParams;
		SGodRayParameter m_godRayParams;
		
#ifdef NETWORKMASTER
		unsigned int GetidId();
	private:

		unsigned int m_idId;
		int m_icId;
#endif


	};

}