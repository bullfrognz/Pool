//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   DialogItem.cpp
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// Framework

// Core

// Content

// This Include
#include "DialogItem.h"

// Static Variables

// Static Function Prototypes

// Implementation

CDialogItem::CDialogItem()
{
	//Empty
}

CDialogItem::~CDialogItem()
{
	//Empty
}

bool
CDialogItem::Initialise(HWND _hParentDialog, int _iItemResourceId)
{
	m_hDialog = _hParentDialog;
	m_iItemResurceId = _iItemResourceId;

	m_hItem = GetDlgItem(m_hDialog, m_iItemResurceId);

	return (true);
}