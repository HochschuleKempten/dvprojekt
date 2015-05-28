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

		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::basic_string<char>& sName, const float layer) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::basic_string<char>& sName, const float layer) override;
		VButton* addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, const Event& clickAction, const std::basic_string<char>& sName, const float layer) override;
		VTextfield* addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int MaxChars, const std::basic_string<char>& Placeholder, const std::basic_string<char>& sName, const float layer) override;
		VText* addText(CFloatRect rect, CWritingFont* writingFont, const std::basic_string<char>& text, const std::basic_string<char>& sName, const float layer) override;
		COverlay* addOverlay(CFloatRect rect, CMaterial* MaterialNormal, const std::basic_string<char>& sName, const float layer) override;

		void onNotify(const Event&) override;
	};

	NAMESPACE_VIEW_E
