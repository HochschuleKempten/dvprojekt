#pragma once

#include "Node3D.h"

namespace Vektoria
{

class CLight;

enum ETopology
{
  ePoints,
  eLineList,
  eLineStrip,
  eTriangleList,
  eTriangleStrip,
  ePatch3List
};

struct SDrawableBufferInfo
{
  unsigned int stride;
  unsigned int iOffset;
  unsigned int iNumElements;
  ETopology etopology;
};

class CDrawable: public CNode3D
{
  public:
	  CDrawable() : m_bTransparent(false) { m_eKind = S_KIND_BLOEDE_BEZEICHNUNG_DRAWABLE; }

    virtual void BeforeDraw() = 0;
    virtual void AfterDraw() = 0;
    virtual void Draw(float fDistanceToCameraSquare, CHMat & mGlobal) = 0;
    virtual void UpdateAABB() = 0;

    SDrawableBufferInfo m_info;
    bool m_bTransparent;
    CLight * m_apLightsAffect[4];
    unsigned int m_iLightsAffectCount;
};

}