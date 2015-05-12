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
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const string& sName) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const string& sName) override;
		void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, string sName) override;
		void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder, string sName) override;
		void addText(CFloatRect rect, CWritingFont* writingFont, string text, string sName) override;
		void addOverlay(CFloatRect rect, CMaterial* MaterialNormal, bool bChromaKeying, string sName) override;
		//void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction) override;
		//void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder) override;
		//void addText(CFloatRect rect, CWritingFont* writingFont, string text)override;
		void onNotify(Event) override;
	};

	NAMESPACE_VIEW_E
