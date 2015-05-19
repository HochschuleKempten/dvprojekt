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
			for (std::pair<std::string,IViewGUIContainer*> ContainerPair : m_Guicontainer)
			{
				delete ContainerPair.second;
			}
			m_Guicontainer.clear();
			
			for (std::pair<std::string, IViewGUIObject*> ObjectPair : m_guiObjects)
			{
				delete ObjectPair.second;
			}
			m_guiObjects.clear();
			for (std::pair<std::string, COverlay*> OverlayPair : m_Overlays)
			{
				delete OverlayPair.second;
			}
			for (std::pair<std::string, CViewport*> ViewportPair : m_viewports)
			{
				delete ViewportPair.second;
			}
			m_guiObjects.clear();
			if (m_hasBackground) delete m_background;
		};

		virtual void switchOn()
		{
			if (m_hasBackground)m_background->SwitchOn();

			for (std::pair<std::string, IViewGUIContainer*> ContainerPair : m_Guicontainer)
			{
				 ContainerPair.second->switchOn();
			}

			for (std::pair<std::string, IViewGUIObject*> ObjectPair : m_guiObjects)
			{
				 ObjectPair.second->switchOn();
			}
			
			for (std::pair<std::string, COverlay*> OverlayPair : m_Overlays)
			{
				 OverlayPair.second->SwitchOn();
			}
			for (std::pair<std::string, CViewport*> ViewportPair : m_viewports)
			{
				ViewportPair.second->SwitchOn();
			}

			for each (std::pair<std::string, COverlay *> overlay in m_Overlays)
			{
				overlay.second->SwitchOn();
			}

			m_bOn = true;
		};

		virtual void switchOff()
		{
			if (m_hasBackground)m_background->SwitchOff();

			for (std::pair<std::string, IViewGUIContainer*> ContainerPair : m_Guicontainer)
			{
				ContainerPair.second->switchOff();
			}

			for (std::pair<std::string, IViewGUIObject*> ObjectPair : m_guiObjects)
			{
				ObjectPair.second->switchOff();
			}

			for (std::pair<std::string, COverlay*> OverlayPair : m_Overlays)
			{
				OverlayPair.second->SwitchOff();
			}
			for (std::pair<std::string, CViewport*> ViewportPair : m_viewports)
			{
				ViewportPair.second->SwitchOff();
			}

			for each (std::pair<std::string, COverlay *> overlay in m_Overlays)
			{
				overlay.second->SwitchOff ();
			}
			m_bOn = false;
		};

		virtual bool isOn()
		{
			return m_bOn;
		}

		virtual VButton* addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, std::string sName)
		{
			m_guiObjects[sName] = new VButton(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, clickAction);
			//m_guiObjects[sName]->setLayer(getLayer() - 0.01F);
			m_guiObjects[sName]->setLayer(0.2F);
			m_guiObjects[sName]->setName(sName);
			m_guiObjects[sName]->addObserver(this);
		}

		virtual VTextfield* addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const std::string& Placeholder, std::string sName)
		{
			m_guiObjects[sName] = new VTextfield(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, MaterialActive, MaxChars, Placeholder);
			//m_guiObjects[sName]->setLayer(getLayer() - 0.01F);
			m_guiObjects[sName]->setLayer(0.2F);
			m_guiObjects[sName]->setName(sName);
			m_guiObjects[sName]->addObserver(this);
		}

		virtual VText* addText(CFloatRect rect, CWritingFont* writingFont, std::string text, std::string sName)
		{
			m_guiObjects[sName] = new VText(m_viewport, createRelativeRectangle(&m_zfRect, &rect), writingFont, text);
			//m_guiObjects[sName]->setLayer(getLayer() - 0.01F);
			m_guiObjects[sName]->setLayer(0.2F);
			m_guiObjects[sName]->setName(sName);
			m_guiObjects[sName]->addObserver(this);
		}

		virtual COverlay * addOverlay(CFloatRect rect, CMaterial* MaterialNormal, bool bChromaKeying, std::string sName)
		{
			m_Overlays[sName] = new COverlay();
			m_Overlays[sName]->Init(MaterialNormal, createRelativeRectangle(&m_zfRect, &rect));
			m_viewport->AddOverlay(m_Overlays[sName]);
			m_Overlays[sName]->SetLayer(0.1F);
		}

		virtual void addViewport(CCamera* cam, CFloatRect rect, const std::string& sName)
		{
			m_viewports[sName] = new CViewport();
			m_viewports[sName]->Init(cam, createRelativeRectangle(&m_zfRect, &rect));
		}
		virtual void addViewport(CViewport* viewport,CCamera* cam, CFloatRect rect, CBackground* background, const std::string& sName)
		{
			m_viewports[sName] = viewport;
			m_viewports[sName]->Init(cam, createRelativeRectangle(&m_zfRect, &rect));
			m_viewports[sName]->AddBackground(background);
		}
		virtual CViewport* getViewport(const std::string& sName)
		{
			return m_viewports[sName];
		}

		virtual void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::string& sName) = 0;


		virtual void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::string& sName) = 0;


		virtual void setLayer(const float layer)
		{
			float fLayerDiff = layer - getLayer();

			if (m_hasBackground)m_background->SetLayer(layer);

			for (std::pair<std::string, IViewGUIObject*> ObjectPair : m_guiObjects)
			{
				ObjectPair.second->setLayer(ObjectPair.second->getLayer() + fLayerDiff);
			}


			//For all containers in the screen
			for (std::pair<std::string, IViewGUIContainer*> ContainerPair : m_Guicontainer)
			{
				ContainerPair.second->setLayer(ContainerPair.second->getLayer() + fLayerDiff);
			}
		}


		IViewGUIContainer* getContainer(const std::string& sName)
		{
			ASSERT(m_Guicontainer.find(sName) != m_Guicontainer.end(), "GUIContainer not available");
			return m_Guicontainer[sName];
		}

		std::unordered_map<std::string, IViewGUIContainer*> getGuiContainerMap()
		{
			return m_Guicontainer;
		}

		COverlay* getOverlay(const std::string& sName)
		{
			ASSERT(m_Overlays.find(sName) != m_Overlays.end(), "Overlay not available");
			return m_Overlays[sName];
		}

		std::unordered_map<std::string, COverlay*> getOverlayMap()
		{
			return m_Overlays;
		}

		std::unordered_map<std::string, IViewGUIObject*> getGuiObjectList()
		{
			return m_guiObjects;
		}

		IViewGUIObject* getGuiObject(const std::string& sName)
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
		std::unordered_map<std::string, IViewGUIObject*> m_guiObjects;

		std::unordered_map<std::string, IViewGUIContainer*> m_Guicontainer;
		

		std::unordered_map<std::string, COverlay*> m_Overlays;
		

		std::unordered_map<std::string, CViewport*> m_viewports;
		

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
