#pragma once
#include "IViewGUIObject.h"
#include "IViewSubject.h"

NAMESPACE_VIEW_B
class VText :
	public IViewGUIObject
{
public:
	VText();
	VText(CViewport* viewport, CFloatRect rect, CWritingFont* writingFont,string text);

	~VText();
	
	virtual void switchOn() override final;
	virtual void switchOff() override final;

	virtual void onMouseOver(void) override final;
	virtual void onMouseOut(void) override final;
	virtual void onMouseClickLeft(void) override final;
	virtual void onMouseClickRight(void) override final;

	void updateText(string text);

private:

	CWritingFont * m_writingFont;
	CWriting* m_writing;
	string m_text;

};

NAMESPACE_VIEW_E
