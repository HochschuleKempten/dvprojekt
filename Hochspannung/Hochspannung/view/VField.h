#pragma once

#include "IViewBuilding.h"

NAMESPACE_VIEW_B


class LField;
class VPlayingField;

class VField
{
	friend class VPlayingField;

private:
	VPlayingField* vPlayingField = nullptr;
	LField* lField = nullptr;
	CPlacement m_zp;
	CGeoCube m_zg;//TODO (JS) quads
	CMaterial m_zmNormal;
	std::shared_ptr<IViewBuilding> m_zViewBuilding = nullptr;
	DEBUG_EXPRESSION(bool initDone = false);

public:
	VField();
	~VField();

	void setHoverOn();
	void setHoverOff();

	void initField(const int rowIdx, const int colIdx);
	void removeBuilding();
};


NAMESPACE_VIEW_E
