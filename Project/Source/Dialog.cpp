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
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <windows.h>

// Local Includes
#include "Resource.h"

// Framework
#include "Utilities.h"

// Core

// Content

// This Include
#include "Dialog.h"

// Static Variables
std::map<HWND, CDialog*> CDialog::s_mapDialogs;

// Static Function Prototypes
BOOL CALLBACK DialogProcWrapper(HWND _hDialog, UINT _Message, WPARAM _wParam, LPARAM _lParam);

// Implementation
CDialog* g_DialogWrapperInstance = 0;

CDialog::CDialog()
: m_hInstance(0)
, m_hWindow(0)
, m_hDialog(0)
, m_iDialogResourceId(0)
, m_bDisplaying(false)
{
	g_DialogWrapperInstance = this;
}

CDialog::~CDialog()
{
	Deinitialise();

	DestroyWindow(m_hDialog);
}

bool
CDialog::Initialise(HINSTANCE _hInstance, HWND _hWindow , int _iResourceId)
{
	m_hInstance = _hInstance;
	m_hWindow = _hWindow;
	m_iDialogResourceId = _iResourceId;

	m_hDialog = CreateDialog(m_hInstance, MAKEINTRESOURCE(m_iDialogResourceId), m_hWindow, DialogProcWrapper);

	s_mapDialogs.insert( std::pair<HWND, CDialog*>(m_hDialog, this) );
	 
	return (true);
}

bool
CDialog::Deinitialise()
{
	std::map<HWND, CDialog*>::iterator Iter;

	Iter = s_mapDialogs.begin();

	while (Iter != s_mapDialogs.end())
	{
		if (Iter->second == this)
		{
			s_mapDialogs.erase(Iter);
			break;
		}
	}

	return (true);
}

BOOL CALLBACK
CDialog::DefaultDialogProc(HWND _hDialog, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam)
{
	std::map<HWND, CDialog*>::iterator Iter;

	Iter = s_mapDialogs.find(_hDialog);

	CDialog* pDialog = 0;
	if (Iter != s_mapDialogs.end())
	{
		pDialog = (*Iter).second;
	}
	else
	{
		return (FALSE);
	}

	switch (_uiMessage)
	{
	case WM_INITDIALOG:
		{
		}

	case WM_COMMAND:
		switch (LOWORD(_wParam))
		{
		case IDOK:
			pDialog->SetDisplay(false);
			break;

		case IDCLOSE:
			pDialog->SetDisplay(false);
			break;

		default:
			break;
		}
		break;

	case WM_CLOSE:
		pDialog->SetDisplay(false);
		return (TRUE);
		break;

	default:
		break;
	}

	return (pDialog->DialogProc(_hDialog, _uiMessage, _wParam, _lParam));
}




BOOL CALLBACK
DialogProcWrapper(HWND _hDialog, UINT _Message, WPARAM _wParam, LPARAM _lParam)
{
	return (CDialog::DefaultDialogProc(_hDialog, _Message, _wParam, _lParam));
}