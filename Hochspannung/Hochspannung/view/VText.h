#pragma once
#include "IViewGUIObject.h"
#include "IViewSubject.h"

NAMESPACE_VIEW_B

	class VText :
		public IViewGUIObject
	{
	public:
		VText();
		VText(CViewport* viewport, CFloatRect rect, CWritingFont* writingFont, std::string text);

		~VText();

		virtual void switchOn() override final;
		virtual void switchOff() override final;

		virtual void onMouseOver(void) override final;
		virtual void onMouseOut(void) override final;
		virtual void onMouseClickLeft(void) override final;
		virtual void onMouseClickRight(void) override final;

		void updateText(std::string text);
		virtual void setLayer(float layer) override final;
		void updateRectangle(CFloatRect rect) override final;


	private:

		CWritingFont* m_writingFont;
		CWriting* m_writing;
		std::string m_text;
	};

	NAMESPACE_VIEW_E
