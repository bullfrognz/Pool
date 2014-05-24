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
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_DEBUGDILOG_H__
#define __IGFEB11_IG220_DEBUGDILOG_H__

// Library Includes
#include <windows.h>

// Local Includes
#include "Dialog.h"

// Types

// Constants

// Prototypes
class CTickBox;
class CTextField;

class CDebugDialog : public CDialog
{
	// Member Functions
public:
	         CDebugDialog();
	virtual ~CDebugDialog();

	virtual bool Initialise(HINSTANCE _hInstance, HWND _hWindow , int _iResourceId);
	virtual bool Deinitialise();

	virtual BOOL CALLBACK DialogProc(HWND _hDialog, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam);

	CTextField& GetDeltaTickField();
	CTextField& GetMaxFramesField();

	bool IsApplyButtonPressed();

	// Member inline Functions

protected:

private:

	// Member Variables
public:

protected:

private:
	CTextField* m_pDeltaTick;
	CTextField* m_pMaxFrames;

	bool m_bApply;

};

#endif // __IGFEB11_IG220_DEBUGDILOG_H__