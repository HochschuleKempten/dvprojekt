#pragma once

#include "IViewGUIContainer.h"
#include "IViewUIObserver.h"


//---------------------------------------------------
// Klasse: CGroup
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------
NAMESPACE_VIEW_B


	class VGroup:public IViewGUIContainer
	{
	public:
		VGroup(CViewport* viewport, CFloatRect floatRect);
		VGroup(CViewport* viewport, CFloatRect floatRect, CMaterial* materialbackground);
		VGroup();
		~VGroup();

		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::string& sName) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::string& sName) override;
		VButton* addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, std::string sName) override;
		VTextfield* addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const std::string& Placeholder, std::string sName) override;
		VText* addText(CFloatRect rect, CWritingFont* writingFont, std::string text, std::string sName) override;
		COverlay* addOverlay(CFloatRect rect, CMaterial* MaterialNormal, bool bChromaKeying, std::string sName) override;

		//void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction) override;
		//void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const std::string& Placeholder) override;
		//void addText(CFloatRect rect, CWritingFont* writingFont, std::string text)override;
		void onNotify(const Event&) override;
	};

	NAMESPACE_VIEW_E
