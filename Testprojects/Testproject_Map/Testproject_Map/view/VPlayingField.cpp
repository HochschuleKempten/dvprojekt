#include "VPlayingField.h"
#include "../logic/LUtility.h"
#include "IViewBuilding.h"

NAMESPACE_VIEW_B


void VPlayingField::placeObject(IViewBuilding* viewObject, const int x, const int y)
{
	viewObjects[x][y] = viewObject;
	m_zpField[x][y].AddPlacement(viewObject->getPlacement());
}

void VPlayingField::initPlayingField()
{
	m_zm.MakeTextureDiffuse("textures\\_original.jpg");
	CHVector size(fieldSize, fieldSize, 0.5);
	std::stringstream stream;

	for (int i = 0; i < m_zgField.getRows(); i++) {
		for (int j = 0; j < m_zgField.getRows(); j++) {
			stream.clear();
			stream.str("");

			stream << getClassName(this) << ";" << i << ";" << j;

			m_zgField[i][j].Init(size, &m_zm);
			m_zgField[i][j].SetName(stream.str().c_str());
			m_zpField[i][j].AddGeo(&m_zgField[i][j]);
			m_zpField[i][j].SetName(stream.str().c_str());
			m_zp.AddPlacement(&m_zpField[i][j]);

			m_zpField[i][j].TranslateX(i * (fieldSize * fieldSize + 0.1));
			m_zpField[i][j].TranslateYDelta(j * (fieldSize * fieldSize + 0.1));
		}
	}

	float rows = m_zgField.getRows();
	m_zp.TranslateDelta(-fieldSize * rows, -fieldSize * rows, -fieldSize * rows * 1.5);
	m_zp.SetFrustumCullingOff();//TODO (V) remove this after bugfix

	vMaster->addScenegraph(getClassName(this), this);
}


NAMESPACE_VIEW_E
