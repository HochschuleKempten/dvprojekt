#pragma once
#include "TriangleStrip.h"
#include "GeoArrow.h"
#include "GeoSphere.h"
#include "Vertex.h"

namespace Vektoria
{


	class CGeoInfoVertex : public CTriangleStrip
	{
	public:
		CGeoInfoVertex();
		~CGeoInfoVertex();

		void Init(CVertex & vertex, float fRadiusUnit = 1.0f, int iGranularity = 7);
		void Init(CVertex & vertex, float fRadiusUnit, CMaterial * pzmNormal, CMaterial * pzmTangent, CMaterial * pzmBitangent, CMaterial * pzmPos, int iGranularity = 7);

		CGeoArrow azgArrow[3];
		CGeoSphere zgSphere;
	};

}