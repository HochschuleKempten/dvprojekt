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

		
		void onNotify(Event events) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const string& sName) override;
		void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const string& sName) override;

		void addTab(CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* background, Event events, const string sName);

		void SwitchToTab(string sName);
		VTab* getTab(string sName);

	private:
		map<string, VTab*> m_tabs;
		void calcButtonSize();
	};

	NAMESPACE_VIEW_E
