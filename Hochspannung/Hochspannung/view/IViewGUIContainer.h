#pragma once

#include"VButton.h"
#include"IViewUIObserver.h"
#include"IViewSubject.h"
#include "VTextfield.h"
#include "VText.h"


NAMESPACE_VIEW_B

	//---------------------------------------------------
	// Interface:IGUIContainer
	// Beschreibung:
	//
	// Autor: Patrick Benkowitsch
	//---------------------------------------------------

	class IViewGUIContainer:public IViewUIObserver,public IViewSubject
	{
	public:
		enum ContainerType
		{
			Group,
			Dialog,
			Register,
			GUIArea,
			ListView
		};

		virtual ~IViewGUIContainer()
		{
			for (m_lIterGUIObjects = m_guiObjects.begin(); m_lIterGUIObjects != m_guiObjects.end(); ++m_lIterGUIObjects)
			{
				delete m_lIterGUIObjects->second;
			}
			m_guiObjects.clear();
			if (m_hasBackground) delete m_background;
		};

		virtual void switchOn()
		{
			if (m_hasBackground)m_background->SwitchOn();

			for (m_lIterGUIObjects = m_guiObjects.begin(); m_lIterGUIObjects != m_guiObjects.end(); m_lIterGUIObjects++)
			{
				m_lIterGUIObjects->second->switchOn();
			}


			//For all containers in the screen
			for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); m_IterGuicontainer++)
			{
				m_IterGuicontainer->second->switchOn();
			}
			m_bOn = true;
		};

		virtual void switchOff()
		{
			if (m_hasBackground)m_background->SwitchOff();

			for (m_lIterGUIObjects = m_guiObjects.begin(); m_lIterGUIObjects != m_guiObjects.end(); m_lIterGUIObjects++)
			{
				m_lIterGUIObjects->second->switchOff();
			}


			//For all containers in the screen
			for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); m_IterGuicontainer++)
			{
				m_IterGuicontainer->second->switchOff();
			}

			m_bOn = false;
		};

		virtual bool isOn()
		{
			return m_bOn;
		}

		virtual void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, std::string sName)
		{
			m_guiObjects[sName] = new VButton(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, clickAction);
			//m_guiObjects[sName]->setLayer(getLayer() - 0.01F);
			m_guiObjects[sName]->setName(sName);
			m_guiObjects[sName]->addObserver(this);
		}

		virtual void addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const std::string& Placeholder, std::string sName)
		{
			m_guiObjects[sName] = new VTextfield(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, MaterialActive, MaxChars, Placeholder);
			//m_guiObjects[sName]->setLayer(getLayer() - 0.01F);
			m_guiObjects[sName]->setName(sName);
			m_guiObjects[sName]->addObserver(this);
		}

		virtual void addText(CFloatRect rect, CWritingFont* writingFont, std::string text, std::string sName)
		{
			m_guiObjects[sName] = new VText(m_viewport, createRelativeRectangle(&m_zfRect, &rect), writingFont, text);
			//m_guiObjects[sName]->setLayer(getLayer() - 0.01F);
			m_guiObjects[sName]->setName(sName);
			m_guiObjects[sName]->addObserver(this);
		}

		virtual void addOverlay(CFloatRect rect, CMaterial* MaterialNormal, bool bChromaKeying, std::string sName)
		{
			m_Overlays[sName] = new COverlay();
			m_Overlays[sName]->Init(MaterialNormal, createRelativeRectangle(&m_zfRect, &rect));
			m_viewport->AddOverlay(m_Overlays[sName]);
			m_Overlays[sName]->SetLayer(0.1F);
		}

		virtual void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::string& sName) = 0;


		virtual void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::string& sName) = 0;


		virtual void setLayer(float layer)
		{
			float fLayerDiff = layer - getLayer();

			if (m_hasBackground)m_background->SetLayer(layer);

			for (m_lIterGUIObjects = m_guiObjects.begin(); m_lIterGUIObjects != m_guiObjects.end(); m_lIterGUIObjects++)
			{
				m_lIterGUIObjects->second->setLayer(m_lIterGUIObjects->second->getLayer() + fLayerDiff);
			}


			//For all containers in the screen
			for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); m_IterGuicontainer++)
			{
				m_IterGuicontainer->second->setLayer(m_IterGuicontainer->second->getLayer() + fLayerDiff);
			}
		}


		IViewGUIContainer* getContainer(std::string sName)
		{
			ASSERT(m_Guicontainer.find(sName) != m_Guicontainer.end(), "GUIContainer not available");
			return m_Guicontainer[sName];
		}

		std::map<std::string, IViewGUIContainer*> getGuiContainerMap()
		{
			return m_Guicontainer;
		}

		COverlay* getOverlay(std::string sName)
		{
			ASSERT(m_Overlays.find(sName) != m_Overlays.end(), "Overlay not available");
			return m_Overlays[sName];
		}

		std::map<std::string, COverlay*> getOverlayMap()
		{
			return m_Overlays;
		}

		std::map<std::string, IViewGUIObject*> getGuiObjectList()
		{
			return m_guiObjects;
		}

		IViewGUIObject* getGuiObject(std::string sName)
		{
			return m_guiObjects[sName];
		}

		CFloatRect getRectangle()
		{
			return m_zfRect;
		}

	protected:

		bool m_bOn = true;
		bool m_hasBackground = false;
		float m_fLayer = 1.0;
		CViewport* m_viewport;
		COverlay* m_background;
		CFloatRect m_zfRect;
		std::map<std::string, IViewGUIObject*> m_guiObjects;
		std::map<std::string, IViewGUIObject*>::iterator m_lIterGUIObjects;

		std::map<std::string, IViewGUIContainer*> m_Guicontainer;
		std::map<std::string, IViewGUIContainer*>::iterator m_IterGuicontainer;

		std::map<std::string, COverlay*> m_Overlays;
		std::map<std::string, COverlay*>::iterator m_IterOverlays;

		virtual CFloatRect createRelativeRectangle(CFloatRect* RelativeToRect, CFloatRect* RelativeRect)
		{
			return CFloatRect(RelativeToRect->GetXPos() + (RelativeToRect->GetXSize() * RelativeRect->GetXPos()), RelativeToRect->GetYPos() + (RelativeToRect->GetYSize() * RelativeRect->GetYPos()),
			                  RelativeToRect->GetXSize() * RelativeRect->GetXSize(), RelativeToRect->GetYSize() * RelativeRect->GetYSize());
		}

		float getLayer()
		{
			return m_fLayer;
		}
	};

	NAMESPACE_VIEW_E
