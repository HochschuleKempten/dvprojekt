#pragma once

#include "Material.h"

namespace Vektoria
{
	namespace MaterialPreset
	{
		class CMaterialPreset
		{
		public:
			virtual CMaterial* GetMaterial() = 0;
		};

		//////////////////////////////////////////////////////////////////////////
		// Marble
		class CMPMarble : public CMaterialPreset
		{
		public:
			CMPMarble();
			~CMPMarble();

			CMaterial* GetMaterial();

			CMaterial m_mat;
		};

		//////////////////////////////////////////////////////////////////////////
		// Black rubber
		class CMPBlackRubber : public CMaterialPreset
		{
		public:
			CMPBlackRubber();
			~CMPBlackRubber();

			CMaterial* GetMaterial();

			CMaterial m_mat;
		};

		//////////////////////////////////////////////////////////////////////////
		// Wood planks
		class CMPWoodPlanks : public CMaterialPreset
		{
		public:
			CMPWoodPlanks();
			~CMPWoodPlanks();

			CMaterial* GetMaterial();

			CMaterial m_mat;
		};

		//////////////////////////////////////////////////////////////////////////
		// Cobble stone wall
		class CMPCobbleStoneWall : public CMaterialPreset
		{
		public:
			CMPCobbleStoneWall();
			~CMPCobbleStoneWall();

			CMaterial* GetMaterial();

			CMaterial m_mat;
		};
	}
}

