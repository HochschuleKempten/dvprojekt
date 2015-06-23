#pragma once
#include "IViewGUIObject.h"
#include "IViewSubject.h"

NAMESPACE_VIEW_B

class VText :
	public IViewGUIObject
{
public:
	enum TextMode
	{
		CENTERED,
		NONE
	};
	VText();
	VText(CViewport* viewport, CFloatRect rect, CWritingFont* writingFont, const std::string& text, const float layer, const TextMode& textmode = NONE);

	~VText();

	virtual void switchOn() override final;
	virtual void switchOff() override final;

	virtual void onMouseOver(void) override final;
	virtual void onMouseOut(void) override final;
	virtual void onMouseClickLeft(void) override final;
	virtual void onMouseClickRight(void) override final;

	void updateText(const std::string& text);
	virtual void setLayer(const float layer) override final;
	void updateRectangle(CFloatRect rect) override final;

	void centerText();

	CWritingFont* getWritingfont();

	std::string getText();

private:

	CWritingFont* m_writingFont;
	CWriting* m_writing;
	std::string m_text;
	int m_maxLength;
	TextMode m_textmode=NONE;
};

NAMESPACE_VIEW_E
