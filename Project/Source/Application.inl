//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Application.inl
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

void
CApplication::InsertDialogHandle(HWND _hDialog)
{
	m_vecDialogHandles.push_back(_hDialog);
}

HINSTANCE
CApplication::GetInstanceHandle()
{
	return m_hInstance;
}
	
CGameWindow&
CApplication::GetGameWindow()
{
	return (*m_pGameWindow);
}

CIniParser&
CApplication::GetIniParser()
{
	return (*m_pIniParser);
}

std::vector<HWND>&
CApplication::GetDialogHandles()
{
	return (m_vecDialogHandles);
}

CLogManager&
CApplication::GetLogManager()
{
	return (*m_pLogManager);
}

void
CApplication::Quit()
{
	PostQuitMessage(0);
}