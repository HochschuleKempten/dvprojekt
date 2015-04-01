#include "VMaster.h"
#include "../logic/IView.h"
#include "../logic/LMaster.h"
#include "../logic/LUtility.h"
#include "VFactory.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B


VMaster::VMaster()
	: factory(this)
{
}

void VMaster::setLMaster(LMaster* lMaster)
{
	this->lMaster = lMaster;
}

void VMaster::initScene(HWND hwnd, CSplash* psplash)
{
	m_zr.Init(psplash);
	m_zf.Init(hwnd);
	m_zc.Init();
	m_zv.InitFull(&m_zc);
	m_zr.AddFrameHere(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zf.AddDeviceKeyboard(&m_zk);
	m_zf.AddDeviceCursor(&m_zkCursor);
	m_zf.AddDeviceMouse(&m_zkMouse);
	m_zr.AddScene(&m_zs);

	m_zb.InitFull("textures/red_image.jpg");
	m_zv.AddBackground(&m_zb);

	m_zs.AddPlacement(&m_zpCamera);
	m_zpCamera.AddCamera(&m_zc);
	m_zs.AddParallelLight(&m_zl);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f),
			CColor(1.0f, 1.0f, 1.0f));
}

void VMaster::tick(float fTime, float fTimeDelta)
{
	m_zk.PlaceWASD(m_zpCamera, fTimeDelta);

	/* Picking */
	static bool pickingActive = false;

	if (m_zkCursor.ButtonPressedLeft()) {
		if (!pickingActive) {
			float f;

			CPlacement *pickedPlacement = m_zkCursor.PickPlacement();
			std::vector<std::string> koord = split(pickedPlacement->GetName(), ';');

			if (pickedPlacement != nullptr && koord.size() > 0)
			{
				DEBUG_OUTPUT("picked object = " << pickedPlacement->GetName());

				if (koord[0] == getClassName(VPlayingField)) {
					ASSERT(koord.size() == 3, "Not enough arguments in the placement name");

					int i = std::stoi(koord[1]);
					int j = std::stoi(koord[2]);

					dynamic_cast<VPlayingField*>(views[getClassName(VPlayingField)])->fieldClicked(i, j);
				}

			}

			pickingActive = true;
		}
	}
	else {
		pickingActive = false;
	}

	m_zr.Tick(fTimeDelta);
}

IVFactory* VMaster::getFactory()
{
	return &factory;
}

VPlayingField* VMaster::getPlayingField()
{
	return dynamic_cast<VPlayingField*>(views[getClassName(VPlayingField)]);
}

void VMaster::addScenegraph(const std::string &name, IViewObject* view)
{
	views[name] = view;
	m_zs.AddPlacement(view->getPlacement());
}

void VMaster::resize(int width, int heigth)
{
	m_zf.ReSize(width, heigth);
}


NAMESPACE_VIEW_E
