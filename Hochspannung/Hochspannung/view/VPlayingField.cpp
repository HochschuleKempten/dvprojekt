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
	//m_zm.MakeTextureDiffuse("textures\\_original.jpg");
	CHVector size(fieldSize, fieldSize, 0.5);
	std::stringstream stream;
	std::string textureDiffuse;
	std::string textureBump;

	for (int rowIdx = 0; rowIdx < m_zgField.getRows(); rowIdx++) {
		for (int colIdx = 0; colIdx < m_zgField.getRows(); colIdx++) {
			stream.clear();
			stream.str("");

			stream << getClassName(this) << ";" << rowIdx << ";" << colIdx;

			textureDiffuse = std::string("textures/LuftaufnahmeDiffuse") + std::to_string(rowIdx) + std::string("_") + std::to_string(colIdx) + std::string(".jpg");
			textureBump = std::string("textures/LuftaufnahmeBump") + std::to_string(rowIdx) + std::string("_") + std::to_string(colIdx) + std::string(".jpg");
			m_zmMaterials[rowIdx][colIdx].MakeTextureDiffuse(const_cast<char*>(textureDiffuse.c_str()));
			m_zmMaterials[rowIdx][colIdx].MakeTextureBump(const_cast<char*>(textureBump.c_str()));
			//m_zgField[rowIdx][colIdx].Init(size, &m_zm);
			m_zgField[rowIdx][colIdx].Init(size, &m_zmMaterials[rowIdx][colIdx]);
			m_zgField[rowIdx][colIdx].SetName(stream.str().c_str());
			m_zpField[rowIdx][colIdx].AddGeo(&m_zgField[rowIdx][colIdx]);
			m_zpField[rowIdx][colIdx].SetName(stream.str().c_str());
			m_zp.AddPlacement(&m_zpField[rowIdx][colIdx]);

			m_zpField[rowIdx][colIdx].TranslateX(colIdx * (fieldSize * fieldSize - 0.0));
			m_zpField[rowIdx][colIdx].TranslateYDelta(rowIdx * (fieldSize * fieldSize - 0.0) * -1);
		}
	}

	float rows = m_zgField.getRows();
	m_zp.TranslateDelta(-fieldSize * rows, fieldSize * rows, -fieldSize * rows * 1.5);
	m_zp.SetFrustumCullingOff();//TODO (V) remove this after bugfix

	vMaster->addScenegraph(getClassName(this), this);
}


NAMESPACE_VIEW_E
