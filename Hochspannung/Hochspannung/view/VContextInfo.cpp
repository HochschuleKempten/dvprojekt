#include "VContextInfo.h"

NAMESPACE_VIEW_B


VContextInfo::VContextInfo(VScreenIngame* vScreenIngame) :m_vScreenIngame(vScreenIngame)
{	
};


VContextInfo::~VContextInfo()
{
	m_infoValues.clear();
}

void VContextInfo::updateValue(const std::string& name, const std::string& value)
{
	m_infoValues[name] = value;
}

void VContextInfo::showContextInfo()
{
	m_vScreenIngame->switchInfo(VScreenIngame::INFOTYPE::FIELDINFO);

	if (m_infoValues.count("Population") > 0)
	{
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("PopulationInfo"))->updateText(m_infoValues.at("Population"));
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("PopulationInfo"))->switchOn();
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlay("PopulationInfoIcon")->SwitchOn();
	}
	else
	{
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("PopulationInfo"))->switchOff();
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlay("PopulationInfoIcon")->SwitchOff();
		
	}
	if (m_infoValues.count("Resource")>0)
	{
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("ResourceInfo"))->updateText(m_infoValues.at("Resource"));
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("ResourceInfo"))->switchOn();
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlay("ResourceInfoIcon")->SwitchOn();
	}
	else
	{
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("ResourceInfo"))->switchOff();
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlay("ResourceInfoIcon")->SwitchOff();
	}
	
	if (m_infoValues.count("SellPrice") > 0)
	{
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("SellInfo"))->updateText(m_infoValues.at("SellPrice"));
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("SellInfo"))->switchOn();
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlay("SellInfoIcon")->SwitchOn();
	}
	else
	{
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("SellInfo"))->switchOff();
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlay("SellInfoIcon")->SwitchOff();
	}


}

NAMESPACE_VIEW_E
