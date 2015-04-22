#pragma once
#include "Viewports.h"
#include "RenderApi.h"

//------------------------------------
// CRenderframe
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

class CRoot;

class CRenderframe
{
public:
	CRenderframe();
	~CRenderframe();
	CRenderframe operator=(CRenderframe renderframe);
	void Copy(CRenderframe renderframe);

	CRenderApi * Init(int eRenderApi, HWND hwnd, int iWidthWindow, int iHeightWindow);
	void Tick(float & fTimeDelta);
	void Fini();

	void SetRoot(CRoot * proot);

	void AddViewport(CViewport * pviewport);

	void ReSize(int iWidthWindow, int iHeightWindow);
	void CommitSuicide(float fTimeToKill);
	bool m_bArrrgh;
	bool m_bCommitSuicide;
	float m_fTimeToKill;

	CViewports m_viewports;
	CRenderApi * m_prenderapi;
	int m_iWidthWindow;
	int m_iHeightWindow;
	HWND m_hwnd;
	int m_eRenderApi;
	CRoot * m_proot;
};
