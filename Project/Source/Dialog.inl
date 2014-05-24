//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Dialog.inl
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <windows.h>

// Local Includes

// Framework

// Core

// Content

// Static Variables

// Static Function Prototypes

// Implementation

void
CDialog::SetDisplay(bool _bDisplay)
{
	if (_bDisplay == true)
	{
		ShowWindow(m_hDialog, SW_SHOW);
	}
	else
	{
		ShowWindow(m_hDialog, SW_HIDE);
	}

	m_bDisplaying = _bDisplay;
}

HWND
CDialog::GetHandle() const
{
	return (m_hDialog);
}

bool
CDialog::IsDisplaying() const
{
	return (m_bDisplaying);
}