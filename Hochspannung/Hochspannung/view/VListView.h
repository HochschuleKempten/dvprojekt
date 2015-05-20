#pragma once
#include "IViewGUIContainer.h"
#include "VListEntry.h"
#include "../network/GameObject.h"

NAMESPACE_VIEW_B

class VListView :
	public IViewGUIContainer
{
public:
		VListView();
		~VListView();
	VListView(CFloatRect floatRect, CViewport* viewport);
	VListView(CFloatRect floatRect, CViewport* viewport, CMaterial* materialBackground);

	void onNotify(const Event& evente) override;
	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::string& sName) override;
	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::string& sName) override;


	VButton* addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, const Event& clickAction, const std::string& sName) override;
	VTextfield* addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int MaxChars, const std::string& Placeholder, const std::string& sName) override;
	VText* addText(CFloatRect rect, CWritingFont* writingFont, const std::string& text, const std::string& sName) override;
	COverlay* addOverlay(CFloatRect rect, CMaterial* MaterialNormal, const std::string& sName) override;
	void setLayer(float layer) override;
	
	void addEntry(const std::string& sName);
	void updateList(const std::vector <Network::CGameObject>& hostList);
	void onNotifyExt(const Event& evente, const std::string& sName) override;

	IViewGUIObject* getSelectedItem();

private:

	std::vector<std::string> m_entries;

	void calcEntrySize();

	IViewGUIObject* m_selectedItem;
	
};

NAMESPACE_VIEW_E
