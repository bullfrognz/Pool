//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Window.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_WINDOW_H__
#define __IGFEB11_IG220_WINDOW_H__

// Library Includes
#include <windows.h>

// Local Includes

// Types
enum EWindowScene
{
	SCENE_INVALID,
	SCENE_MAINMENU,
	SCENE_GAME,
	SCENE_MAX
};

// Constants

// Prototypes
class CClock;
class CBackBuffer;
class CMessageManager;
class IScene;
enum EWindowScene;

class CGameWindow
{
    // Member Functions
public:
	CGameWindow(HINSTANCE _hInstance);
	~CGameWindow();

	HWND Initialise(LPCWSTR _kcpTitle, DWORD _iStyle, int _iPosX, int _iPosY, int _iWidth,
					int _iHeight, HMENU hwndMenu = NULL, HWND hwndParent = NULL);

	LRESULT CALLBACK WindowProc(HWND _hWindow, UINT _Message, WPARAM _wParam, LPARAM _lParam);

	void SetScene(EWindowScene _eScene);

	void ExecuteOneFrame();

	void SetCursorDisplay(bool _bShow);

	// Member inline Functions
	inline int GetWidth();
	inline int GetHeight();

	inline CBackBuffer& GetBackBuffer();
	inline CClock& GetClock();
	inline CMessageManager& GetMsgManager();

	inline HWND GetHandle();

	inline RECT GetBounds();

	inline IScene& GetScene();

protected:

private:
	CGameWindow(const CGameWindow& _kr);
	CGameWindow& operator= (const CGameWindow& _kr);

	bool InitialiseWinClass();

    // Member Variables
public:

protected:

private:
	RECT m_rectBounds;

	CClock* m_pClock;
	CBackBuffer* m_pBackBuffer;

	IScene* m_pWindowScene;

	CMessageManager* m_pMessageManager;

	HINSTANCE m_hInstance;
	
	HWND m_hWindow;
	HICON m_hIcon;
	HCURSOR m_hCursor;
	HMENU m_hMenu;

	int m_iWidth;
	int m_iHeight;

	bool m_bCursorDisplay;

};

#include "GameWindow.inl"

#endif // __IGFEB11_IG220_WINDOW_H__
