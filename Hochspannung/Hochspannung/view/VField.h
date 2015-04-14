#pragma once

#include <memory>
#include "IViewBuilding.h"
#include <string>

class LField;

NAMESPACE_VIEW_B


class VPlayingField;

class VField
{
	friend class VPlayingField;

private:
	VPlayingField* vPlayingField = nullptr;
	LField* lField = nullptr;
	CPlacement m_zp;
	CGeoCube m_zg;
	CMaterial m_zm;
	std::shared_ptr<IViewBuilding> m_zViewBuilding = nullptr;

public:
	VField();
	~VField();

	void initField(const int rowIdx, const int colIdx);
	void removeBuilding();
};


NAMESPACE_VIEW_E
