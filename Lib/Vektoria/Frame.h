////////////////////////////////////////////////////
/// @file Frame.h
/// @description
///
/// @author Tobias Breiner, Matthias Sommer
/// ** Copyright (c) Vektoria **
/// ** This file is part of vektoria **
////////////////////////////////////////////////////
#pragma once
#include "Viewports.h"
#include "ApiRender.h"
#include "ApiSound.h"
#include "Device.h"
#include "DeviceKeyboard.h"
#include "DeviceMouse.h"
#include "DeviceGameController.h"
#include "DeviceCursor.h"
#include "DistributedGlobal.h"



namespace Vektoria
{
	// Forward declarations
	class CRoot;
	class CFrames;


	class CFrame: public CNode
	{
		friend class CRoot;
		friend class CFrames;
	private:
		void Tick(float & fTimeDelta, bool & bTickTack);
		// The WndProc callback function.
		//		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMessage, WPARAM wParam, LPARAM lParam);
		void SetRoot(CRoot* pRoot);
		CRoot* GetRoot(void) const;
		CRoot* m_proot;				// Pointer to the root of vektoria.

	public:
		// Data
		CViewports m_viewports;		// List of attached viewports.
		EApiInput m_eApiInput;		// The input api.
		EApiRender m_eApiRender;	// The render api
		EApiSound m_eApiSound;	// The render api
		CApiRender* m_papirender;	// Pointer to the render api.
		CApiSound* m_papisound;		// Pointer zur Sound-Api.
//		string sWindowName;			// The name of the frame.
		int m_iWidthWindow;			// The with of the frame.
		int m_iHeightWindow;		// The height of the frame.
		bool m_bFullScreen;			// Indicates weather the frame is in full screen mode.
		HWND m_hwnd;				// The Win32 window handle. (TODO: Here no OS spectific members o.O)
		CDevice* m_pdevice;			// Input devices (Keyboard, Mouse, GameController).
		CDeviceCursor* m_pdevicecursor; 

		// Default constructor
		CFrame(void);
		// Destructor
		~CFrame(void);

		// Overloaded assignment operator.
		CFrame operator=(const CFrame& frame);

		// Copy the frame.
		void Copy(const CFrame& frame);

		// Initialize the frame.
		// CApiRender* Init(HWND hwnd, EApiRender eApiRender = eApiRender_DirectX11_Shadermodel50, EApiInput eApiInput = eApiInput_DirectInput, EShaderCreation eShaderCreation = eShaderCreation_CompileChanges, EShaderAutoRecompilation eShaderAutoRecompilation = eShaderAutoRecompilation_Enabled);
		void Init(HWND hwnd, EApiRender eApiRender = eApiRender_DirectX11_Shadermodel50, EApiInput eApiInput = eApiInput_DirectInput, EApiSound eApiSound = eApiSound_DirectSound, EShaderCreation eShaderCreation = eShaderCreation_CompileChanges, EShaderAutoRecompilation eShaderAutoRecompilation = eShaderAutoRecompilation_Enabled);

		// Finalize the frame.
		void Fini(void);

		void AddViewport(CViewport * pviewport);
		void AddDeviceKeyboard(CDeviceKeyboard * pdevicekeyboard);
		void AddDeviceMouse(CDeviceMouse * pdevicemouse);
		void AddDeviceGameController(CDeviceGameController * pdevicegamecontroller);
		void AddDeviceCursor(CDeviceCursor * pdevicecursor);



		// Resize the frame.
		void ReSize(int iWidthWindow, int iHeightWindow);



		// Toggle full screen.
		// void ToggleFullScreen(void);

		#pragma region NetworkMaster
	#ifdef NETWORKMASTER
		unsigned int GetidId();
	private:
		unsigned int m_idId;
		int m_icId;
	#endif
		#pragma endregion
		


	};
}