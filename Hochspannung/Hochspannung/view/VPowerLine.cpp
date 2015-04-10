#include "VPowerLine.h"
#include "VPlayingField.h"
#include "VIdentifier.h"

NAMESPACE_VIEW_B 


VPowerLine::VPowerLine(VMaster* vMaster, LPowerLine* lpowerLine)
	: IViewBuilding(vMaster, &m_zp), IVPowerLine(lpowerLine)
{
	m_zp.Init();
	m_zp.RotateX(M_PI / 2);
	m_zp.ScaleDelta(2.0);
	m_zp.TranslateZDelta(0.5);
	//m_zm.MakeTextureDiffuse("textures\\_original.jpg");
	//m_zg.Init(CHVector(1.5f, 2.6f, 0.8f), &m_zm);
	//m_zp.Init();
	//m_zp.AddGeo(&m_zg);
}

void VPowerLine::initPowerLine(const std::shared_ptr<IVPowerLine>& objPtr, const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VPowerLine);
}


NAMESPACE_VIEW_E
