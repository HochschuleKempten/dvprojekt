#pragma once

#include "VGeneral.h"
#include "VMaterialLoader.h"
#include "IViewBuilding.h"
#include "../logic/ILBuilding.h"
#include <array>
#include "VMaster.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B


class IViewModel
{
	NON_COPYABLE(IViewModel);

protected:
	CPlacement m_zpMain; //TODO (JS) make this private when m_zpLOD is used
	/** @brief Holds the different LOD levels for every model. m_zpLOD[0] is the nearest (much details) and m_zpLOD[2] is the furthest (less details) */
	std::array<CPlacement, 3> m_zpLOD;
	IViewBuilding* vBuilding = nullptr;
	CGeoCube m_zgFoundation;

public:
	inline IViewModel()
	{
		const float step = 100.0f / CASTS<float>(m_zpLOD.size());
		float previous = 0;

		for (size_t i = 0; i < m_zpLOD.size(); i++) {
			m_zpMain.AddPlacement(&m_zpLOD[i]);

			m_zpLOD[i].SetLoD(previous, previous + step);
			previous = previous + step;
		}
	}

	virtual inline ~IViewModel()
	{}

	inline void initViewModel(IViewBuilding* vBuilding)
	{
		this->vBuilding = vBuilding;

		float foundationWidth = vBuilding->getVMaster()->getPlayingField()->getFieldSize() * 0.2;
		float foundationHeight = foundationWidth * 0.2f;
		m_zgFoundation.Init(CHVector(foundationWidth, foundationHeight, foundationWidth), &VMaterialLoader::materialFoundationPlayer[vBuilding->getLBuilding()->getPlayerId()]);
	}

	virtual float getHeight() = 0;
	virtual float getWidth() = 0;

	virtual float getDepth()
	{
		return 0.0f;
	}

	inline CPlacement* getMainPlacement()
	{
		return &m_zpMain;
	}
};


NAMESPACE_VIEW_E
