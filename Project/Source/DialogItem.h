//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   DialogItem.h
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_DIALOGITEM_H__
#define __IGFEB11_IG220_DIALOGITEM_H__

// Library Includes
#include <windows.h>

// Local Includes

// Types

// Constants

// Prototypes


class CDialogItem
{
	// Member Functions
public:
	         CDialogItem();
	virtual ~CDialogItem();

	virtual bool Initialise(HWND _hParentDialog, int _iItemResourceId);

	// Member inline Functions
	inline void SetDisabled(bool _bDisabled);

	inline bool IsDisabled();

protected:

private:

	// Member Variables
public:

protected:
	HWND m_hDialog;
	HWND m_hItem;

	int m_iItemResurceId;
	
	bool m_bDisabled;

private:

};

#include "DialogItem.inl"

#endif // __IGFEB11_IG220_DIALOGITEM_H__