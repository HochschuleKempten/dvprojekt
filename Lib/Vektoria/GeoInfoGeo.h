#pragma once
#include "GeoInfoVertex.h"

namespace Vektoria
{


	class CGeoInfoGeo : public CTriangleStrip
//		public CGeoInfoVertex
	{
	public:
		CGeoInfoGeo();
		~CGeoInfoGeo();

		void Init(CGeo & zg);
		CGeoInfoVertex * ageoinfovertex;
	};

}