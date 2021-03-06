#pragma once
#include "IViewGUIObject.h"

NAMESPACE_VIEW_B

class VTextfield :
	public IViewGUIObject
{
public:
	VTextfield();

	VTextfield(CViewport* viewport, CFloatRect& rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int MaxChars, const std::string& Placeholder, const float layer);
	~VTextfield();

	virtual void checkEvent(CDeviceCursor* cursor, CDeviceKeyboard* keyboard) override;

	virtual void switchOn() override final;


	virtual void switchOff() override final;
	virtual void onMouseOver(void) override final;
	virtual void onMouseOut(void) override final;
	virtual void onMouseClickLeft(void) override final;
	virtual void onMouseClickRight(void) override final;

	void AddChar(const char character);
	void deleteChar();
	bool isActive();

	void setLayer(const float layer) override;
	void updateRectangle(CFloatRect rect) override;

	std::string getValue();

private:
	COverlay* m_zoNormal;
	COverlay* m_zoActive;
	COverlay* m_zoHover;

	CWritingFont* m_writingfont;

	CWriting* m_writing;

	bool m_bIsActive = false;
	std::string m_sInputtext;
	bool pressedBefore = false;
	unsigned int m_iMaxChars;
	std::string m_sPlaceholder;
private:
	void setActive(const bool wert);
};

NAMESPACE_VIEW_E
