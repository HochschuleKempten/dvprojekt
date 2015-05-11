#pragma once

#include "VGeneral.h"
#include "VMaterialLoader.h"
#include "../logic/ILBuilding.h"
#include "IViewBuilding.h"
#include "VMaster.h"
#include "VPlayingField.h"
#include <array>

NAMESPACE_VIEW_B


class IViewModel
{
	NON_COPYABLE(IViewModel);

private:
	static const int LODLevels = 3;

protected:
	CPlacement m_zpMain;
	/** @brief Holds the different LOD levels for every model. m_zpLOD[0] is the nearest (much details) and m_zpLOD[2] is the furthest (less details) */
	std::array<CPlacement, LODLevels> m_zpLOD;
	/** @brief Holds the different LOD borders. m_zpLODBorder[0] = 0 and m_zpLODBorder[LODLevels + 1] = MAX */
	std::array<float, LODLevels + 1> m_zpLODBorder;
	IViewBuilding* vBuilding = nullptr;
	CGeoCube m_zgFoundation;
	float foundationWidth = 0.4f;
	float foundationHeight = 0.08f;

public:
	inline IViewModel()
	{
		const float step = 100.0f / CASTS<float>(m_zpLOD.size());
		float previous = 0;
		m_zpLODBorder[0] = previous;

		for (size_t i = 0; i < m_zpLOD.size(); i++) {
			m_zpMain.AddPlacement(&m_zpLOD[i]);

			m_zpLOD[i].SetLoD(previous, previous + step);
			previous = previous + step;
			m_zpLODBorder[i + 1] = previous;
		}

		DEBUG_EXPRESSION(initViewModel(nullptr));	//TODO (JS) Problems because of double init?
	}

	virtual inline ~IViewModel()
	{}

	inline void initViewModel(IViewBuilding* vBuilding)
	{
		this->vBuilding = vBuilding;

//<<<<<<< HEAD
		float foundationWidth = vBuilding->getVMaster()->getPlayingField()->getFieldSize() * 0.2F;
		float foundationHeight = foundationWidth * 0.2f;
		m_zgFoundation.Init(CHVector(foundationWidth, foundationHeight, foundationWidth), &VMaterialLoader::materialFoundationPlayer[vBuilding->getLBuilding()->getPlayerId()]);
//=======
		if (vBuilding != nullptr) {
			foundationWidth = vBuilding->getVMaster()->getPlayingField()->getFieldSize() * 0.2;
			foundationHeight = foundationWidth * 0.2f;
			m_zgFoundation.Init(CHVector(foundationWidth, foundationHeight, foundationWidth), &VMaterialLoader::materialFoundationPlayer[vBuilding->getLBuilding()->getPlayerId()]);
		}
		else {
			m_zgFoundation.Init(CHVector(foundationWidth, foundationHeight, foundationWidth), &VMaterialLoader::materialFoundationPlayer[LPlayer::Local]);
		}
//>>>>>>> master
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
