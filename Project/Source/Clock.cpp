//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Clock.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <iostream>

// Local Includes

// Framework
#include "Application.h"
#include "GameWindow.h"
#include "IniParser.h"

// Core
#include "Text.h"

// Scene

// This Include
#include "Clock.h"

// Static Variables

// Static Function Prototypes

// Implementation

CClock::CClock()
: m_fTimeElapsed(0)
, m_fDeltaTime(0)
, m_fCurrentTime(0)
, m_fLastTime(0)
, m_iFrameCount(0)
, m_cpFpsMessage(0)
, m_fSetDeltaTick(0)
{
	// Default Constructor.
}

CClock::~CClock()
{
	delete m_pFpsText;
	m_pFpsText = 0;

	delete m_cpFpsMessage;
	m_cpFpsMessage = 0;
}

bool 
CClock::Initialise()
{
	const int iWindowWidth  = CApplication::GetInstance().GetGameWindow().GetWidth();
	const int iWindowHeight = CApplication::GetInstance().GetGameWindow().GetHeight();

	m_cpFpsMessage = new char[32];

	m_pFpsText = new CText;
	m_pFpsText->Initialise();
	m_pFpsText->SetText("Initialising");
	m_pFpsText->SetDisplay(true);
	m_pFpsText->SetPosition(X, iWindowWidth - 80.0f);
	m_pFpsText->SetPosition(Y, iWindowHeight - 80.0f);

	float fMaxFrames = 60.0f;

	CIniParser& rIniGameSettings = CApplication::GetInstance().GetIniParser();
	rIniGameSettings.GetValue("Clock", "MaxFrames", fMaxFrames);

	m_fMaxFrames = fMaxFrames;

	m_fMinFrames = 60.0f;
	m_fMaxDeltaTick = 1.0f / m_fMinFrames;

	return(true);
}

bool 
CClock::Deinitialise()
{
	return (true);
}

void 
CClock::Process()
{
	m_fLastTime = m_fCurrentTime;
		
	m_fCurrentTime = static_cast<float>(timeGetTime());

	if(m_fLastTime == 0.0f)
	{
		m_fLastTime = m_fCurrentTime;
	}

	m_fDeltaTime = (m_fCurrentTime - m_fLastTime) / 1000.0f;

	m_fTimeElapsed += m_fDeltaTime;

	ProcessFPSCap();
	ProcessFPSText();
}

void
CClock::Draw()
{
	m_pFpsText->Draw();
}

void
CClock::ProcessFPSCap()
{


}

void
CClock::ProcessFPSText()
{
	++ m_iFrameCount;

	if (m_fTimeElapsed > 1.0f)
	{
		sprintf_s(m_cpFpsMessage, 32, "FPS: %d", m_iFrameCount);
		m_pFpsText->SetText(m_cpFpsMessage);

		m_iFrameCount = 0;
		m_fTimeElapsed = 0.0f;
	}
}

float 
CClock::GetDeltaTick()
{
	if (m_fSetDeltaTick != 0.0f && m_fSetDeltaTick > 0.0f)
	{
		return (m_fSetDeltaTick);
	}

	if (m_fMaxDeltaTick < m_fDeltaTime)
	{
		return (m_fMaxDeltaTick);
	}

	return(m_fDeltaTime);
}

void
CClock::SetStaticDeltaTick(float _fDeltaTick)
{
	m_fSetDeltaTick = _fDeltaTick;
}

void
CClock::SetMaxFrames(float _fMaxFrames)
{
	if (_fMaxFrames < 1.0f)
	{
		_fMaxFrames = 1;
	}

	m_fMaxFrames = _fMaxFrames;
}

float
CClock::GetMaxFrames()
{
	return (m_fMaxFrames);
}

float
CClock::GetStaticDeltatick()
{
	return (m_fSetDeltaTick);
}