#pragma once
#include "Windows.h"

//-------------------------------------------
// CSplash: Klasse für ein Spläschfenstersche
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.04.2014
// Copyright: Moyzelle Vektoria
//-------------------------------------------

namespace Vektoria
{


	class CSplash
	{
		friend class CRoot;
	public:
		CSplash();
		virtual ~CSplash();

		void Init(HWND hwnd, HINSTANCE hinstance);
		void ShowProgressBar(float frProgress);
		void HideProgressBar();

		void Hide();
		void Show();

		bool m_bShow;
		bool m_bShowProgressBar;

		int m_ixSplash, m_iySplash;
		int m_ixFather, m_iyFather;
		int m_iWidth, m_iHeight;
		RECT m_rectFather;



	private:
		int CalcKey(char * szPath);

		UINT m_idTimer;
		HWND m_hwnd;
		HINSTANCE m_hinstance;
		HWND m_hwndParent;
		HWND m_hwndSplash;
		HWND m_hwndProgressBar;
		bool m_bShowed;
		int m_idInit;
		int m_idShow;

	};

}