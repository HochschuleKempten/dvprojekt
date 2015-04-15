#include "VPlayingField.h"
#include "IViewBuilding.h"
#include "VIdentifier.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


VPlayingField::~VPlayingField()
{
	//Sub the field itself
	int square = CASTS<int>(sqrt(m_zpPlacementHolders.size()));
	for (int holder = 0; holder < CASTS<int>(m_zpPlacementHolders.size()); holder++) {
		
		//Sub each field placement from the holders
		for (int rowIdx = (holder % square) * 5; rowIdx < ((holder % square) + 1) * 5; rowIdx++) {
			for (int colIdx = (holder / square) * 5; colIdx < ((holder / square + 1) * 5); colIdx++) {
				m_zpPlacementHolders[holder].SubPlacement(&vFields[rowIdx][colIdx].m_zp);
			}
		}

		//Sub the holder from the playing field placement
		m_zp.SubPlacement(&m_zpPlacementHolders[holder]);
	}

	//Now the sub of the field starts in the VField destructor
}

void VPlayingField::placeObject(const std::shared_ptr<IViewBuilding>& objPtr, const int x, const int y)
{
	vFields[x][y].m_zViewBuilding = objPtr;
	vFields[x][y].m_zp.AddPlacement(objPtr->getPlacement());
}

void VPlayingField::initPlayingField()
{
	m_zp.Fasten(); // direkt das oberste fasten????????

	int square = CASTS<int>(sqrt(m_zpPlacementHolders.size()));
	for (int holder = 0; holder < CASTS<int>(m_zpPlacementHolders.size()); holder++)
	{
		std::stringstream stream;
		stream << "holder = " << holder;
		m_zpPlacementHolders[holder].SetName(stream.str().c_str());
		m_zp.AddPlacement(&m_zpPlacementHolders[holder]);

		for (int rowIdx = (holder % square) * 5; rowIdx < ((holder % square) + 1) * 5; rowIdx++)
		{
			for (int colIdx = (holder / square) * 5 ; colIdx < ((holder /square + 1) * 5); colIdx++)
			{

				vFields[rowIdx][colIdx].initField(rowIdx, colIdx);
				m_zpPlacementHolders[holder].AddPlacement(&vFields[rowIdx][colIdx].m_zp);
			}
		}
	}

	float rows = CASTS<float>(vFields.getRows());
	m_zp.TranslateDelta(CASTS<float>(-fieldSize * rows), CASTS<float>(fieldSize * rows), CASTS<float>(-fieldSize * rows * 1.5));

	m_zp.SetName("Placement VPlayingField");
}

void VPlayingField::objectRemoved(const int x, const int y)
{
	vFields[x][y].removeBuilding();
}


NAMESPACE_VIEW_E
