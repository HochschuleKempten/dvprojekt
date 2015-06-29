#include "VContextInfo.h"
#include "VUIHelper.h"

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

	for (std::pair<std::string, IViewGUIObject*> object : m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObjectList())
	{
		object.second->switchOff();
	}
	for (std::pair<std::string, COverlay*> overlay : m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlayMap())
	{
		overlay.second->SwitchOff();
	}

	if (m_infoValues.count("Population") > 0)
	{
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("PopulationInfo"))->updateText(m_infoValues.at("Population"));
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("PopulationInfo")->switchOn();
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlay("PopulationInfoIcon")->SwitchOn();
	}
	
	if (m_infoValues.count("Resource")>0)
	{
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("ResourceInfo"))->updateText(m_infoValues.at("Resource"));
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("ResourceInfo")->switchOn();
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlay("ResourceInfoIcon")->SwitchOn();
	}
	
	if (m_infoValues.count("Energy")>0)
	{
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("EnergyInfo"))->updateText(m_infoValues.at("Energy"));
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("EnergyInfo")->switchOn();
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlay("EnergyInfoIcon")->SwitchOn();
	}
	
	if (m_infoValues.count("SellPrice") > 0)
	{
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("SellPriceInfo"))->updateText(m_infoValues.at("SellPrice"));
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject("SellPriceInfo")->switchOn();
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlay("SellPriceInfoIcon")->SwitchOn();
	}
	

	//for (std::pair<std::string, IViewGUIObject*> object : m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObjectList())
	//{
	//	object.second->switchOff();
	//}
	//for (std::pair<std::string, COverlay*> overlay : m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlayMap())
	//{
	//	overlay.second->SwitchOff();
	//}
	//
	//float Distance = 0.02F;
	//float startPos = 0.61F ;
	//float InfoSize = 1.0F - startPos;
	//float maxYSize = 0.1F;

	//

	//int number = m_infoValues.size();
	//int i=0;
	//for (std::pair<std::string,std::string> field : m_infoValues)
	//{
	//	IViewGUIObject* tempObject = m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject(field.first + "Info");
	//	CFloatRect rectText = tempObject->getRectangle();

	//	rectText.SetXPos(0.1F);
	//	rectText.SetXSize(0.5F);
	//	 
	//	
	//	rectText.SetYSize(InfoSize / CASTS<float>(number));
	//	
	//	if (rectText.GetYSize() > maxYSize)
	//		rectText.SetYSize(maxYSize);
	//		
	//	rectText.SetYPos((rectText.GetYSize() + Distance )*CASTS<float>(i) +startPos);
	//	
	//	rectText = createRelativeRectangle(&m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getRectangle(), &rectText);
	//	
	//	VText text = *CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject(field.first + "Info"));
	//	//m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObjectList().emplace(field.first + "Info", new VText(m_vScreenIngame->m_viewport, rectText, text.getWritingfont(), text.getText(),text.getLayer()));
	//	m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObjectList().erase(field.first + "Info");
	//	m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->addText(rectText, text.getWritingfont(), text.getText(),text.getName(), text.getLayer());


	//	
	//	COverlay* tempIcon = m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlay(field.first + "InfoIcon");
	//	CFloatRect rectIcon;
	//	rectIcon.SetXPos(0.65F);
	//	rectIcon.SetXSize(0.25F);
	//	
	//	rectIcon.SetYSize(InfoSize / CASTS<float>(number));
	//	if (rectIcon.GetYSize() > maxYSize)
	//		rectIcon.SetYSize(maxYSize);
	//	
	//	rectIcon.SetYPos((rectIcon.GetYSize() + Distance)*CASTS<float>(i)  +startPos);
	//	
	//	rectIcon = createRelativeRectangle(&m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getRectangle(), &rectIcon);

	//	tempIcon->SetRect(rectIcon);

		/*COverlay* tempIcon = m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlay(field.first + "InfoIcon");
		CFloatRect rectIcon= tempIcon->GetRect();
		rectIcon.SetYSize((CASTS<float>(i)*InfoSize / CASTS<float>(number)) + startPos);

		if (rectIcon.GetYSize() > maxYSize)
			rectIcon.SetYSize(maxYSize);

		rectIcon.SetYPos(rectText.GetYSize()*CASTS<float>(i) +Distance + startPos);
		
		rectIcon = createRelativeRectangle(&m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getRectangle(), &rectIcon);
		
		tempIcon->SetRect(rectIcon);*/


		/*
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject(field.first + "Info"))->updateText(m_infoValues.at(field.first));
		CASTD<VText*>(m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getGuiObject(field.first + "Info"))->switchOn();
		m_vScreenIngame->getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->getOverlay(field.first + "InfoIcon")->SwitchOn();

		i++;*/
	/*}*/
}

NAMESPACE_VIEW_E
