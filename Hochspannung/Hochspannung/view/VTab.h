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

		void onNotify(Event events) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const string& sName) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const string& sName) override;
	};

	NAMESPACE_VIEW_E
