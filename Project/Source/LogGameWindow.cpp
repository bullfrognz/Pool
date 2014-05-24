//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   LogGameWindow.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <windows.h>

// Local Includes
#include "Text.h"

// This Include
#include "LogGameWindow.h"

// Static Variables

// Static Function Prototypes

// Implementation

CLogGameWindow::CLogGameWindow()
: m_iNumActiveText(0)
{
	//Empty
}

CLogGameWindow::~CLogGameWindow()
{
	Deinitialise();
}

void
CLogGameWindow::Initialise()
{
	for (int i = 0; i < s_kiMaxLogText; ++ i)
	{
		m_pLogText[i] = new CText;
		m_pLogText[i]->Initialise();
		m_pLogText[i]->SetTextAlign(TEXTALIGN_LEFT);
	}
}

void
CLogGameWindow::Deinitialise()
{
	for (int i = 0; i < s_kiMaxLogText; ++ i)
	{
		delete m_pLogText[i];
		m_pLogText[i] = 0;
	}
}

void
CLogGameWindow::Process(float _fDeltaTick)
{
	for (int i = 0; i < s_kiMaxLogText; ++ i)
	{
		m_pLogText[i]->Process(_fDeltaTick);
	}
}

void
CLogGameWindow::Draw()
{
	for (int i = 0; i < s_kiMaxLogText; ++ i)
	{
		m_pLogText[i]->Draw();
		m_pLogText[i]->SetDisplay(false);
	}

	m_iNumActiveText = 0;
}

void 
CLogGameWindow::Write(const char* _pcMessage)
{
	const int kiTextHeight = m_pLogText[0]->GetFontHeight();

	for (int i = 0; i < s_kiMaxLogText; ++ i)
	{
		if (m_pLogText[i]->IsDisplaying() == false)
		{
			const int kiPaddingTop = (m_iNumActiveText * kiTextHeight) + 5;

			m_pLogText[i]->SetText(_pcMessage);
			m_pLogText[i]->SetPosition(X, 10);
			m_pLogText[i]->SetPosition(Y, kiPaddingTop);
			m_pLogText[i]->SetDisplay(true);

			++ m_iNumActiveText;

			break;
		}
	}
}