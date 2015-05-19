#pragma once

#include "IViewGUIContainer.h"

NAMESPACE_VIEW_B


	class VDialog : public IViewGUIContainer
	{
	public:
		VDialog();
		VDialog(CViewport* viewport, CFloatRect floatRect, CMaterial* MaterialNormal);
		VDialog(CViewport* viewport, CFloatRect floatRect);

		void onNotify(const Event& events) override;


		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::string& sName) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::string& sName) override;
	
	};


	NAMESPACE_VIEW_E
