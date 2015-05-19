#pragma once
#include "IViewGUIContainer.h"
#include "VListEntry.h"

NAMESPACE_VIEW_B

class VListView :
	public IViewGUIContainer
{
public:
		VListView();
		~VListView();
	VListView(CFloatRect floatRect, CViewport* viewport);
	VListView(CFloatRect floatRect, CViewport* viewport, CMaterial* materialBackground);

	void onNotify(Event evente) override;
	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::string& sName) override;
	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::string& sName) override;


	VButton* addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, std::string sName) override;
	VTextfield* addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const std::string& Placeholder, std::string sName) override;
	VText* addText(CFloatRect rect, CWritingFont* writingFont, std::string text, std::string sName) override;
	COverlay* addOverlay(CFloatRect rect, CMaterial* MaterialNormal, bool bChromaKeying, std::string sName) override;
	void setLayer(float layer) override;
	
	void addEntry(CMaterial* MaterialEntryNormal, CMaterial* MaterialEntryHover,std::string sName);

	void onNotifyExt(Event evente, std::string sName) override;

	VListEntry* getSelectedItem();

private:
	std::map<std::string, VListEntry*> m_entries;
	std::map<std::string, VListEntry*>::iterator m_IterEntries;

	void calcEntrySize();

	VListEntry* m_selectedItem;
	
};

NAMESPACE_VIEW_E
