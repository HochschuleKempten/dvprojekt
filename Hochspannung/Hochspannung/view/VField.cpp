#include "VField.h"
#include "VPlayingField.h"
#include "VMaterialLoader.h"
#include "VIdentifier.h"
#include "../logic/LField.h"

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
	}
}

void VField::initField(const int rowIdx, const int colIdx)
{
	lField = vPlayingField->lPlayingField->getField(rowIdx, colIdx);

	std::stringstream stream;
	stream << VIdentifier::VPlayingField << ";" << rowIdx << ";" << colIdx;
	m_zp.SetName(stream.str().c_str());

	m_zm = VMaterialLoader::fieldMaterials[VMaterialLoader::FieldPair(lField->getFieldType(), lField->getFieldLevel())];
	ASSERT(m_zm.m_ptextureDiffuse != nullptr, "Could not load the material for the field");
	
	m_zg.Init(vPlayingField->size, &m_zm);
	m_zp.AddGeo(&m_zg);

	m_zp.TranslateX(colIdx * (vPlayingField->fieldSize * vPlayingField->fieldSize - 0.0));
	m_zp.TranslateYDelta(rowIdx * (vPlayingField->fieldSize * vPlayingField->fieldSize - 0.0) * -1);
}

void VField::removeBuilding()
{
	bool erg = m_zp.SubPlacement(m_zViewBuilding->getPlacement());
	ASSERT(erg, "Unable to sub the placement");
	m_zViewBuilding = nullptr;
}


NAMESPACE_VIEW_E