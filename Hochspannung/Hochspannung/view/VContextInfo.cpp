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
	CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("RessourceInfo"))->updateText(m_infoValues["Ressource"]);
	CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("SellInfo"))->updateText(m_infoValues["SellPrice"]);
	m_vScreenIngame->switchInfo(VScreenIngame::INFOTYPE::FIELDINFO);

}

NAMESPACE_VIEW_E
