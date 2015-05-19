#pragma once
#include "IViewGUIContainer.h"

NAMESPACE_VIEW_B

	class VGUIArea :
		public IViewGUIContainer
	{
	public:
		VGUIArea();

		VGUIArea(CViewport* viewport, CFloatRect floatRect);
		VGUIArea(CViewport* viewport, CFloatRect floatRect, CMaterial* materialbackground);

		~VGUIArea();

		void onNotify(const Event& events) override;

		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::string& sName) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::string& sName) override;
	};

	NAMESPACE_VIEW_E
