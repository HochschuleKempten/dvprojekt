#pragma once

#include "IViewGUIContainer.h"

NAMESPACE_VIEW_B


class VDialog : public IViewGUIContainer
{
public:
	VDialog();
	VDialog(CViewport* viewport, CFloatRect floatRect, CMaterial* MaterialNormal,const std::string& sName, const float layer);
	VDialog(CViewport* viewport, CFloatRect floatRect, const std::string& sName, const float layer);

	void onNotify(const Event& events) override;


	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::basic_string<char>& sName, const float layer) override;
	void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::basic_string<char>& sName, const float layer) override;
};


NAMESPACE_VIEW_E
