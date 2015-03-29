#pragma once

#include "VMaster.h"
#include "../logic/IVPlayingField.h"
#include "../logic/LPlayingField.h"

NAMESPACE_VIEW_B


class VPlayingField : public IVPlayingField, public CPlacement
{
private:
	//VMaster m_vMaster;
	CPlacement m_zpCentral;
	CGeoCube* m_zg;
	CPlacement* m_zp;
	CMaterial m_zm;
	int arrLength;

public:
	VPlayingField(IVMaster* master, LPlayingField* field)
		: IVPlayingField(master, field)
	{	
		arrLength = field->getFieldLength();
		m_zg = new CGeoCube[arrLength*arrLength];
		m_zp = new CPlacement[arrLength*arrLength];
	}

	virtual ~VPlayingField()
	{
		delete[] m_zg;
		delete[] m_zp;
	}
	
	virtual void init();

};


NAMESPACE_VIEW_E
