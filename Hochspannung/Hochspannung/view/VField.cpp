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

void VField::setHoverOn()
{
	m_zmNormal.SetColorAmbient(CColor(1.0, 0.0, 0.0));
}

void VField::setHoverOff()
{
	m_zmNormal.SetColorAmbient(CColor(0.0, 0.0, 0.0));
}

void VField::initField(const int rowIdx, const int colIdx)
{
	lField = vPlayingField->lPlayingField->getField(rowIdx, colIdx);

	static std::stringstream stream;	//Create only one object
	stream.str("");
	stream.clear();
	stream << VIdentifier::VPlayingField << ";" << rowIdx << ";" << colIdx;
	m_zp.SetName(stream.str().c_str());

	m_zmNormal = VMaterialLoader::fieldMaterials[VMaterialLoader::FieldPair(lField->getFieldType(), lField->getFieldLevel())];
	ASSERT(m_zmNormal.m_ptextureDiffuse != nullptr, "Could not load the material for the field " << lField->getFieldType());
	
	m_zg.Init(vPlayingField->size, &m_zmNormal);
	m_zp.AddGeo(&m_zg);

	m_zp.RotateZ(M_PI);
	m_zp.TranslateXDelta(CASTS<float>(colIdx * (vPlayingField->fieldSize * vPlayingField->fieldSize - 0.0)));
	m_zp.TranslateYDelta(CASTS<float>(rowIdx * (vPlayingField->fieldSize * vPlayingField->fieldSize - 0.0) * -1));
}

void VField::removeBuilding()
{
#ifdef _DEBUG
	bool erg = m_zp.SubPlacement(m_zViewBuilding->getPlacement());
	ASSERT(erg, "Unable to sub the placement");
#else
	m_zp.SubPlacement(m_zViewBuilding->getPlacement());
#endif

	m_zViewBuilding = nullptr;
}


NAMESPACE_VIEW_E
