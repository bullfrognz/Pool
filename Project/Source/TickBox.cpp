//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   TickBox.cpp
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

// This Include
#include "TickBox.h"

// Static Variables

// Static Function Prototypes

// Implementation

CTickBox::CTickBox()
: m_bTicked(false)
{
	//Empty
}

CTickBox::~CTickBox()
{
	//Empty
}

bool
CTickBox::Initialise(HWND _hParentDialog, int _iItemResourceId)
{
	CDialogItem::Initialise(_hParentDialog, _iItemResourceId);

	return (true);
}

bool
CTickBox::Deinitialise()
{
	//Empty

	return (true);
}

void
CTickBox::SetTicked(bool _bTicked)
{
	if (_bTicked == true)
	{
		CheckDlgButton(m_hDialog, m_iItemResurceId, BST_CHECKED);
	}
	else
	{
		CheckDlgButton(m_hDialog, m_iItemResurceId, BST_UNCHECKED);
	}
}

bool
CTickBox::IsTicked()
{
	UINT unitChecked = IsDlgButtonChecked(m_hItem, m_iItemResurceId);

	if (unitChecked == BST_CHECKED)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}