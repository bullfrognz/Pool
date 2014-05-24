//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   ComboBox.h
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_COMBOBOX_H__
#define __IGFEB11_IG220_COMBOBOX_H__

// Library Includes

// Local Includes
#include "DialogItem.h"

// Types

// Constants

// Prototypes


class CComboBox : public CDialogItem
{
	// Member Functions
public:
	         CComboBox();
	virtual ~CComboBox();

	virtual bool Initialise(HWND _hParentDialog, int _iItemResourceId);
	bool Deinitialise();

	void AddItem(const char* _kcpText);
	void RemoveItem(const char* _kcpText);
	const char* GetSelectedItem();

protected:

private:

	// Member Variables
public:

protected:

private:

};

#endif // __IGFEB11_IG220_COMBOBOX_H__