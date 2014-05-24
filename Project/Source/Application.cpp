//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Applcation.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <Windows.h>

// Local Includes
#include "IniParser.h"
#include "GameWindow.h"
#include "LogManager.h"

// Framework

// Core

// Scene

// This Include
#include "Application.h"

// Static Variables

// Static Function Prototypes
CApplication* CApplication::s_pApplication = 0;

// Implementation
CApplication::CApplication()
: m_hInstance(0)
, m_pGameWindow(0)
, m_pIniParser(0)
, m_pLogManager(0)
{
	//Empty
}

CApplication::~CApplication()
{
	delete m_pGameWindow;
	m_pGameWindow = 0;

	m_pIniParser->CloseFile(true);
	delete m_pIniParser;
	m_pIniParser = 0;

	//delete m_pLogManager;
	//m_pLogManager = 0;
}

CApplication&
CApplication::GetInstance()
{
	if (s_pApplication == 0)
	{
		s_pApplication = new CApplication();

		srand(static_cast<unsigned int>(timeGetTime()));
	}

	return (*s_pApplication);
}

void
CApplication::DestroyInstance()
{
	delete s_pApplication;
	s_pApplication = 0;
}

void
CApplication::Initialise(HINSTANCE _hInstance)
{
	m_hInstance = _hInstance;

	m_pGameWindow = new CGameWindow(m_hInstance);

	m_pIniParser = new CIniParser;
	m_pIniParser->LoadIniFile("GameSettings.ini");

	//m_pLogManager = new CLogManager();
	//m_pLogManager->Initialise();
	//m_pLogManager->AddLogTarget(LOGTARGET_GAMEWINDOW);
}