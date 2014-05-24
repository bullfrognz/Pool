//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   DebugDialog.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_DEBUGDIALOG_H__
#define __IGFEB11_IG120_DEBUGDIALOG_H__

// Library Includes
#include <windows.h>
#include <map>

// Local Includes

// Types

// Constants

// Prototypes

class CDialog
{
    // Member Functions
public:
	         CDialog();
	virtual ~CDialog();

	virtual bool Initialise(HINSTANCE _hInstance, HWND _hWindow , int _iResourceId);
	virtual bool Deinitialise();

	virtual BOOL CALLBACK DialogProc(HWND _hDialog, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam) = 0;

	// Member Static Functions
	static BOOL CALLBACK DefaultDialogProc(HWND _hDialog, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam);

	// Member inline Functions
	inline void SetDisplay(bool _bDisplay);

	inline HWND GetHandle() const;
	inline bool IsDisplaying() const;

	static inline std::map<HWND, CDialog*>& GetDialogs();

protected:

private:
	CDialog(const CDialog& _kr);
	CDialog& operator= (const CDialog& _kr);

    // Member Variables
public:

protected:
	HINSTANCE m_hInstance;

	HWND m_hWindow;
	HWND m_hDialog;

	int m_iDialogResourceId;

	bool m_bDisplaying;

	// Member Static Variables
	static std::map<HWND, CDialog*> s_mapDialogs;

private:

};

#include "Dialog.inl"

#endif // __IGFEB11_IG120_DEBUGDIALOG_H__
