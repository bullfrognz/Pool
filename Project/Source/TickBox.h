//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   TickBox.h
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_TICKBOX_H__
#define __IGFEB11_IG220_TICKBOX_H__

// Library Includes

// Local Includes
#include "DialogItem.h"

// Types

// Constants

// Prototypes


class CTickBox : public CDialogItem
{
	// Member Functions
public:
	         CTickBox();
	virtual ~CTickBox();

	virtual bool Initialise(HWND _hParentDialog, int _iItemResourceId);
	bool Deinitialise();

	void SetTicked(bool _bTicked);

	bool IsTicked();

protected:

private:

	// Member Variables
public:

protected:

private:
	bool m_bTicked;

};

#endif // __IGFEB11_IG220_TICKBOX_H__