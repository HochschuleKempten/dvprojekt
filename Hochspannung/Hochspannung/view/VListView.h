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
	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const string& sName) override;
	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const string& sName) override;


	void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, string sName) override;
	void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder, string sName) override;
	void addText(CFloatRect rect, CWritingFont* writingFont, string text, string sName) override;
	void addOverlay(CFloatRect rect, CMaterial* MaterialNormal, bool bChromaKeying, string sName) override;
	void setLayer(float layer) override;
	
	void addEntry(CMaterial* MaterialEntryNormal, CMaterial* MaterialEntryHover,string sName);

	void onNotifyExt(Event evente, string sName) override;

	VListEntry* getSelectedItem();

private:
	map<string, VListEntry*> m_entries;
	map<string, VListEntry*>::iterator m_IterEntries;

	void calcEntrySize();

	VListEntry* m_selectedItem;
	
};

NAMESPACE_VIEW_E
