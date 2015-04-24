#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class IViewModel
{
	NON_COPYABLE(IViewModel);
	
protected:
	CPlacement m_zpMain;	//TODO (JS) make this private when m_zpLOD is used
	std::array<CPlacement, 3> m_zpLOD;

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

	virtual float getHeight() = 0;
	virtual float getWidth() = 0;

	inline CPlacement* getMainPlacement()
	{
		return &m_zpMain;
	}
};


NAMESPACE_VIEW_E
