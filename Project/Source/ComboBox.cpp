//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   ComboBox.cpp
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// Framework
#include "Utilities.h"

// Core

// Content

// This Include
#include "ComboBox.h"

// Static Variables

// Static Function Prototypes

// Implementation

CComboBox::CComboBox()
{
	//Empty
}

CComboBox::~CComboBox()
{
	//Empty
}

bool
CComboBox::Initialise(HWND _hParentDialog, int _iItemResourceId)
{
	m_hDialog = _hParentDialog;
	m_iItemResurceId = _iItemResourceId;

	m_hItem = GetDlgItem(m_hDialog, m_iItemResurceId);

	return (true);
}

bool
CComboBox::Deinitialise()
{
	//Empty

	return (true);
}

void
CComboBox::AddItem(const char* _kcpText)
{
	wchar_t* wcpBuffer = 0;

	wcpBuffer = ConvertConstCharToWchart(_kcpText);

	SendMessage(m_hItem, CB_ADDSTRING, 0,
				(LPARAM)wcpBuffer);

	delete wcpBuffer;
	wcpBuffer = 0;
}

void
CComboBox::RemoveItem(const char* _kcpText)
{
	wchar_t* wcpBuffer = 0;

	wcpBuffer = ConvertConstCharToWchart(_kcpText);

	SendMessage(m_hItem, CB_DELETESTRING, 0,
				(LPARAM)wcpBuffer);

	delete wcpBuffer;
	wcpBuffer = 0;
}

const char*
CComboBox::GetSelectedItem()
{
	int iIndex = static_cast<int>(SendMessage(m_hItem,
								  CB_GETCURSEL, 0, 0));

	wchar_t* wcharSelection = new wchar_t[128];

	SendMessage(m_hItem, CB_GETLBTEXT, (WPARAM)iIndex,
		(LPARAM)wcharSelection);

	const char* kcpSelection = ConvertWchartToChar(wcharSelection);

	delete wcharSelection;
	wcharSelection = 0;

	return (kcpSelection);
}