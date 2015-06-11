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
	CColor colorAmbientOn;
	CColor colorAmbientOff;
	bool switchedState;

protected:
	void removeMaterial(CMaterial* material)
	{
		ASSERT(vBuilding != nullptr, "vBuilding is not initialized");

		vBuilding->getVMaster()->getVUi()->removeMaterialFromRoot(material);
	}

public:
	inline IViewModel()
		: colorAmbientOn(0.0f, 0.0f, 0.0f), colorAmbientOff(-0.2f, -0.2f, -0.2f)
	{
		const float step = 50.0f / CASTS<float>(m_zpLOD.size());
		const float lastStep = 999.0f;
		float previous = 0;
		m_zpLODBorder[0] = previous;
		
		size_t i = 0;
		for (; i < m_zpLOD.size() - 1; i++) {
			m_zpMain.AddPlacement(&m_zpLOD[i]);

			m_zpLOD[i].SetLoD(previous, previous + step);
			previous = previous + step;
			m_zpLODBorder[i + 1] = previous;
		}

		//The last one goes until "infinity"
		m_zpMain.AddPlacement(&m_zpLOD[i]);
		m_zpLOD[i].SetLoD(previous, lastStep);
		m_zpLODBorder[i + 1] = lastStep;

		initViewModel(nullptr);
	}

	virtual inline ~IViewModel()
	{}

	inline void initViewModel(IViewBuilding* vBuilding, const bool switchedOn = true)
	{
		this->vBuilding = vBuilding;
		this->switchedState = switchedOn;

		if (vBuilding != nullptr) {
			foundationWidth = vBuilding->getVMaster()->getVPlayingField()->getFieldSize() * 0.2f;
			foundationHeight = foundationWidth * 0.2f;
			m_zgFoundation.Init(CHVector(foundationWidth, foundationHeight, foundationWidth), &VMaterialLoader::materialFoundationPlayer[vBuilding->getLBuilding()->getPlayerId()]);
		}
		else {
			m_zgFoundation.Init(CHVector(foundationWidth, foundationHeight, foundationWidth), &VMaterialLoader::materialFoundationPlayer[LPlayer::Local | LPlayer::Remote]);
		}
	}

	virtual float getHeight() = 0;
	virtual float getWidth() = 0;

	virtual void switchOn()
	{}
	virtual void switchOff()
	{}

	inline CPlacement* getMainPlacement()
	{
		return &m_zpMain;
	}
};


NAMESPACE_VIEW_E
