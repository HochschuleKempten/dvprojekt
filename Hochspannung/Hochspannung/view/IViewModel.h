#pragma once

#include "VGeneral.h"
#include <array>
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


class IViewModel
{
	NON_COPYABLE(IViewModel);
	
protected:
	CPlacement m_zpMain;	//TODO (JS) make this private when m_zpLOD is used
	/** @brief Holds the different LOD levels for every model. m_zpLOD[0] is the nearest (much details) and m_zpLOD[2] is the furthest (less details) */
	std::array<CPlacement, 3> m_zpLOD;
	CGeoCube m_zgFoundation;
	float m_fFoundationHeight = 0;
	float m_fFoundationWidth = 0;

public:
	inline IViewModel()
	{
		m_zgFoundation.Init(CHVector(m_fFoundationWidth, m_fFoundationHeight, m_fFoundationWidth), &VMaterialLoader::m_zmConcrete);

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
