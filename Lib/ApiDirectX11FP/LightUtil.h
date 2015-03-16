//------------------------------------------------------------------
// CLightUtil: Manages direct3D resources for lights 
//
// Author: Patrick Fleischmann
// Letzte Änderung: 2014-09-10
//-------------------------------------------------------------------

#pragma once

#include "DirectX11FP.h"

#include "..\Vektoria\PointLight.h"
#include "..\Vektoria\SpotLight.h"

#define MAX_LIGHT_NUM 1024
#define MAX_SHADOWCASTING_LIGHT_NUM 12

namespace Vektoria
{
	enum ELightMode
	{
		LIGHTING_SHADOWS = 0,
		LIGHTING_NOSHADOWS 
	};

	struct SSpotLightParams
	{
		unsigned short usLightDirX;
		unsigned short usLightDirY;
		unsigned short usCosineOfConeAngleAndLightDirZSign;
		unsigned short usFallOffRadius;
	};

	class CLightUtil
	{
	public:
		CLightUtil();
		~CLightUtil();

		void Init(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dContext);

		void AddShadowCastingPointLight(CPointLight& pointlight);
		void AddShadowCastingSpotLight(CSpotLight& spotlight);
		void AddPointLight(CPointLight& pointlight);
		void AddSpotLight(CSpotLight& spotlight);
		void UpdateLightBuffer();
		void ResetLightCount();

		unsigned GetPointLightCount(bool bShadow);
		unsigned GetSpotLightCount(bool bShadow);


		ID3D11ShaderResourceView* const* GetPointLightCenterAndRadiusSRV(int iLightingmode) const
		{	
			return (iLightingmode == LIGHTING_SHADOWS) ? &m_pShadowCastingPointLightCenterAndRadiusSRV :
															&m_pPointLightCenterAndRadiusSRV;
		}
		ID3D11ShaderResourceView* const* GetPointLightColorSRV(int iLightingmode) const
		{
			return (iLightingmode == LIGHTING_SHADOWS) ? &m_pShadowCastingPointLightColorSRV :
														   &m_pPointLightColorSRV;
		}
		ID3D11ShaderResourceView* const* GetSpotLightCenterAndRadiusSRV(int iLightmode) const
		{
			return (iLightmode == LIGHTING_SHADOWS) ? &m_pShadowCastingSpotLightCenterAndRadiusSRV :
													    &m_pSpotLightCenterAndRadiusSRV;
		}
		ID3D11ShaderResourceView* const* GetSpotLightColorSRV(int iLightmode) const
		{
			return (iLightmode == LIGHTING_SHADOWS) ? &m_pShadowCastingSpotLightColorSRV :
													    &m_pSpotLightColorSRV;
		}
		ID3D11ShaderResourceView* const* GetSpotLightParamsSRV(int iLightmode) const
		{
			return (iLightmode == LIGHTING_SHADOWS) ? &m_pShadowCastingSpotLightPramsSRV :
														&m_pSpotLightPramsSRV;
		}

		static const XMMATRIX(*GetShadowCastingPointLightViewProjTransArray())[6];
		static const XMMATRIX(*GetShadowCastingPointLightViewProjInvTransArray())[6];

		static const XMMATRIX* GetShadowCastingSpotLightViewProjTransArray();
		static const XMMATRIX* GetShadowCastingSpotLightViewProjInvTransArray();

		static const XMMATRIX(*GetShadowCastingPointLightViewProjTransArrayRSM())[6];
		static const XMMATRIX(*GetShadowCastingPointLightViewProjInvTransArrayRSM())[6];

		static const XMMATRIX* GetShadowCastingSpotLightViewProjTransArrayRSM();
		static const XMMATRIX* GetShadowCastingSpotLightViewProjInvTransArrayRSM();

	private:

		static void CalcSpotLightViewProj(const XMFLOAT4& vPositionAndRadius, const XMFLOAT3& vLookAt, const XMFLOAT3& vUp,
										  float fAperture, XMMATRIX* pmViewProjTransposed, XMMATRIX* pmViewProjInvTransposed,
										  bool bRSM);
		static void CalcSpotLightView(const XMFLOAT3& vEye, const XMFLOAT3& vLookAt, const XMFLOAT3& vUp, XMMATRIX& mView);
		static void CalcSpotLightProj(float fRadius, float fAperture, XMMATRIX& mProj);

		static void CalcSpotLightViewRSM(const XMFLOAT3& vEye, const XMFLOAT3& vLookAt, const XMFLOAT3& vUp, XMMATRIX& mView);
		static void CalcSpotLightProjRSM(float fRadius, float fAperture, XMMATRIX& mProj);

		static void CalcPointLightViewProj(const XMFLOAT4& vPositionAndRadius, XMMATRIX* pmViewProjTransposed,
										   XMMATRIX* pmViewProjInvTransposed, bool bRSM);
		static void CalcPointLightView(const XMFLOAT4& vPositionAndRadius, int iFace, XMMATRIX& mView);
		static void CalcPointLightProj(const XMFLOAT4& vPositionAndRadius, XMMATRIX& mProj);

		static void CalcPointLightViewRSM(const XMFLOAT4& vPositionAndRadius, int iFace, XMMATRIX& mView);
		static void CalcPointLightProjRSM(const XMFLOAT4& vPositionAndRadius, XMMATRIX& mProj);

		static SSpotLightParams PackSpotParams(const XMFLOAT3& vLightDir, float fCosineOfConeAngle, float fFallOffRadius);
		static unsigned short ConvertF32ToF16(float fVal);
		static DWORD PackColorParams(float fR, float fG, float fB);

		// Point lights
		ID3D11Buffer* m_pPointLightCenterAndRadiusBuffer;
		ID3D11ShaderResourceView* m_pPointLightCenterAndRadiusSRV;
		ID3D11Buffer* m_pPointLightColorBuffer;
		ID3D11ShaderResourceView* m_pPointLightColorSRV;
		// Shadow casting point lights
		ID3D11Buffer* m_pShadowCastingPointLightCenterAndRadiusBuffer;
		ID3D11ShaderResourceView* m_pShadowCastingPointLightCenterAndRadiusSRV;
		ID3D11Buffer* m_pShadowCastingPointLightColorBuffer;
		ID3D11ShaderResourceView* m_pShadowCastingPointLightColorSRV;
		// Spot lights
		ID3D11Buffer* m_pSpotLightCenterAndRadiusBuffer;
		ID3D11ShaderResourceView* m_pSpotLightCenterAndRadiusSRV;
		ID3D11Buffer* m_pSpotLightColorBuffer;
		ID3D11ShaderResourceView* m_pSpotLightColorSRV;
		ID3D11Buffer* m_pSpotlightParamsBuffer;
		ID3D11ShaderResourceView* m_pSpotLightPramsSRV;
		// Shadow casting spot lights
		ID3D11Buffer* m_pShadowCastingSpotLightCenterAndRadiusBuffer;
		ID3D11ShaderResourceView* m_pShadowCastingSpotLightCenterAndRadiusSRV;
		ID3D11Buffer* m_pShadowCastingSpotLightColorBuffer;
		ID3D11ShaderResourceView* m_pShadowCastingSpotLightColorSRV;
		ID3D11Buffer* m_pShadowCastingSpotlightParamsBuffer;
		ID3D11ShaderResourceView* m_pShadowCastingSpotLightPramsSRV;

		ID3D11Device* m_pd3dDevice;
		ID3D11DeviceContext* m_pd3dContext;

		unsigned m_uShadowSpotLightCount;
		unsigned m_uSpotLightCount;
		unsigned m_uShadowPointLightCount;
		unsigned m_uPointLightCount;
	};
}

