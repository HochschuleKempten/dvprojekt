#pragma once
#include "IViewGUIContainer.h"

NAMESPACE_VIEW_B

class VGUIArea :
	public IViewGUIContainer
{
public:
	VGUIArea();

	VGUIArea(CViewport* viewport, CFloatRect floatRect, const float layer);
	VGUIArea(CViewport* viewport, CFloatRect floatRect, CMaterial* materialbackground, const float layer);

	~VGUIArea();

	void onNotify(const Event& events) override;

	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::basic_string<char>& sName, const float layer) override;
	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::basic_string<char>& sName, const float layer) override;
};

NAMESPACE_VIEW_E
