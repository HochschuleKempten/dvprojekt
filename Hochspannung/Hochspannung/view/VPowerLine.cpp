#include "VPowerLine.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B 


VPowerLine::VPowerLine(VMaster* vMaster, LPowerLine* lpowerLine)
	: IViewBuilding(vMaster, &m_zp), IVPowerLine(lpowerLine)
{}

VPowerLine::~VPowerLine()
{}

void VPowerLine::initPowerLine(const std::shared_ptr<IVPowerLine>& objPtr, const int x, const int y, const int orientation)
{
	m_zg.Init(0.2, 0.2, 1.0, &VMaterialLoader::materialCoalPowerPlant);
	m_zp.AddGeo(&m_zg);
	m_zp.RotateX(CASTS<float>(M_PI / 2.0f));
	m_zp.TranslateZDelta(0.5);

	//switch (orientation) {
	//	case LPowerLine::NORTH | LPowerLine::SOUTH:
	//		m_zp.Init(VModelPowerLine::STRAIGHT, VModelPowerLine::NORTH);
	//		break;

	//	case LPowerLine::EAST | LPowerLine::WEST:
	//		m_zp.Init(VModelPowerLine::STRAIGHT, VModelPowerLine::EAST);
	//		break;

	//	case LPowerLine::NORTH | LPowerLine::EAST:
	//		m_zp.Init(VModelPowerLine::ANGLE, VModelPowerLine::EAST);
	//		break;

	//	case LPowerLine::SOUTH | LPowerLine::EAST:
	//		m_zp.Init(VModelPowerLine::ANGLE, VModelPowerLine::SOUTH);
	//		break;

	//	case LPowerLine::SOUTH | LPowerLine::WEST:
	//		m_zp.Init(VModelPowerLine::ANGLE, VModelPowerLine::WEST);
	//		break;

	//	case LPowerLine::NORTH | LPowerLine::WEST:
	//		m_zp.Init(VModelPowerLine::ANGLE, VModelPowerLine::NORTH);
	//		break;

	//	case LPowerLine::NORTH | LPowerLine::EAST | LPowerLine::SOUTH | LPowerLine::WEST:
	//		m_zp.Init(VModelPowerLine::CROSS);
	//		break;

	//	default:
	//		ASSERT(false, "Unchecked switch case");
	//		break;
	//}

	//m_zp.RotateX(CASTS<float>(M_PI / 2.0f));
	//m_zp.ScaleDelta(2.0f);
	//m_zp.TranslateZDelta(m_zp.getHeight() / 2.0f);

	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VPowerLine);
}


NAMESPACE_VIEW_E
