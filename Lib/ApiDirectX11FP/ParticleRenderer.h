// ------------------------------------------------------------------
// CParticleRenderer: This class handles the DirectX rendering for our particle system.
// 
// Autor: Michael Ruecker
// -------------------------------------------------------------------
// 
// #pragma once
// #include "DirectX11FP.h"
// namespace Vektoria
// {
// 
// class CEmitter;
// 
// debug
// struct  DebugThreadGroups
// {
// 	UINT a;
// 	UINT b;
// 	UINT c;
// };
// 
// struct DebugBla
// {
// 	DebugBla(int a, int b, EParticleDistribution * c) {this->a = a; this->b = b; memcpy(this->c, c, 500*sizeof(EParticleDistribution)); /*this->c = c;this->d = d;*/};
// 	int a;
// 	int b;
// 	EParticleDistribution c[500];
// 	int c;
// 	int d;
// };
// 
// ---
// 
// 
// struct PARTICLE
// {
// 	D3DXVECTOR4 position;
// 	D3DXVECTOR4 spawnPosition;
// 	D3DXVECTOR4 color;
// 	float fBirthTime;
// 	float fLastUpdateTime;
// 	float fRandBetweenVelocityOverTimeX;
// 	float fRandBetweenVelocityOverTimeY;
// 	float fRandBetweenVelocityOverTimeZ;
// 	float fRandBetweenForceOverTimeX;
// 	float fRandBetweenForceOverTimeY;
// 	float fRandBetweenForceOverTimeZ;
// 	int iPicNumber;
// 	float fRandBetweenTextureAnim;
// 	float fSizeMultiplicator;
// 	float fRandBetweenSizeOverTime;
// 	float fRandBetweenSizeBySpeed;
// 	float fAngularVelocityRad;
// 	float fAngularVelocityRadBySpeed;
// 	float fRandBetweenRotationOverTime;
// 	float fRandBetweenRotationBySpeed;
// 	float fRandBetweenColorOverTime;
// 	float fRandBetweenColorBySpeed;
// };
// 
// 
// struct PARTICLE_SPAWN_DATA
// {
// 	int iParticlesToSpawn;
// 	int iArrayEntries;
// };
// 
// struct PARTICLE_SPAWN_DISTRIBUTION
// {
// 	float fTime;
// 	int iMaxParticleId;
// };
// 
// struct PARTICLE_SYSTEM_CB_DATA_UPDATE_PER_FRAME
// {
// 	float fTimeDelta;
// 	float fDuration;
// 	float fNearClipping;
// 	float fFarClipping;
// 	float fMSAAEnabled;
// 	D3DXVECTOR2 fScreenSize;
// };		   
// 
// struct PARTICLE_SYSTEM_CB_DATA_UPDATE_PER_USER_REQUEST
// {
// 	// we have to use D3DXVECTOR4 here instead of other data types because directx packs everything in 4 byte groups.
// 	// i have to change this later
// 	// http://msdn.microsoft.com/en-us/library/windows/desktop/bb509632(v=vs.85).aspx
// 	D3DXVECTOR4 fDistanceThroughVelocityTop[101];
// 	D3DXVECTOR4 fDistanceThroughVelocityBottom[101];
// 	D3DXVECTOR4 fDistanceThroughForceTop[101];
// 	D3DXVECTOR4 fDistanceThroughForceBottom[101];
// 	D3DXVECTOR4 fTextureFrame[101];
// 	D3DXVECTOR4 fSizeOverTime[101];
// 	D3DXVECTOR4 fSizeBySpeed[101];
// 	D3DXVECTOR4 fRotationOverTime[101];
// 	D3DXVECTOR4 fRotationOverTimeBySpeed[101];
// 	D3DXVECTOR4 fColorOverTimeTop[101];
// 	D3DXVECTOR4 fColorOverTimeBottom[101];
// 	D3DXVECTOR4 fColorBySpeedTop[101];
// 	D3DXVECTOR4 fColorBySpeedBottom[101];
// 	D3DXVECTOR4 fSizeBySpeedSpeedRange; // 2x float
// 	D3DXVECTOR4 fRotationBySpeedSpeedRange; // 2x float
// 	D3DXVECTOR4 fColorBySpeedSpeedRange; // 2x float
// 	D3DXVECTOR4 fBillboardSize; // 2x float
// 	D3DXVECTOR4 iTileCount; // 2x int
// 	D3DXVECTOR4 bRandomBetweenVelocity; // bool
// 	D3DXVECTOR4 bRandomBetweenForce; // bool
// 	D3DXVECTOR4 bRandomBetweenTextureAnim; // bool
// 	D3DXVECTOR4 bRandBetweenSizeOverTime; // bool
// 	D3DXVECTOR4 bRandBetweenSizeBySpeed; // bool
// 	D3DXVECTOR4 bRandBetweenRotationOverTime; // bool
// 	D3DXVECTOR4 bRandBetweenRotationBySpeed; // bool
// 	D3DXVECTOR4 bRandBetweenColorOverTime; // bool
// 	D3DXVECTOR4 bRandBetweenColorBySpeed; // bool
// 	D3DXVECTOR4 iSpawnShapeId; // iSpawnShapeId.x = SpawnShape. 0 == NONE, 1 == SPHERE, 2 == HEMISPHERE, 3 == PLANE, 4 == BOX, 5 == CONICAL_FRUSTUM
// 	D3DXVECTOR4 fSpawnShapeParams; // .x = param1, .y = param2, .z = param3, .w = param4
// 	D3DXVECTOR4 bSoftParticlesEnabled; // bool
// 	D3DXVECTOR4 fSoftParticlesFactor; // 1x float
// 	int iMaxParticles;
// };
// 
// 
// struct PARTICLE_SYSTEM_DATA
// {
// 	int iParticleSystemId;
// 	CHMat mGlobal;
// 	ID3D11Buffer *m_pbSimulationStateCurrent;
// 	ID3D11Buffer *m_pbSimulationSateNew;
// 	ID3D11Buffer *m_pbParticleCountBuffer;
// 	ID3D11Buffer *m_pbThreadGroupsForUpdate;
// 	ID3D11Buffer *m_pbParticleSpawnData;
// 	ID3D11Buffer *m_pbParticleDistribution;
// 	ID3D11Buffer *m_pbDrawIndirectArgs;
// 	ID3D11Buffer *m_pbActiveParticleCount;
// 	ID3D11UnorderedAccessView *m_puavActiveParticleCount;
// 	ID3D11UnorderedAccessView *m_puavSimulationSateCurrent;
// 	ID3D11UnorderedAccessView *m_puavSimulationSateNew;
// 	ID3D11UnorderedAccessView *m_puavThreadGroupsForUpdate;
// 	ID3D11ShaderResourceView *m_psrvSimulationSateCurrent;
// 	ID3D11ShaderResourceView *m_psrvSimulationSateNew;
// 	ID3D11ShaderResourceView *m_psrvParticleSpawnData;
// 	ID3D11ShaderResourceView *m_psrvParticleDistribution;
// 	unsigned int uiActiveParticles;
// 	CEmitter * pEmitter;
// 	int iTimeUnitsPassedLastRound;
// 	ID3D11Buffer *m_pbDataUpdatePerUserRequest;
// 	PARTICLE_SYSTEM_CB_DATA_UPDATE_PER_USER_REQUEST m_cbDataUpdatePerUserRequest;
// 	std::vector<EParticleDistribution> aParticleDistribution;
// 	EState iLastState;
// 	ID3D11BlendState* pBlendingState;
// 	ID3D11DepthStencilState *pDepthStencilState;
// };
// 
// struct PARTICLE_SYSTEM_DEBUG_DATA
// {
// 	int iParticleCountCurrent;
// 	int iParticleCountNew;
// };
// 
// class CParticleRenderer
// {
// public:
// 	CParticleRenderer(CDirectX11FP *pRenderAPI);
// 	~CParticleRenderer(void);
// 	void AddEmitter(CEmitter * pEmitter);
// 	void CreateSamplerState();
// 	void CreateSRVs( PARTICLE_SYSTEM_DATA &NewParticleSystem );
// 	void CreateUAVs( PARTICLE_SYSTEM_DATA &NewParticleSystem );
// 	void CreateBuffers( int imaxParticleCount, PARTICLE_SYSTEM_DATA &NewParticleSystem );
// 	void InitShaders();
// 	void ComputeAndRenderParticles();
// 
// 	//void SpawnNewParticlesWithPrewarm( std::vector<PARTICLE_SYSTEM_DATA>::iterator it );
// 
// 	void UpdateParticles( std::vector<ID3D11UnorderedAccessView*> &uavsParticleSimulation, std::vector<PARTICLE_SYSTEM_DATA>::iterator it );
// 
// 	void DrawParticles( std::vector<PARTICLE_SYSTEM_DATA>::iterator it);
// 
// 	void SpawnNewParticles( std::vector<PARTICLE_SYSTEM_DATA>::iterator it);
// 
// 	void DisableAlphaBlending(std::vector<PARTICLE_SYSTEM_DATA>::iterator it);
// 
// 	void EnableAlphaBlending(std::vector<PARTICLE_SYSTEM_DATA>::iterator it);
// 
// 	void CalculateThreadGroupsForUpdate( std::vector<PARTICLE_SYSTEM_DATA>::iterator it );
// 
// 	void UpdateShaderDataPerFrame( std::vector<PARTICLE_SYSTEM_DATA>::iterator it );
// 	void UpdateShaderDataPerUserRequest( CEmitter * pEmitter );
// 
// 	void SwapSimulationStates( std::vector<PARTICLE_SYSTEM_DATA>::iterator it );
// 
// 	void DeactivateShaders();
// 	void ActivateShaders();
// 	void CreateBlendState(std::vector<PARTICLE_SYSTEM_DATA>::iterator it);
// 
// private:
// 	CDirectX11FP *m_pRenderAPI;
// 
// 	// General
// 	int m_iVertexShaderId, m_iPixelShaderId, m_iGeometryShaderId, m_iComputeShaderSimulateId, m_iComputeShaderSpawnId, m_iComputeShaderCalculateThreadGroupsForUpdateId;
// 	int m_iParticleSystemId;
// 	std::vector<PARTICLE_SYSTEM_DATA> m_ParticleSystems;
// 	ID3D11Buffer *m_pbufferParticleSystemDataUpdatePerFrame;
// 	PARTICLE_SYSTEM_CB_DATA_UPDATE_PER_FRAME m_cbParticleSystemDataUpdatePerFrame;
// 	
// 	// sampler states
// 	ID3D11SamplerState* m_samplerstateLinear;
// 	ID3D11SamplerState* m_samplerstatePoint;
// 
// 	// blend states
// 	float m_BlendFactor[4];
// 	ID3D11BlendState* m_OldBlendingState;
// 	ID3D11DepthStencilState *m_pOldDepthStencilState;
// 
// 
// 	// debug
// 	bool m_bDebug;
// 	PARTICLE_SYSTEM_DEBUG_DATA m_DebugData;
// 	std::vector<DebugBla> m_DebugParticleSpawnTimes;
// 
// 
// 	// will be removed maybe
// 	PARTICLE * m_pverticesParticleSystem;
// 	//ID3D11UnorderedAccessView *m_puacurrentSimulationSate;
// 	//ID3D11ShaderResourceView *m_psrvcurrentSimulationSateSRV;
// 	// ID3D11Buffer *m_pbcurrentSimulationSate;
// 	//UINT m_imaxParticleCount;
// 	ID3D11Buffer *m_pbverticesIndex;
// 	ID3D11ShaderResourceView* m_texture;
// 	
// };
// 
// }