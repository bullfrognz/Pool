//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   MessageTarget.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_MESSAGETARGET_H__
#define __IGFEB11_IG220_MESSAGETARGET_H__

// Library Includes
#include <windows.h>

// Local Includes

// Types

// Constants

// Prototypes
enum EKeyCode;

class IMessageTarget
{
    // Member Functions
public:
	IMessageTarget() {};
	virtual ~IMessageTarget() {};

	virtual void HandleMessage(EKeyCode _EKeyCode, WPARAM _wParam, LPARAM _lParam) = 0;

protected:

private:
	IMessageTarget(const IMessageTarget& _kr);
	IMessageTarget& operator= (const IMessageTarget& _kr);

    // Member Variables
public:

protected:

private:

};

#endif // __IGFEB11_IG220_MESSAGETARGET_H__
