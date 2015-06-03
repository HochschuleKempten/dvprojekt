#pragma once

#include"VButton.h"
#include"IViewUIObserver.h"
#include"IViewSubject.h"
#include "VTextfield.h"
#include "VText.h"
#include "VGraph.h"
#include "VGraphRatio.h"

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
		for (std::pair<std::string, IViewGUIContainer*> ContainerPair : m_Guicontainer)
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
			overlay.second->SwitchOff();
		}
		m_bOn = false;
	};

	virtual bool isOn()
	{
		return m_bOn;
	}

	virtual VButton* addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, const Event& clickAction, const std::string& sName, const float layer)
	{
		m_guiObjects[sName] = new VButton(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, clickAction, layer);

		m_guiObjects[sName]->setName(sName);
		m_guiObjects[sName]->addObserver(this);


		return CASTD<VButton*>(m_guiObjects[sName]);
	}

	virtual VButton* addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const Event& clickAction, const std::string& sName, const float layer)
	{
		m_guiObjects[sName] = new VButton(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, MaterialActive, clickAction, layer);

		m_guiObjects[sName]->setName(sName);
		m_guiObjects[sName]->addObserver(this);


		return CASTD<VButton*>(m_guiObjects[sName]);
	}

	virtual VTextfield* addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int MaxChars, const std::string& Placeholder, const std::string& sName, const float layer)
	{
		m_guiObjects[sName] = new VTextfield(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, MaterialActive, MaxChars, Placeholder, layer);

		m_guiObjects[sName]->setName(sName);
		m_guiObjects[sName]->addObserver(this);


		return CASTD<VTextfield*>(m_guiObjects[sName]);
	}

	virtual VText* addText(CFloatRect rect, CWritingFont* writingFont, const std::string& text, const std::string& sName, const float layer)
	{
		m_guiObjects[sName] = new VText(m_viewport, createRelativeRectangle(&m_zfRect, &rect), writingFont, text, layer);

		m_guiObjects[sName]->setName(sName);
		m_guiObjects[sName]->addObserver(this);


		return CASTD<VText*>(m_guiObjects[sName]);
	}

	virtual COverlay* addOverlay(CFloatRect rect, CMaterial* MaterialNormal, const std::string& sName, const float layer)
	{
		m_Overlays[sName] = new COverlay();
		m_Overlays[sName]->Init(MaterialNormal, createRelativeRectangle(&m_zfRect, &rect));
		m_viewport->AddOverlay(m_Overlays[sName]);

		if (layer == NULL)
		{
			m_Overlays[sName]->SetLayer(getLayer() - 0.01F);
		}
		else
		{
			m_Overlays[sName]->SetLayer(layer);
		}

		return m_Overlays[sName];
	}

	virtual CViewport* addViewport(CCamera* cam, CFloatRect rect, const std::string& sName)
	{
		m_viewports[sName] = new CViewport();
		m_viewports[sName]->Init(cam, createRelativeRectangle(&m_zfRect, &rect));

		return m_viewports[sName];
	}

	virtual VGraph* addGraph(CFloatRect rect, const std::string& sName)
	{
		m_guiObjects[sName] = new VGraph(m_viewport, createRelativeRectangle(&m_zfRect, &rect));
		//m_guiObjects[sName]->setLayer(getLayer() - 0.01F);
		m_guiObjects[sName]->setLayer(0.2F);
		m_guiObjects[sName]->setName(sName);
		m_guiObjects[sName]->addObserver(this);

		return CASTD<VGraph *>(m_guiObjects[sName]);
	}

	virtual VGraphRatio* addGraphRatio(CFloatRect rect, const std::string& sName, CMaterial* normalMaterial)
	{
		m_guiObjects[sName] = new VGraphRatio(m_viewport, createRelativeRectangle(&m_zfRect, &rect), normalMaterial);
		//m_guiObjects[sName]->setLayer(getLayer() - 0.01F);
		m_guiObjects[sName]->setLayer(0.2F);
		m_guiObjects[sName]->setName(sName);
		m_guiObjects[sName]->addObserver(this);

		return CASTD<VGraphRatio *>(m_guiObjects[sName]);
	}

	virtual CViewport* addViewport(CViewport* viewport, CCamera* cam, CFloatRect rect, CBackground* background, const std::string& sName)
	{
		m_viewports[sName] = viewport;
		m_viewports[sName]->Init(cam, createRelativeRectangle(&m_zfRect, &rect));
		m_viewports[sName]->AddBackground(background);

		return m_viewports[sName];
	}

	virtual CViewport* getViewport(const std::string& sName)
	{
		return m_viewports[sName];
	}

	virtual void addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::string& sName, const float layer) = 0;


	virtual void addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::string& sName, const float layer) = 0;


	virtual void setLayer(const float layer)
	{
		float fLayerDiff = layer - 0.01F;

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

	void slideDown(float amount)
	{
		for (std::pair<std::string, IViewGUIContainer*> ContainerPair : m_Guicontainer)
		{
			ContainerPair.second->m_zfRect.SetYPos(ContainerPair.second->m_zfRect.GetYPos()-amount);
			ContainerPair.second->slideDown(amount);
		}

		for (std::pair<std::string, IViewGUIObject*> ObjectPair : m_guiObjects)
		{
			CFloatRect tempRect = ObjectPair.second->getRectangle();
			tempRect.SetYPos(tempRect.GetYPos() - amount);
			ObjectPair.second->updateRectangle(tempRect);
			ObjectPair.second->setRectangle(tempRect);
		}

		for (std::pair<std::string, COverlay*> OverlayPair : m_Overlays)
		{
			CFloatRect tempRect = OverlayPair.second->GetRect();
			tempRect.SetYPos(tempRect.GetYPos() - amount);
			OverlayPair.second->SetRect(tempRect);
		}
		for (std::pair<std::string, CViewport*> ViewportPair : m_viewports)
		{
			//ViewportPair.second->
			
		}

		m_zfRect.SetYPos(m_zfRect.GetYPos() - amount);

	}

	std::string getName()
	{
		return m_sName;
	}

	void setName(const std::string& value)
	{
		m_sName=value;
	}
protected:

	bool m_bOn = true;
	bool m_hasBackground = false;
	float m_fLayer = 1.0;
	CViewport* m_viewport;
	COverlay* m_background;
	CFloatRect m_zfRect;
	std::string m_sName="";
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
