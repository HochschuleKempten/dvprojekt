#pragma once

#include "VGeneral.h"
#include "IViewModel.h"

NAMESPACE_VIEW_B


class VModelMountains : public IViewModel
{
private:

	// Placements -------------------------------------------------------------------------

	CPlacement m_zpBerg;

	// Gebirge
	CPlacement m_zpGebirge;
	CPlacement m_zpGebirge1;
	CPlacement m_zpGebirge2;
	CPlacement m_zpGebirge3;
	CPlacement m_zpBerg1;
	CPlacement m_zpBerg2;
	CPlacement m_zpBerg3;
	CPlacement m_zpBerg4;
	CPlacement m_zpBerg5;
	CPlacement m_zpBerg6;
	CPlacement m_zpBerg7;
	CPlacement m_zpBerg8;

	//Geo-Objects --------------------------------------------------------------------------
	CGeoCone m_zgBerg;
	
public:
	VModelMountains();
	virtual ~VModelMountains() override;

	virtual void init() override;

	virtual float getHeight() override
	{
		return 4.5f;
	}
	virtual float getWidth() override
	{
		return 0.0f;
	}
};


NAMESPACE_VIEW_E
