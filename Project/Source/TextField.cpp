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
#include <iostream>

// Local Includes

// Framework
#include "Utilities.h"

// Core

// Content

// This Include
#include "TextField.h"

// Static Variables

// Static Function Prototypes

// Implementation

CTextField::CTextField()
{
	//Empty
}

CTextField::~CTextField()
{
	//Empty
}

bool
CTextField::Initialise(HWND _hParentDialog, int _iItemResourceId)
{
	CDialogItem::Initialise(_hParentDialog, _iItemResourceId);

	return (true);
}

bool
CTextField::Deinitialise()
{
	//Empty

	return (true);
}

void
CTextField::SetText(const char* _kcpText)
{
	wchar_t* wcpBuffer = 0;

	wcpBuffer = ConvertConstCharToWchart(_kcpText);
	SetWindowText(m_hItem, wcpBuffer);

	delete wcpBuffer;
	wcpBuffer = 0;
}

void
CTextField::SetText(int _iValue)
{
	char* cpBuffer = new char[128];
	sprintf_s(cpBuffer, 128, "%d", _iValue);

	SetText(cpBuffer);

	delete cpBuffer;
	cpBuffer = 0;
}

void
CTextField::SetText(float _fValue)
{
	char* cpBuffer = new char[128];
	sprintf_s(cpBuffer, 128, "%f", _fValue);

	SetText(cpBuffer);

	delete cpBuffer;
	cpBuffer = 0;
}

void 
CTextField::GetValue(char* _cpValue)
{
	wchar_t* wcpBuffer = new wchar_t[256];
	
	GetWindowText(m_hItem, wcpBuffer, 256);
	_cpValue = ConvertWchartToChar(wcpBuffer);

	delete wcpBuffer;
	wcpBuffer = 0;
}

void
CTextField::GetValue(int& _iValue)
{
	wchar_t* wcpBuffer = new wchar_t[256];
	
	GetWindowText(m_hItem, wcpBuffer, 256);

	_iValue = static_cast<int>(_wtoi(wcpBuffer));

	delete wcpBuffer;
	wcpBuffer = 0;
}

void
CTextField::GetValue(float& _fValue)
{
	wchar_t* wcpBuffer = new wchar_t[256];
	
	GetWindowText(m_hItem, wcpBuffer, 256);

	_fValue = static_cast<float>(_wtof(wcpBuffer));

	delete wcpBuffer;
	wcpBuffer = 0;
}