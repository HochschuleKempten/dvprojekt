#pragma once
#include "IViewGUIContainer.h"
NAMESPACE_VIEW_B

	class VTab :
		public IViewGUIContainer
	{
	public:
		VTab(CViewport* viewport, CFloatRect rect);
		VTab(CViewport* viewport, CFloatRect rect, CMaterial* materialBackground);
		~VTab();

		void onNotify(const Event& events) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::string& sName) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::string& sName) override;
	};

	NAMESPACE_VIEW_E
