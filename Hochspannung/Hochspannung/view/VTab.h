#pragma once
#include "IViewGUIContainer.h"
NAMESPACE_VIEW_B

class VTab :
	public IViewGUIContainer
{
public:
	VTab(CViewport* viewport, CFloatRect rect, const float layer);
	VTab(CViewport* viewport, CFloatRect rect, CMaterial* materialBackground, const float layer);
	~VTab();

	void onNotify(const Event& events) override;
	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::basic_string<char>& sName, const float layer) override;
	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::basic_string<char>& sName, const float layer) override;
};

NAMESPACE_VIEW_E
