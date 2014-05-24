//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   TextField.h
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_TEXTFIELD_H__
#define __IGFEB11_IG220_TEXTFIELD_H__

// Library Includes

// Local Includes
#include "DialogItem.h"

// Types

// Constants

// Prototypes


class CTextField : public CDialogItem
{
	// Member Functions
public:
	         CTextField();
	virtual ~CTextField();

	virtual bool Initialise(HWND _hParentDialog, int _iItemResourceId);
	bool Deinitialise();

	void SetText(const char* _kcpText);
	void SetText(int _iValue);
	void SetText(float _fValue);

	void GetValue(char* _cpValue);
	void GetValue(int& _iValue);
	void GetValue(float& _fValue);

protected:

private:

	// Member Variables
public:

protected:

private:

};

#endif // __IGFEB11_IG220_TEXTFIELD_H__