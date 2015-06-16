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
	VListView(CFloatRect floatRect, CViewport* viewport, const std::string& sName, const float layer);
	VListView(CFloatRect floatRect, CViewport* viewport, CMaterial* materialBackground, const std::string& sName, const float layer);

	void onNotify(const Event& evente) override;
	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::basic_string<char>& sName, const float layer) override;
	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::basic_string<char>& sName, const float layer) override;


	void setLayer(float layer) override;

	void addEntry(const std::string& sName, const float layer);
	void updateList(const std::unordered_map<std::string, Network::CGameObject>& hostList);
	void onNotifyExt(const Event& evente, const std::string& sName) override;

	IViewGUIObject* getSelectedItem();

private:

	std::vector<std::string> m_entries;

	void calcEntrySize();

	IViewGUIObject* m_selectedItem = nullptr;
};

NAMESPACE_VIEW_E
