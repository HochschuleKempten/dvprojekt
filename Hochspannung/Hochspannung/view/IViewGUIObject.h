#pragma once
//TODO (pb)
#include "IViewUIObserver.h"
#include "IViewSubject.h"


//---------------------------------------------------
// IGUIObjekt Interface
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------
NAMESPACE_VIEW_B

	class IViewGUIObject :public IViewSubject
	{
	public:
		virtual ~IViewGUIObject()
		{
		};

		virtual bool checkHover(const float& fPosX, const float& fPosY)
		{
			//Prüfe ob X-Koordinate innerhalb des Buttons
			if ((fPosX > m_zfrRect.GetXPos()) && (fPosX < (m_zfrRect.GetXPos() + m_zfrRect.GetXSize())))
			{
				//Prüfe ob Y-Koordinate innerhalb des Buttons
				if ((fPosY > m_zfrRect.GetYPos()) && (fPosY < (m_zfrRect.GetYPos() + m_zfrRect.GetYSize())))
				{
					//Koordinaten sind auf Button
					onMouseOver();
					return true;
				}
				else
				{
					//X-Koordinate passt aber Y-Koordinate nicht
					//Koordinaten sind auf Button
					onMouseOut();
					return false;
				}
			}
			else
			{
				//X-Koordinate passt nicht
				onMouseOut();
				return false;
			}
		}

		virtual void checkEvent(CDeviceCursor* cursor, CDeviceKeyboard* keyboard)
		{
			float fPosX;
			float fPosY;

			cursor->GetFractional(fPosX, fPosY, true);


			if (checkHover(fPosX, fPosY))
			{
				if (cursor->ButtonPressedLeft())
				{
					onMouseClickLeft();
				}
			}
		}

		virtual void switchOn(void) =0;
		virtual void switchOff(void) = 0;
		virtual void onMouseOver(void) = 0;
		virtual void onMouseOut(void) = 0;
		virtual void onMouseClickLeft(void) = 0;
		virtual void onMouseClickRight(void) = 0;

		virtual bool isOn()
		{
			return m_bisOn;
		}

		virtual CFloatRect getRectangle()
		{
			return m_zfrRect;
		}

		virtual void setRectangle(CFloatRect tempRect)
		{
			m_zfrRect = tempRect;
		}

		virtual void setLayer(float layer) = 0;

		virtual void updateRectangle(CFloatRect rect) = 0;

		float getLayer()
		{
			return m_fLayer;
		}


		std::string sObjectName = "";
		//virtual void resize(int width, int height);
	protected:
		CFloatRect m_zfrRect = CFloatRect(0, 0, 0, 0);
		bool m_bisOn = true;
		float m_fLayer = 1.0;
	};

	NAMESPACE_VIEW_E
