//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   LogGameWindow.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_LogGameWindow_H__
#define __IGFEB11_IG220_LogGameWindow_H__

// Library Includes

// Local Includes
#include "LogManager.h"

// Types

// Constants

// Prototypes
class CText;

class CLogGameWindow : public ILogTarget
{
    // Member Functions
public:
	         CLogGameWindow();
	virtual ~CLogGameWindow();

	virtual void Initialise();
	virtual void Deinitialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	virtual void Write(const char* _pcMessage);

protected:

private:
	CLogGameWindow(const CLogGameWindow& _kr);
	CLogGameWindow& operator= (const CLogGameWindow& _kr);

    // Member Variables
public:

protected:

private:
	static const int s_kiMaxLogText = 25;
	CText* m_pLogText[s_kiMaxLogText];

	int m_iNumActiveText;

};

#endif // __IGFEB11_IG220_LogGameWindow_H__
