#include "VPlayingField.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


VPlayingField::VPlayingField(VMaster* vMaster, LPlayingField* lPlayingField)
	: IViewObject(vMaster, &m_zp),
      IVPlayingField(lPlayingField),
	  m_zpPlacementHolders(lPlayingField->getFieldLength()*lPlayingField->getFieldLength() / 25),
	  vFields(lPlayingField->getFieldLength(), lPlayingField->getFieldLength(), [this] (VField& vField)
	  {
		  vField.vPlayingField = this;
	  })
{}

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

void VPlayingField::hoverField(const int x, const int y)
{
	static std::pair<int, int> previousHover(x, y);

	vFields[previousHover.first][previousHover.second].setHoverOff();
	vFields[x][y].setHoverOn();

	previousHover.first = x;
	previousHover.second = y;
}

void VPlayingField::initPlayingField(const std::shared_ptr<IVPlayingField>& objPtr)
{
	vMaster->setVPlayingField(dynamic_pointer_cast<VPlayingField>(objPtr));
}

void VPlayingField::buildPlayingField()
{
	int square = CASTS<int>(sqrt(m_zpPlacementHolders.size()));
	for (int holder = 0; holder < CASTS<int>(m_zpPlacementHolders.size()); holder++) {
		DEBUG_EXPRESSION(std::string name = std::string("#holder = ") + std::to_string(holder));
		DEBUG_EXPRESSION(m_zpPlacementHolders[holder].SetName(name.c_str()));
		
		m_zp.AddPlacement(&m_zpPlacementHolders[holder]);

		for (int rowIdx = (holder % square) * 5; rowIdx < ((holder % square) + 1) * 5; rowIdx++) {
			for (int colIdx = (holder / square) * 5; colIdx < ((holder / square + 1) * 5); colIdx++) {

				vFields[rowIdx][colIdx].initField(rowIdx, colIdx);
				m_zpPlacementHolders[holder].AddPlacement(&vFields[rowIdx][colIdx].m_zp);
				m_zpPlacementHolders[holder].Fasten();
				m_zpPlacementHolders[holder].SetFrustumCullingOn();
			}
		}
	}

	//for (int rowIdx = 0; rowIdx < lPlayingField->getFieldLength(); rowIdx++) {
	//	for (int colIdx = 0; colIdx < lPlayingField->getFieldLength(); colIdx++) {
	//		vFields[rowIdx][colIdx].initField(rowIdx, colIdx);
	//		m_zp.AddPlacement(&vFields[rowIdx][colIdx].m_zp);
	//		//m_zpPlacementHolders[holder].AddPlacement(&vFields[rowIdx][colIdx].m_zp);
	//		//m_zpPlacementHolders[holder].Fasten();
	//		//m_zpPlacementHolders[holder].SetFrustumCullingOn();
	//	}
	//}

	float rows = CASTS<float>(vFields.getRows());
	m_zp.TranslateDelta(CASTS<float>(-fieldSize * lPlayingField->getCityPosition().first), CASTS<float>(fieldSize * lPlayingField->getCityPosition().second), CASTS<float>(fieldSize * rows * 0.5));
     
	//m_zp.SetFrustumCullingOn();
	//m_zp.Fasten();

	DEBUG_EXPRESSION(m_zp.SetName("#Placement VPlayingField"));

#ifdef _DEBUG
	for (int rowIdx = 0; rowIdx < lPlayingField->getFieldLength(); rowIdx++) {
		for (int colIdx = 0; colIdx < lPlayingField->getFieldLength(); colIdx++) {
			ASSERT(vFields[rowIdx][colIdx].initDone, "Not every field is initialized");
		}
	}
#endif
}

void VPlayingField::objectRemoved(const int x, const int y)
{
	vFields[x][y].removeBuilding();
}

void VPlayingField::messageBuildingFailed(const std::string& message)
{
	DEBUG_OUTPUT("BuildMessage: " << message);
}


NAMESPACE_VIEW_E
