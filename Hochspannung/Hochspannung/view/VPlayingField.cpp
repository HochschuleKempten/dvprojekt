#include "VPlayingField.h"
#include "IViewBuilding.h"
#include "VIdentifier.h"

NAMESPACE_VIEW_B


VPlayingField::~VPlayingField()
{
	//First sub everything from the field
	for (int rowIdx = 0; rowIdx < m_zpField.getRows(); rowIdx++) {
		for (int colIdx = 0; colIdx < m_zpField.getRows(); colIdx++) {
			//Sub field geo
			m_zpField[rowIdx][colIdx].SubGeo(&m_zgField[rowIdx][colIdx]);

			//Sub view object placement if it exists
			if (viewObjects[rowIdx][colIdx] != nullptr) {
				m_zpField[rowIdx][colIdx].SubPlacement(viewObjects[rowIdx][colIdx]->getPlacement());
			}
		}
	}

	//Now sub the field itself
	int square = sqrt(m_zpPlacementHolders.size());
	for (int holder = 0; holder < static_cast<int>(m_zpPlacementHolders.size()); holder++) {
		
		//Sub each field placement from the holders
		for (int rowIdx = (holder % square) * 5; rowIdx < ((holder % square) + 1) * 5; rowIdx++) {
			for (int colIdx = (holder / square) * 5; colIdx < ((holder / square + 1) * 5); colIdx++) {
				m_zpPlacementHolders[holder].SubPlacement(&m_zpField[rowIdx][colIdx]);
			}
		}

		//Sub the holder from the playing field placement
		m_zp.SubPlacement(&m_zpPlacementHolders[holder]);
	}
}

void VPlayingField::placeObject(const std::shared_ptr<IViewBuilding>& objPtr, const int x, const int y)
{
	viewObjects[x][y] = objPtr;
	m_zpField[x][y].AddPlacement(objPtr->getPlacement());
}

void VPlayingField::initPlayingField()
{
	m_zp.Fasten(); // direkt das oberste fasten????????
	CHVector size(fieldSize, fieldSize, 0.5f);
	std::stringstream stream;
	std::string textureDiffuse;
	std::string textureBump;

	int square = sqrt(m_zpPlacementHolders.size());
	
	for (int holder = 0; holder < static_cast<int>(m_zpPlacementHolders.size()); holder++)
	{
		m_zp.AddPlacement(&m_zpPlacementHolders[holder]);

		for (int rowIdx = (holder % square) * 5; rowIdx < ((holder % square) + 1) * 5; rowIdx++)
		{
			for (int colIdx = (holder / square) * 5 ; colIdx < ((holder /square + 1) * 5); colIdx++)
			{
				stream.clear();
				stream.str("");

				stream << VIdentifier::VPlayingField << ";" << rowIdx << ";" << colIdx;

				textureDiffuse = std::string("textures/LuftaufnahmeDiffuse") + std::to_string(rowIdx) + std::string("_") + std::to_string(colIdx) + std::string(".jpg");
				textureBump = std::string("textures/LuftaufnahmeBump") + std::to_string(rowIdx) + std::string("_") + std::to_string(colIdx) + std::string(".jpg");
				m_zmMaterials[rowIdx][colIdx].MakeTextureDiffuse(const_cast<char*>(textureDiffuse.c_str()));
				m_zmMaterials[rowIdx][colIdx].MakeTextureBump(const_cast<char*>(textureBump.c_str()));
				m_zgField[rowIdx][colIdx].Init(size, &m_zmMaterials[rowIdx][colIdx]);
				m_zgField[rowIdx][colIdx].SetName(stream.str().c_str());
				m_zpField[rowIdx][colIdx].AddGeo(&m_zgField[rowIdx][colIdx]);
				m_zpField[rowIdx][colIdx].SetName(stream.str().c_str());

				m_zpPlacementHolders[holder].AddPlacement(&m_zpField[rowIdx][colIdx]);
				//int test = colIdx * (fieldSize * fieldSize - 0.0);
				//int ttest = rowIdx * (fieldSize * fieldSize - 0.0) * -1;

				m_zpField[rowIdx][colIdx].TranslateX(colIdx * (fieldSize * fieldSize - 0.0));
				m_zpField[rowIdx][colIdx].TranslateYDelta(rowIdx * (fieldSize * fieldSize - 0.0) * -1);

			

				DEBUG_OUTPUT("Placements: " << holder << rowIdx << colIdx);
/*
				DEBUG_OUTPUT("X Pos: " << test);
				DEBUG_OUTPUT("Y Pos: " << ttest);
			*/

			}
		}
	}

	float rows = m_zgField.getRows();
	m_zp.TranslateDelta(-fieldSize * rows, fieldSize * rows, -fieldSize * rows * 1.5);
	m_zp.SetFrustumCullingOff();//TODO (V) remove this after bugfix

	vMaster->setVPlayingField(this);
}

void VPlayingField::objectRemoved(const int x, const int y)
{
	bool erg = m_zpField[x][y].SubPlacement(viewObjects[x][y]->getPlacement());
	ASSERT(erg, "Unable to sub the placement");
	viewObjects[x][y] = nullptr;
}


NAMESPACE_VIEW_E
