#include "VMaster.h"
#include "../logic/IView.h"

NAMESPACE_VIEW_B


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
			CGeo* picked = m_zkCursor.PickGeo(CHVector(), f);
			//CPlacement* picked = m_zkCursor.PickPlacement();

			if (picked != nullptr) {
				DEBUG_OUTPUT("picked object = " << picked->GetName());
			}

			pickingActive = true;
		}
	}
	else {
		pickingActive = false;
	}

	m_zr.Tick(fTimeDelta);
}

void VMaster::addScenegraph(IView* view)
{
	views.push_back(view);
	m_zs.AddPlacement(dynamic_cast<CPlacement*>(view));
}


NAMESPACE_VIEW_E
