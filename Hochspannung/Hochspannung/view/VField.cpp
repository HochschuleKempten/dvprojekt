#include "VField.h"
#include "VPlayingField.h"
#include "VMaterialLoader.h"
#include "VIdentifier.h"
#include "../logic/LField.h"
#include "VMountains.h"

NAMESPACE_VIEW_B


VField::VField()
{}

VField::~VField()
{
	//Sub field geo
	m_zp.SubGeo(&m_zg);

	//Sub view object placement if it exists
	if (m_zViewBuilding != nullptr) {
		m_zp.SubPlacement(m_zViewBuilding->getPlacement());

		//Sub second placement, if it exists
		if (m_zViewBuilding->getPlacementSecond() != nullptr)
		{
			m_zp.SubPlacement(m_zViewBuilding->getPlacementSecond());
		}
	}
}

void VField::setHoverOn()
{
	//The current player is always the local player and uses the same color
	m_zmNormal.SetColorAmbient(VMaterialLoader::colorPlayers[LPlayer::Local]);
}

void VField::setHoverOff()
{
	m_zmNormal.SetColorAmbient(CColor(0.0, 0.0, 0.0));
}

void VField::initField(const int rowIdx, const int colIdx)
{
	ASSERT(!initDone, "VField << " << rowIdx << ", " << colIdx << " is initalized twice");

	lField = vPlayingField->lPlayingField->getField(rowIdx, colIdx);

	std::string name = std::to_string(VIdentifier::VPlayingField) + ";" + std::to_string(rowIdx) + ";" + std::to_string(colIdx);
	m_zp.SetName(name.c_str());

	//Material needs to be copied so that hover is working
	m_zmNormal = VMaterialLoader::fieldMaterials[VMaterialLoader::FieldPair(lField->getFieldType(), lField->getFieldLevel())];
	ASSERT(m_zmNormal.m_ptextureDiffuse != nullptr, "Could not load the material for the field " << lField->getFieldType());
	
	m_zg.Init(vPlayingField->fieldSize, vPlayingField->fieldSize, &m_zmNormal);
	m_zg.SetName(name.c_str());
	m_zp.AddGeo(&m_zg);

	m_zp.TranslateX(CASTS<float>(colIdx * (vPlayingField->fieldSize * vPlayingField->fieldSize - 0.0)));
	m_zp.TranslateYDelta(CASTS<float>(rowIdx * (vPlayingField->fieldSize * vPlayingField->fieldSize - 0.0) * -1));

	if (lField->getFieldType() == LField::MOUNTAIN)
	{
		m_zViewBuilding = std::dynamic_pointer_cast<IViewBuilding>(std::make_shared<VMountains>(vPlayingField->vMaster, rowIdx, colIdx));
	}

	DEBUG_EXPRESSION(initDone = true);
}

void VField::removeBuilding()
{
#ifdef _DEBUG
	bool erg = m_zp.SubPlacement(m_zViewBuilding->getPlacement());
	if (m_zViewBuilding->getPlacementSecond() != nullptr)
	{
		bool ergOff = m_zp.SubPlacement(m_zViewBuilding->getPlacementSecond());
		ASSERT(ergOff, "Unable to sub the placement");
	}
	ASSERT(erg, "Unable to sub the placement");
#else
	m_zp.SubPlacement(m_zViewBuilding->getPlacement());
	if (m_zViewBuilding->getPlacementSecond() != nullptr)
	{
		m_zp.SubPlacement(m_zViewBuilding->getPlacementSecond());
	}
#endif

	m_zViewBuilding = nullptr;
}


NAMESPACE_VIEW_E
