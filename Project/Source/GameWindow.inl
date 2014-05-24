//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Window.inl
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Include

// Static Variables

// Static Function Prototypes

// Implementation

int
CGameWindow::GetWidth()
{
	return (m_iWidth);
}

int
CGameWindow::GetHeight()
{
	return (m_iHeight);
}

CBackBuffer&
CGameWindow::GetBackBuffer()
{
	return (*m_pBackBuffer);
}

CClock&
CGameWindow::GetClock()
{
	return (*m_pClock);
}

CMessageManager&
CGameWindow::GetMsgManager()
{
	return (*m_pMessageManager);
}

HWND
CGameWindow::GetHandle()
{
	return (m_hWindow);
}

RECT
CGameWindow::GetBounds()
{
	return (m_rectBounds);
}

IScene&
CGameWindow::GetScene()
{
	return (*m_pWindowScene);
}