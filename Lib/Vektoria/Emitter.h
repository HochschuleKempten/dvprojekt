#pragma once
#include "Node3D.h"
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "Material.h"

//---------------------------------------------------
// CEmitter: Particle Emitter
//
// Autor: Michael Rücker
//---------------------------------------------------

namespace Vektoria
{

class CPlacements;
class CApiRender;
class CGeo;
class CTimer;

enum EState
{
	RUNNING = 1,
	STOPPED = 2,
	PAUSED = 3
};

enum ESpace 
{
	LOCAL,
	WORLD
};

enum EBlendMode
{
	ADDITIVE, 
	ADDITIVESOFT,
	MULTIPLICATIVE,
	MULTIPLICATIVE2X,
	ALPHA,
	ALPHAPREMULTIPLIED
};

enum ESpawnShapeType
{
	NONE,
	SPHERE,
	HEMISPHERE,
	PLANE,
	BOX,
	CONICAL_FRUSTUM
};

struct EParticleDistribution
{
	EParticleDistribution(){this->x = 0.0f; this->y = 0;};
	EParticleDistribution(float x, int y) {this->x = x; this->y = y;}
	float x;
	int y;
};

struct ERGBA
{
	char cR;
	char cG;
	char cB;
	float fA;
};

struct EGraphRectangle 
{
	EGraphRectangle() {}
	EGraphRectangle(float fIntervalLeft, float fIntervalRight) { this->fIntervalLeft = fIntervalLeft; this->fIntervalRight = fIntervalRight;}
	float fIntervalLeft;
	float fIntervalRight;
};

template<class T>
class CEGraph {
	friend class CEmitter;
	friend class CParticleRenderer;
public:
	void Add(int fPercent, T tValue) 
	{
		if (fPercent < 0) fPercent = 0;
		if (fPercent > 100) fPercent = 100;

		DataPoints.erase(fPercent);
		DataPoints.insert(std::pair<int,T>(fPercent, tValue));
	}

	void AddWithoutOverride(int fPercent, T tValue)
	{
		if (fPercent < 0) fPercent = 0;
		if (fPercent > 100) fPercent = 100;

		DataPoints.insert(std::pair<int,T>(fPercent, tValue));
	}

	void ClearDataPoints()
	{
		DataPoints.clear();
	}

	void CEGraph<T>::Interpolate();
	float CEGraph<T>::GetArea( float fIntervalLeft, float fIntervalRight );


private:
	float CEGraph<T>::CalcRectangleArea(float fXLeft, float fYLeft, float fXRight, float fYRight);
	float CEGraph<T>::GetValueOfPointOnLine(float fXLeft, float fYLeft, float fXRight, float fYRight, float fXPointOfInterest); 
	std::map<int, T> DataPoints;
	std::map<int, T> DataPointsInterpolated;
};

class CESpawnShape
{
public:
	CESpawnShape() {m_SpawnShapeType = NONE; bFilled = true; fAttribute1 = 0.0f; fAttribute2 = 0.0f; fAttribute3 = 0.0f;};
	ESpawnShapeType m_SpawnShapeType;
	bool bFilled;
	float fAttribute1;
	float fAttribute2;
	float fAttribute3;
};

class CESpawnShapePoint : public CESpawnShape {
public:
	CESpawnShapePoint() {m_SpawnShapeType = NONE;};
};

class CESpawnShapeSphere : public CESpawnShape {
public:
	CESpawnShapeSphere(float fRadius, bool bFilled = true) 
	{
		m_SpawnShapeType = SPHERE; this->fAttribute1 = fRadius; this->bFilled = bFilled;
	};
};

class CESpawnShapeHemisphere : public CESpawnShape {
public:
	CESpawnShapeHemisphere(float fRadius, bool bFilled = true) 
	{
		m_SpawnShapeType = HEMISPHERE; this->fAttribute1 = fRadius; this->bFilled = bFilled;
	};
};

class CESpawnShapePlane : public CESpawnShape {
public:
	CESpawnShapePlane(float fx, float fY) 
	{
		m_SpawnShapeType = PLANE; this->fAttribute1 = fx; this->fAttribute2 = fY;
	};
};

class CESpawnShapeBox : public CESpawnShape {
public:
	CESpawnShapeBox(float fx, float fY, float fZ, bool bFilled = true) 
	{
		m_SpawnShapeType = BOX; this->fAttribute1 = fx; this->fAttribute2 = fY; this->fAttribute3 = fZ; this->bFilled = bFilled;
	};
};

class CESpawnShapeConicalFrustum : public CESpawnShape {
public:
	CESpawnShapeConicalFrustum(float fHeight, float fRadiusBottom, float fRadiusTop, bool bFilled = true) 
	{
		m_SpawnShapeType = CONICAL_FRUSTUM; this->fAttribute1 = fHeight; this->fAttribute2 = fRadiusBottom; this->fAttribute3 = fRadiusTop; this->bFilled = bFilled;
	};
};

class CEBasic
{
	friend class CEmitter;
	friend class CParticleRenderer;
	friend class CEEmission;
	
public:
	CEBasic();
	~CEBasic(){};

	// The length of time the particle system is emitting particles.
	// Range: 0sec (0.0f) - 5 min (300.0f)
	void SetDuration(float fDuration);

	void SetMaxParticles(int iMaxParticles);

// 	// the particle lifetime
// 	void SetParticleLifetime(CEGraph<float> * fLifetime);

	// If loop is true, the particle system starts over as soon as the duration time has been passed.
	// If bCoolDown is true, the particle system updates and draws particles until all particles die naturally. (When their lifetime is over)
	void SetLoop(bool bLoop, bool bCoolDown = false);

	void SetBillboardSize(float fBillboardSizeX, float fBillboardSizeY);

	void Prewarm(float fSeconds);

	// fFactor is the softness factor. Range is between 0.000001f and 1.0f. The lower the harder the edge. 
	void SoftParticles(bool bEnabled, float fFactor);

	void Update();
private:
	CEmitter * m_pEmitter;
	bool m_bRequiresRendererUpdate;
	float m_fDuration;
	bool m_bLoop; 
	bool m_bCoolDown;
//	CEGraph<float> *m_fLifetime[2]; 
	int m_iMaxParticles;
	float m_fBillboardSizeX;
	float m_fBillboardSizeY;
	float m_fPrewarm;

	bool m_bSoftParticlesEnabled;
	float m_fSoftParticleFactor;
};


class CEEmission
{
	friend class CEmitter;
	friend class CParticleRenderer;

public:
	CEEmission();
	~CEEmission(){};

	void SpawnGraphAdd(int iPercent, float fValue);
	void SpawnGraphClear();

	// fTime must be between 0.1 and particle system duration
	void SpawnBurstsAdd(float fTime, int iParticles);

	// This indicates how many times per second the particle system checks for new particle spawns.
	// The higher this value the more memory and performance will be used.
	// Range is between 1 and 100.
	void SetSpawnAccuracy(int iSpawnAccuracy);

	void SetSpawnShape(CESpawnShape ssSpawnShape);

	void Update(bool bProcessSpawnRate = true);
private:
	CEmitter * m_pEmitter;
	bool m_bRequiresRendererUpdate;
	int m_iSpawnAccuracy;
	float m_fSpawnLastParticleFraction;
	//float m_fSpawnLastParticleBurstFraction;
	CEGraph<float> m_graphSpawnRate;
	std::map<int, float> m_mapParticleSpawnTimes;
	std::map<float, int> m_mapParticleSpawnBursts;
	void GetParticlesToSpawn(int iStartTime, int iEndTime, std::vector<EParticleDistribution> * vParticleDistribution, int * iArraySize, int * iParticleCount, int * iTimeOffset);
	void ProcessSpawnRate();

	CESpawnShape m_ssSpawnShape;
	
};


class CEVelocity
{
	friend class CEmitter;
	friend class CParticleRenderer;
public:
	CEVelocity();
	~CEVelocity(){};
	
	class CEVelocityOverTime {
		friend class CEVelocity;
		public:
			void IsRandBetweenGraphs(bool bActive);

			void GraphXAdd(int iPercent, float fValueTop, float fValueBottom = 0);
			void GraphXClear();

			void GraphYAdd(int iPercent, float fValueTop, float fValueBottom = 0);
			void GraphYClear();

			void GraphZAdd(int iPercent, float fValueTop, float fValueBottom = 0);
			void GraphZClear();
		private:
			void SetParent(CEVelocity *x) { m_pVelocity = x;};
			CEVelocity *m_pVelocity;
	};

	CEVelocityOverTime VelocityOverTime;
	void Update();
private:
	bool m_bVelocityOverTimeRandBetweenGraphs;
	CEmitter * m_pEmitter;
	bool m_bRequiresRendererUpdate;
	ESpace m_space;
	CEGraph<float> m_graphVelocityOverTimeTopX;
	CEGraph<float> m_graphVelocityOverTimeTopY;
	CEGraph<float> m_graphVelocityOverTimeTopZ;
	CEGraph<float> m_graphVelocityOverTimeBottomX;
	CEGraph<float> m_graphVelocityOverTimeBottomY;
	CEGraph<float> m_graphVelocityOverTimeBottomZ;


};

class CEForce
{
	friend class CEmitter;
	friend class CParticleRenderer;
public:
	CEForce();
	~CEForce(){};

	class CEForceOverTime {
		friend class CEForce;
		public:
			void IsRandBetweenGraphs(bool bActive);

			void GraphXAdd(int iPercent, float fValueTop, float fValueBottom = 0);
			void GraphXClear();

			void GraphYAdd(int iPercent, float fValueTop, float fValueBottom = 0);
			void GraphYClear();

			void GraphZAdd(int iPercent, float fValueTop, float fValueBottom = 0);
			void GraphZClear();
		private:
			void SetParent(CEForce *x) { m_pForce = x;};
			CEForce *m_pForce;
	};

	CEForceOverTime ForceOverTime;
	void Update();

private:
	CEmitter * m_pEmitter;
	bool m_bRequiresRendererUpdate;
	CEGraph<float> m_graphForceOverTimeTopX;
	CEGraph<float> m_graphForceOverTimeTopY;
	CEGraph<float> m_graphForceOverTimeTopZ;
	CEGraph<float> m_graphForceOverTimeBottomX;
	CEGraph<float> m_graphForceOverTimeBottomY;
	CEGraph<float> m_graphForceOverTimeBottomZ;
	ESpace m_space;
	bool m_bForceOverTimeRandBetweenGraphs;
};

class CETexture
{
	friend class CEmitter;
	friend class CParticleRenderer;
public:
	CETexture();
	~CETexture(){};

	class CEFramesOverTime {
		friend class CETexture;
		public:
			void IsRandBetweenGraphs(bool bActive);
			void GraphAdd(int iPercent, float fValueTop, float fValueBottom = 0);
			void GraphClear();
		private:
			void SetParent(CETexture *x) { m_pTexture = x;};
			CETexture *m_pTexture;
	};

	CEFramesOverTime FramesOverTime;

	void SetMaterial(CMaterial * pmaterial);
	void SetBlendMode(EBlendMode m_bmBlendMode, bool bAlphaToCoverageEnabled);
	void Update();

private:
	EBlendMode m_bmBlendMode;
	bool bAlphaToCoverageEnabled;
	CEmitter * m_pEmitter;
	bool m_bRequiresRendererUpdate;
	CEGraph<float> m_graphFramesOverLifetimeTop;
	CEGraph<float> m_graphFramesOverLifetimeBottom;
	bool m_bFramesOverTimeRandBetweenGraphs;
	CMaterial * m_pmaterial;
	int m_idMaterial;
};


class CESize
{
	friend class CEmitter;
	friend class CParticleRenderer;
public:
	CESize();
	~CESize(){};

	class CESizeOverTime {
		friend class CESize;
		public:
			void IsRandBetweenGraphs(bool bActive);
			void GraphAdd(int iPercent, float fValueTop, float fValueBottom = 0);
			void GraphClear();
		private:
			void SetParent(CESize *x) { m_pSize = x;};
			CESize *m_pSize;
	};

	class CESizeBySpeed {
		friend class CESize;
		public:
			void IsRandBetweenGraphs(bool bActive);
			void GraphAdd(int iPercent, float fValueTop, float fValueBottom = 0);
			void GraphClear();
			void SpeedRange(float fSpeedRangeBottom, float fSpeedRangeTop);
		private:
			void SetParent(CESize *x) { m_pSize = x;};
			CESize *m_pSize;
	};

	CESizeOverTime SizeOverTime;
	CESizeBySpeed SizeBySpeed;

	void Update();

private:
	CEmitter * m_pEmitter;
	bool m_bRequiresRendererUpdate;
	CEGraph<float> m_graphSizeOverTimeTop;
	CEGraph<float> m_graphSizeOverTimeBottom;
	bool m_bSizeOverTimeRandBetweenGraphs;

	CEGraph<float> m_graphSizeBySpeedTop;
	CEGraph<float> m_graphSizeBySpeedBottom;
	bool m_bSizeBySpeedRandBetweenGraphs;
	float m_fSizeBySpeedSpeedRangeBottom;
	float m_fSizeBySpeedSpeedRangeTop;

};

class CERotation
{
	friend class CEmitter;
	friend class CParticleRenderer;
public:
	CERotation();
	~CERotation(){};
	class CERotationOverTime {
		friend class CERotation;
	public:
		void IsRandBetweenGraphs(bool bActive);

		// rads per second
		void GraphAdd(int iPercent, float fValueTop, float fValueBottom = 0);
		void GraphClear();
	private:
		void SetParent(CERotation *x) { m_pRotation = x;};
		CERotation *m_pRotation;
	};
	
	class CERotationBySpeed {
		friend class CERotation;
	public:
		void IsRandBetweenGraphs(bool bActive);

		// rads per second
		void GraphAdd(int iPercent, float fValueTop, float fValueBottom = 0);
		void GraphClear();
		void SpeedRange(float fSpeedRangeBottom, float fSpeedRangeTop);
	private:
		void SetParent(CERotation *x) { m_pRotation = x;};
		CERotation *m_pRotation;
	};

	CERotationOverTime AngularVelocityOverTime;
	CERotationBySpeed AngularVelocityBySpeed;

	void Update();
private:
	CEmitter * m_pEmitter;
	bool m_bRequiresRendererUpdate;
	CEGraph<float> m_graphRotationOverTimeTop;
	CEGraph<float> m_graphRotationOverTimeBottom;
	bool m_bRotationOverTimeRandBetweenGraphs;

	CEGraph<float> m_graphRotationBySpeedTop;
	CEGraph<float> m_graphRotationBySpeedBottom;
	bool m_bRotationBySpeedRandBetweenGraphs;
	float m_fRotationBySpeedSpeedRangeBottom;
	float m_fRotationBySpeedSpeedRangeTop;
};

class CEColor
{
	friend class CEmitter;
	friend class CParticleRenderer;
public:
	CEColor();
	~CEColor(){};

	class CEColorOverTime {
		friend class CEColor;
	public:
		void IsRandBetweenGraphs(bool bActive);
		
		void GraphAdd(int iPercent, CColor fValueTop, CColor fValueBottom = CColor(1.0f, 1.0f, 1.0f, 1.0f));
		void GraphClear();
	private:
		void SetParent(CEColor *x) { m_pColor = x;};
		CEColor *m_pColor;
	};

	class CEColorBySpeed {
		friend class CEColor;
	public:
		void IsRandBetweenGraphs(bool bActive);

		void GraphAdd(int iPercent, CColor fValueTop, CColor fValueBottom = CColor(1.0f, 1.0f, 1.0f, 1.0f));
		void GraphClear();
		void SpeedRange(float fSpeedRangeBottom, float fSpeedRangeTop);
	private:
		void SetParent(CEColor *x) { m_pColor = x;};
		CEColor *m_pColor;
	};

	CEColorOverTime ColorOverTime;
	CEColorBySpeed ColorBySpeed;

	void Update();
private:
	CEmitter * m_pEmitter;
	bool m_bRequiresRendererUpdate;

	bool m_bColorOverTimeRandBetweenGraphs;
	CEGraph<CColor> m_graphColorOverTimeTop;
	CEGraph<CColor> m_graphColorOverTimeBottom;

	bool m_bColorBySpeedRandBetweenGraphs;
	CEGraph<CColor> m_graphColorBySpeedTop;
	CEGraph<CColor> m_graphColorBySpeedBottom;
	float m_fColorBySpeedSpeedRangeBottom;
	float m_fColorBySpeedSpeedRangeTop;
};

class CEmitter : public CNode3D
{
	friend class CEBasic;
	friend class CETexture;
	friend class CEEmission;
	friend class CEVelocity;
	friend class CEForce;
	friend class CERotation;
	friend class CESize;
	friend class CParticleRenderer;
	friend class CEColor;
public:
	CEmitter();
	~CEmitter();
	CEmitter operator=(CEmitter & emitter);
	void Copy(CEmitter & emitter);

	void Init();
	void Tick(CHMat & m, bool & bTick);
	void Fini();

	void Draw(CHMat & mGlobal );

	virtual void UpdateAABB();
	
	void Start();
	void Stop();
	void Pause();

	EState GetState();
	float GetElapsedTime();

	CEBasic Basic;
	CETexture Texture;
	CEEmission Emission;
	CEVelocity Velocity;
	CEForce Force;
	CESize Size;
	CERotation Rotation;
	CEColor Color;

private:
	EState m_estateRunningState;
	bool m_bInitialized;
	bool m_bUpdateEmitterData;
	float m_fElapsedTime;
	CTimer *m_ptimerRuntime;
	int m_iParticleSystemId;

	// Always updating everything is very slow and should not be called from the user. Do the individual updates per attribute if you change something. 
	// Making this private for now. Removes the possibility to abuse this function.
	void UpdateAllAttributes();
	
};

}