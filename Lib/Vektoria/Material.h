#pragma once
#include "Node.h"
#include "Textures.h"
#include "../VektoriaMath/Color.h"
#include <string>

#include "DistributedGlobal.h"


//---------------------------------------------------
// CMaterial: Klasse für Materialien
//
// Autoren: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2014-10-30
//---------------------------------------------------



//  0 = Diffuse,		 4 = Glow,			 8 = Specular,			12 = Bump
// 16 = DiffuseBlack,	20 = GlowAsDiffuse,	24 = SpecularAsDiffuse,	28 = HeightAsImage
// 32 = DiffuseWhite,	36 = GlowWhite,		40 = SpecularWhite,		44 = Height
// 48 = ShadingOff,		52 = Environment,	56 = POM


#define TEXFLAG_NODIFFUSE 0
#define TEXFLAG_DIFFUSE 1
#define TEXFLAG_DIFFUSEBLACK 2
#define TEXFLAG_DIFFUSEWHITE 3
#define TEXFLAG_DIFFUSEPURE 4

#define TEXFLAG_NOGLOW 0
#define TEXFLAG_GLOW 1
#define TEXFLAG_GLOWASDIFFUSE 2
#define TEXFLAG_GLOWWHITE 3
#define TEXFLAG_GLOWASAMBIENT 5

#define TEXFLAG_NOSPECULAR 0
#define TEXFLAG_SPECULAR 1
#define TEXFLAG_SPECULARASDIFFUSE 2
#define TEXFLAG_SPECULARWHITE 3

#define TEXFLAG_NOBUMP 0
#define TEXFLAG_BUMP 1
#define TEXFLAG_HEIGHTASDIFFUSE 2
#define TEXFLAG_HEIGHT 3

#define TEXFLAG_NOENVIRONMENTAL 0;
#define TEXFLAG_ENVIRONMENTAL 1;

#define TEXFLAG_NOTEXBRDF 0;
#define TEXFLAG_TEXBRDF 1;

#define TEXFLAG_NOPOM 0;
#define TEXFLAG_POM	  1;

#define TEXFLAG_NOPOMCONE 0;
#define TEXFLAG_POMCONE	  2;

#define TEXFLAG_NOTHICKNESS 0;
#define TEXFLAG_THICKNESS	1;

#define TEXFLAG_NOREFLECTIONMAP 0
#define TEXFLAG_REFLECTIONMAP 1


namespace Vektoria
{

	class CGeos;

	enum ETextureAddressMode
	{
		eTextureAdressMode_Wrap,
		eTextureAdressMode_Mirror,
		eTextureAdressMode_Clamp
	};

	enum ETransparencyKind
	{
		eTransparencyKind_No,
		eTransparencyKind_BinaryByAlphaTest,
		eTransparencyKind_BinaryByChromaKey,
		eTransparencyKind_Continual
	};


	class CHardware;

	class CMaterial : public CNode
	{
		friend class CMaterials;
	private:
		void Tick(float & fTimeDelta, CHardware & zh);
	public:
		CMaterial();
		~CMaterial();
		CMaterial operator=(CMaterial & material);
		void Copy(CMaterial & material);

		void Init();
		void Init(CColor colorDiffuse, CColor colorAmbient, CColor colorSpecular);
		void Fini();

		void SetTextureSky(CTexture *ptexture); // Setzt eine Textur, die für Skymaps, Skydomes etc. geeignet ist  
		void SetTextureDiffuse(CTexture *ptexture);
		void SetTextureGlow(CTexture *ptexture);
		void SetTextureSpecular(CTexture *ptexture);
		void SetTextureBump(CTexture *ptexture);
		void SetTextureHeight(CTexture *ptexture, bool bIsConeMap);
		void SetTextureEnvironment(CTexture *ptexture);
		void SetTextureThickness(CTexture* ptexture);
		void SetTextureSprite(CTexture *ptexture);	// Setzt eine Textur, die für Sprites wie Backgrounds, Overlays, Writings und WritingChars geeignet ist   

		CImage * MakeTextureDiffuse(char * acPath);
		CImage * MakeTextureGlow(char * acPath);
		CImage * MakeTextureSpecular(char * acPath);
		CImage * MakeTextureBump(char * acPath);
		CImage * MakeTextureHeight(char * acPath, bool bIsConeMap = false); //== Parallax Occlusion Mapping mit Heightmap oder Relaxed Conemap
		CImage * MakeTextureEnvironment(char * acPath);
		CImage * MakeTextureSky(char * acPath); // Erzeugt eine Texturhierarchie, die für Skymaps, Skydomes etc. geeignet ist  
		CImage * MakeTextureThickness(char * acPath, CColor colorSSS); // Materialdickebeschreibung für Subsurfacescattering und Farbe des Subsurfaces
		CImage * MakeTextureSprite(char * acPath); // Erzeugt eine Texturhierarchie, die für Sprites wie Backgrounds, Overlays, Writings und WritingChars geeignet ist   

		void SetAni(int ixPics, int iyPics, float fFps); // Erzeugt ein animiertes Material 
		void SetBot(int ixPics, int iyPics); // Erzeugt ein steuerbares Material
		void SetPic(int ixPic, int iyPic); // Setzt Unterbild bei animierten oder steuerbaren Materialien

		void SetShadingOn();
		void SetShadingOff();
		void SetTextureGlowWhite();
		void SetTextureGlowBlack();
		void SetTextureGlowAsDiffuse();
		void SetTextureGlowAsAmbient();
		void SetTextureSpecularWhite();
		void SetTextureSpecularBlack();
		void SetTextureSpecularAsDiffuse();
		void SetTextureTexBRDF(); // Texturbasiertes BRDF mit Normal- und Heightmap. Benötigt POM und Bumpmapping => TODO: Rausmachen !!!!
		void SetReflectionMap(); // Setzt Alphakanal der Environmentmap als Reflectionmap => TODO: Rausmachen !!!!

		void SetColorAmbient(CColor color); // Ambient-Light für
		void SetBumpStrength(float fBumpStrength); // Die Stärke der Bumpmap, Default = 1.0f, auch negative Werte ist  
		void SetSpecularSharpness(float fSpecularSharpness);
		void SetIndexOfRefraction(float fIOR); // Brechungsindex
		void SetDiffuseSharpness(float fDiffuseSharpness);
		void SetTransparency(float frTransparancy);
		void SetAbsoluteMaterialThickness(float fThickness); // Absolute Materialdicke für Subsurfacescattering, auch im Basic-Renderer
		void SetRimLightStrength(float fRimStrength); // Stärke der Glanzlichter des Subsurfacescattering
		void SetSubSurfaceColor(CColor color);
		void SetEnviromentMapIntensityReduction(float fIntensity); //Stärke der Enviromentmap verringern

		// Nur für FP-Renderer:
		void SetRoughness(float fRoughness); // Rauheit der Oberfläche, nur im FP-Render
		void SetSpecular(float fSpecular); // Wie spiegelnd ist die Oberfläche, nur im FP-Renderer 
		void SetSpecularTint(float fSpeculatTint); // Wieviel Farbe von der Diffuse-Map geht ins Highlight rein, nur im FP-Renderer 
		void SetMetallic(float fMetallic); // Metallischer Faktor 
		void SetSubsurface(float fSubsurface); // kein Subsurface-Scattering!, nur FP
		void SetAnisotropic(float fAnistropic); // Speculare Highlights sind nicht mehr rund, sondern anisotrop, nur FP
		void SetSheen(float fSheen); // Oberfläche leuchtet, niedriger Wert nehmen, nur FP
		void SetSheenTint(float fSheenTint); // Farbe von diffusen Material kommt dazu, nur FP
		void SetClearCoat(float fClearCoat); // wie Plastik, schwarfe spekulare Highlights, buggy!
		void SetClearCoatGloss(float fClearCoatGloss); // glossyness der spekularen Highligsts
		void SetBRDFReflectance(float fReflectance); // Stärke der Reflektionen des BRDF

		void SetTransparencyKind(ETransparencyKind eTransparencyKind); // Gibt die Transparenzart an: eTransparencyKind_No für opake Texturen, eTransparencyKind_BinaryByAlphaTest für ja-nein-Alpha-Texturen, eTransparencyKind_BinaryByChromaKey für Farbschlüsseltexturen, eTransparencyKind_Continual für Semitransparente Texturen mit Alpghakanal


		void SetTransparencyOn();
		void SetTransparencyOff();

		void SetChromaKeyingOn();
		void SetChromaKeyingOff();

		bool IsOpaque(); // Gibt true aus, falls es sich um eine vollkommen undurchsichtige Textur handelt, ansonsten, also wenn Chroma-Keying, Transparenz oder AlphaTest eingeschaltet ist wird false ausgegeben
		ETransparencyKind m_eTransparencyKind;


		void SetTextureAddressMode(ETextureAddressMode eTextureAddressMode);

		CTexture * m_ptextureDiffuse;
		CTexture * m_ptextureGlow;
		CTexture * m_ptextureSpecular;
		CTexture * m_ptextureBump;
		CTexture * m_ptextureEnvironment;
		CTexture * m_ptexturePOM;
		CTexture * m_ptextureThickness;

		CColor m_colorDiffuse;
		CColor m_colorAmbient;
		CColor m_colorSpecular;
		CColor m_colorSSS;

		float m_fDiffuseSharpness;
		float m_fSpecularSharpness;
		float m_fBumpStrength;
		float m_frTransparency;
		float m_fAbsoluteThickness;
		float m_fBRDFReflectance;
		float m_fRimLightStr;
		float m_fEnviromentInt;
		float m_fRoughness;
		float m_fIOR;
		float m_fSpecular;
		float m_fSpecularTint;
		float m_fMetallic;
		float m_fSubsurface;
		float m_fAnistropic;
		float m_fSheen;
		float m_fSheenTint;
		float m_fClearCoat;
		float m_fClearCoatGloss;

		int m_iFlagsDiffuse;
		int m_iFlagsGlow;
		int m_iFlagsSpecular;
		int m_iFlagsBump;
		int m_iFlagsEnvironment;
		int m_iFlagsPOM;
		int m_iFlagsTexBRDF;
		int m_iFlagsSSS;
		int m_iFlagsReflectionMap;

		bool m_bShading;
		int m_id;
		bool m_bChanged;
		bool m_bChangedAni;

		CGeos * m_pgeos; // Liste aller Geometrien, die das Material verwenden

		// Animierte Materialien:

		bool m_bAni; // true, wenn animiertes Material
		bool m_bBot; // true, wenn steuertbares Material
		int m_ixPics; // Animationsbilder in X-Richtung 
		int m_iyPics; // Animationsbilder in y-Richtung

		int m_ixPic; 
		int m_iyPic;

		int m_iPic;
		int m_iPics;
		float m_fPic;
		float m_fFps; // Bildwiederholrate von animierten Materialien

		ETextureAddressMode m_eTextureAddressMode;

#ifdef NETWORKMASTER
		unsigned int GetidId();

	private:

		unsigned int m_idId;
		int m_icId;
#endif
	};

}