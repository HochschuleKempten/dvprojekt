#pragma once
#include "IViewGUIContainer.h"
#include "VTab.h"

NAMESPACE_VIEW_B

class VRegister :
	public IViewGUIContainer
{
public:
	VRegister();
	VRegister(CFloatRect floatRect, CViewport* viewport, const float layer);
	VRegister(CFloatRect floatRect, CViewport* viewport, CMaterial* materialBackground, const float layer);
	~VRegister();

	void onNotify(const Event& events) override;
	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::basic_string<char>& sName, const float layer) override;
	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::basic_string<char>& sName, const float layer) override;

	void addTab(CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* background, const Event& events, const std::string& sName, const float layer);

	void SwitchToTab(const std::string& sName);
	VTab* getTab(const std::string& sName);

private:
	std::unordered_map<std::string, VTab*> m_tabs;
	void calcButtonSize();
};

NAMESPACE_VIEW_E
