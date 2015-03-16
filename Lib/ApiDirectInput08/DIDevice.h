// DIDevice.h: interface for the CDIDevice class
//
//////////////////////////////////////////////////////////////////////
#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"

namespace Vektoria
{

class CDIDevice
{
public:
    CDIDevice(void);
    virtual ~CDIDevice(void);

    virtual bool Init(void);
    virtual void Tick(void);
    void Fini(void); // Gibt das Device wieder frei

    void SetHWND(HWND hwnd); // The the HWND to which the game controller will be attached
	void SetHINSTANCE(HINSTANCE hinst);
	void SetDirectInput(LPDIRECTINPUT8 lpDI);
    void SetDIDeviceInfo(LPCDIDEVICEINSTANCE lpDIDeviceInfo);
    void SetGUID(GUID guid);

    bool IsDeviceInitialized(void);
protected:
    HWND m_hwnd; // HWND to which Direct Input will be attached to
	HINSTANCE m_hInstance; // This modules Instance

	LPDIRECTINPUT8 m_lpDI; // Pointer to Direct Input
    LPCDIDEVICEINSTANCE m_lpDIDeviceInfo; // Pointer to Device Info
	LPDIRECTINPUTDEVICE8 m_lpDIDevice; // Pointer to Direct Input Device

    GUID m_GUID_Device;

	bool m_bDIInit; // Has Direct Input Been Initialised?
	bool m_bDeviceInit;
};

}