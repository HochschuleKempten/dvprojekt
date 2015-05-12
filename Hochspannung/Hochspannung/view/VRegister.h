#pragma once
#include "IViewGUIContainer.h"
#include "VTab.h"

NAMESPACE_VIEW_B

	class VRegister :
		public IViewGUIContainer
	{
	public:
		VRegister();
		VRegister(CFloatRect floatRect, CViewport* viewport);
		VRegister(CFloatRect floatRect, CViewport* viewport, CMaterial* materialBackground);
		~VRegister();

		void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, std::string sName) override;
		void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const std::string& Placeholder, std::string sName) override;
		void addText(CFloatRect rect, CWritingFont* writingFont, std::string text, std::string sName) override;
		void addOverlay(CFloatRect rect, CMaterial* MaterialNormal, bool bChromaKeying, std::string sName) override;

		void onNotify(Event events) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::string& sName) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::string& sName) override;

		void addTab(CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* background, Event events, const std::string sName);

		void SwitchToTab(std::string sName);
		VTab* getTab(std::string sName);

	private:
		std::map<std::string, VTab*> m_tabs;
		void calcButtonSize();
	};

	NAMESPACE_VIEW_E
