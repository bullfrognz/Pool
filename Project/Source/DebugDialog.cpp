//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   DebugDialog.cpp
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "Resource.h"

// Framework
#include "TickBox.h"
#include "TextField.h"

// Core

// Scene

// This Include
#include "DebugDialog.h"

// Static Variables

// Static Function Prototypes

// Implementation

CDebugDialog::CDebugDialog()
: m_pDeltaTick(0)
, m_pMaxFrames(0)
, m_bApply(false)
{
	//Empty
}

CDebugDialog::~CDebugDialog()
{
	Deinitialise();
}

bool
CDebugDialog::Initialise(HINSTANCE _hInstance, HWND _hWindow , int _iResourceId)
{
	CDialog::Initialise(_hInstance, _hWindow, _iResourceId);

	m_pDeltaTick = new CTextField;
	m_pDeltaTick->Initialise(CDialog::m_hDialog, IDC_TEXTFIELD_DELTATICK);

	m_pMaxFrames = new CTextField;
	m_pMaxFrames->Initialise(CDialog::m_hDialog, IDC_TEXTFIELD_MAXFRAMES);

	return (true);
}

bool
CDebugDialog::Deinitialise()
{
	delete m_pDeltaTick;
	m_pDeltaTick = 0;

	delete m_pMaxFrames;
	m_pMaxFrames = 0;

	return (true);
}

BOOL CALLBACK 
CDebugDialog::DialogProc(HWND _hDialog, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uiMessage)
	{
	case WM_COMMAND:
		{
			switch (LOWORD(_wParam))
			{
			case ID_APPLY:
				m_bApply = true;
				break;

			default:
				break;
			}
			break;
		}

	default:
		break;
	}

	return (FALSE);
}

CTextField&
CDebugDialog::GetDeltaTickField()
{
	return (*m_pDeltaTick);
}

CTextField&
CDebugDialog::GetMaxFramesField()
{
	return (*m_pMaxFrames);
}

bool
CDebugDialog::IsApplyButtonPressed()
{
	bool bTemp = m_bApply;
	m_bApply = false;

	return (bTemp);
}