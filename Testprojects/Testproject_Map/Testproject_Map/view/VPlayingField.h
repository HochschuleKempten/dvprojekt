#pragma once

#include "VMaster.h"
#include "../logic/IVPlayingField.h"

NAMESPACE_VIEW_B


class VPlayingField : public IVPlayingField, public CPlacement
{
private:
	static const int width = 2;
	static const int height = 2;

	//VMaster m_vMaster;
	CPlacement m_zpCentral;
	CGeoCube m_zg[width][height];
	CPlacement m_zp[width][height];
	CMaterial m_zm;

public:
	VPlayingField(IVMaster* master, LPlayingField* field)
		: IVPlayingField(master, field)
	{}
	virtual ~VPlayingField()
	{}
	
	virtual void init();

};


NAMESPACE_VIEW_E
