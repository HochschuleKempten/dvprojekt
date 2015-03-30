#pragma once

#include "VMaster.h"
#include "../logic/IVPlayingField.h"
#include "../logic/LPlayingField.h"
#include "../logic/Array2D.h"

NAMESPACE_VIEW_B


class VPlayingField : public IVPlayingField, public CPlacement
{
private:
	CPlacement m_zpCentral;
	Array2D<CGeoCube> m_zg;
	Array2D<CPlacement> m_zp;
	CMaterial m_zm;

public:
	VPlayingField(IVMaster* master, LPlayingField* field)
		: IVPlayingField(master, field),
		  m_zg(field->getFieldLength(), field->getFieldLength()),
		  m_zp(field->getFieldLength(), field->getFieldLength())
	{}

	virtual ~VPlayingField()
	{}
	
	virtual void init();
};


NAMESPACE_VIEW_E
