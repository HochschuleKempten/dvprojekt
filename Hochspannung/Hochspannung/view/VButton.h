#pragma once

#include "IViewGUIObject.h"
//---------------------------------------------------
// CPEmitter: Button Klasse für GUI
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------
NAMESPACE_VIEW_B

	class VButton:public IViewGUIObject
	{
	public:

		VButton();
		VButton(CViewport* viewport, CFloatRect& rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewUIObserver::Event clickAction);
		~VButton();


		virtual void switchOn() override final;
		virtual void switchOff() override final;

		virtual void onMouseOver(void) override final;
		virtual void onMouseOut(void) override final;
		virtual void onMouseClickLeft(void) override final;
		virtual void onMouseClickRight(void) override final;

		virtual void setLayer(float layer) override;
		virtual void updateRectangle(CFloatRect rect) override;
		bool bGetHasHover();


		//Getter

		COverlay* getHoverOverlay();
		COverlay* getNormalOverlay();

		CFloatRect getRectangle() override;


		//ClickAction getAction();

	private:

		COverlay* m_zoNormal;
		COverlay* m_zoHover;

		bool m_bHasHover;

		IViewUIObserver::Event action;
	};

	NAMESPACE_VIEW_E
