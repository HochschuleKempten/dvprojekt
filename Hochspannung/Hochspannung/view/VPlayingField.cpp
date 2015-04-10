#include "VPlayingField.h"
#include "IViewBuilding.h"

NAMESPACE_VIEW_B


void VPlayingField::placeObject(const std::shared_ptr<IViewBuilding>& objPtr, const int x, const int y)
{
	viewObjects[x][y] = objPtr;
	m_zpField[x][y].AddPlacement(objPtr->getPlacement());
}

void VPlayingField::initPlayingField()
{
	CHVector size(fieldSize, fieldSize, 0.5f);
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

void VPlayingField::objectRemoved(const int x, const int y)
{
	bool erg = m_zpField[x][y].SubPlacement(viewObjects[x][y]->getPlacement());
	ASSERT(erg, "Unable to sub the placement");
	viewObjects[x][y] = nullptr;
}


NAMESPACE_VIEW_E
