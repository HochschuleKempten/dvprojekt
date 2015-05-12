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

		void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, std::string sName) override;
		void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const std::string& Placeholder, std::string sName) override;
		void addText(CFloatRect rect, CWritingFont* writingFont, std::string text, std::string sName) override;
		void addOverlay(CFloatRect rect, CMaterial* MaterialNormal, bool bChromaKeying, std::string sName) override;

		void onNotify(Event events) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::string& sName) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::string& sName) override;
	};

	NAMESPACE_VIEW_E
