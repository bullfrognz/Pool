//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Application.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_APPLICATION_H__
#define __IGFEB11_IG220_APPLICATION_H__

// Library Includes
#include <windows.h>
#include <vector>

// Local Includes

// Types

// Constants

// Prototypes
class CGameWindow;
class CIniParser;
class CLogManager;

class CApplication
{
    // Member Functions
public:
	~CApplication();

	static CApplication& GetInstance();
	static void DestroyInstance();

	void Initialise(HINSTANCE _hInstance);

	// Member inline Funtions
	inline void InsertDialogHandle(HWND _hDialog);

	inline HINSTANCE GetInstanceHandle();
	inline CGameWindow& GetGameWindow();
	inline CIniParser& GetIniParser();

	inline std::vector<HWND>& GetDialogHandles();

	inline CLogManager& GetLogManager();

	inline void Quit();

protected:
	
private:
	CApplication();
	CApplication(const CApplication& _kr);
	CApplication& operator= (const CApplication& _kr);

    // Member Variables
public:

protected:

private:
	HINSTANCE m_hInstance;
	CGameWindow*  m_pGameWindow;

	CIniParser* m_pIniParser;
	CLogManager* m_pLogManager;

	std::vector<HWND> m_vecDialogHandles;

	static CApplication* s_pApplication;

};

#include "Application.inl"

#endif // __IGFEB11_IG220_APPLICATION_H__
