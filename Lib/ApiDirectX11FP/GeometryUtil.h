#pragma once

#include "DirectX11FP.h"

namespace Vektoria
{
	class CForwardPlusRenderer;
	class CMaterialUtil;
	class CGeometryUtil
	{
	public:
		CGeometryUtil();
		~CGeometryUtil();

		void Init(ID3D11Device* pdevice, ID3D11DeviceContext* pdevivecontext, CMaterialUtil* pMaterialUtil);

		void DrawOpaqueObjects(bool bWithMaterials, CForwardPlusRenderer* pCurrRenderer);
		void DrawTransparentObjects(bool bWithMaterials, CForwardPlusRenderer* pCurrRenderer);
		void DrawPPGeometrie(CViewport* pViewport, CForwardPlusRenderer* pCurrRenderer);
		void DrawBackGroundObjects(CForwardPlusRenderer* pCurrRenderer);
		void DrawTransparentBinaryObjects(bool bWithMaterials, CForwardPlusRenderer* pCurrRenderer);
		void DrawSprites(CForwardPlusRenderer* pCurrRenderer);
		void SortTransparentObjects();


		void UpdateTriangleList(CTriangleList *ptrianglelist, SRenderObjectHandle& handle);
		void UpdateTriangleStrip(CTriangleStrip *ptrianglestrip, SRenderObjectHandle& handle);
		SRenderObjectHandle CreateTriangleList(CTriangleList *ptrianglelist);
		SRenderObjectHandle CreateTriangleStrip(CTriangleStrip *ptrianglestrip);

		void FreeHandle(SRenderObjectHandle handle);
		void ClearRenderQueues();

		void SetObjectShaderConstantProjection(CHMat& mat);
		void SetObjectShaderConstantView(CHMat& mat);
		void SetObjectShaderConstantViewInv(CHMat& mat);

		void Draw(SRenderObjectHandle& handle, int& idTexture, float fDistanceToCameraSquare, int iKind, CHMat& mGlobal,
			CLight **aplightAffect, unsigned int iLightsAffectCount);

		unsigned int GetTransparentObjectCount();

	private:

		void DrawTriangleList(ID3D11Buffer *pbuffer);
		void DrawTriangleStrip(ID3D11Buffer *pbuffer, ID3D11Buffer *indexBuffer);
		void DrawDrawable(ID3D11Buffer *buffer, ID3D11Buffer *indexBuffer, CDrawable *pdrawable);


		void PassToGPU(SRenderObjectHandle & handle, int & idMaterial);
		void SetObjectDrawingParameters(CHMat &m, const unsigned int * pLightsAffectIndices,
			const unsigned int iLightsAffectCount,
			CForwardPlusRenderer* pCurrRenderer);
		void SetSpriteDrawingParameters(CHMat &m, CForwardPlusRenderer* pCurrRenderer);

		CMaterialUtil* m_pMaterialUtil;

		CDrawObjects m_drawobjectsBackground;
		CDrawObjects m_drawobjectsSprite;
		CDrawObjects m_drawobjectsSpriteTransparent;
		CDrawObjects m_drawobjectsOpaque;
		CDrawObjects m_drawobjectsTransparent;
		CDrawObjects m_drawobjectsTransparentBinary;

		SOBJECT_SHADER_CONSTANTS m_objectshaderconstants;
		SOBJECT_SHADER_CONSTANTS m_objectshaderconstantsParallelProjection;

		BufferMap m_buffermap;
		ID3D11Buffer *m_pbufferGPU;
		D3D11_BUFFER_DESC m_bufferdescVertex;

		CGeoQuad m_gPPQuad;
		CTriangleList* m_pgPPGeo;
		CMaterial m_mPPMaterial;
		
		ID3D11ShaderResourceView* m_pshaderresourceviewLights;

		ID3D11Device* m_pdevice;
		ID3D11DeviceContext* m_pdevicecontext;

	};
}

