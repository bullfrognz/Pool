//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Clock.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_CLOCK_H__
#define __IGFEB11_IG220_CLOCK_H__

// Library Includes
#include <windows.h>
#include <windowsx.h>

// Local Includes

// Types

// Constants

// Prototypes
class CText;

class CClock
{
	// Member Functions
public:
	CClock();
	virtual ~CClock();

	virtual bool Initialise();
	virtual bool Deinitialise();
	virtual void Process();
	virtual void Draw();

	void ProcessFPSCap();
	void ProcessFPSText();

	float GetDeltaTick();

	void SetMaxFrames(float _fMaxFrames);
	float GetMaxFrames();

	void SetStaticDeltaTick(float _fDeltaTick);
	float GetStaticDeltatick();

protected:

private:
	CClock(const CClock& _kr);
	CClock& operator=(const CClock& _kr);

	// Member Variables
public:

protected:
	CText* m_pFpsText;
	char* m_cpFpsMessage;

	float m_fDeltaTime;

	float m_fTimeElapsed;
	float m_fLastTime;
	float m_fCurrentTime;

	int m_iFrameCount;

	float m_fSetDeltaTick;
	float m_fMinFrames;
	float m_fMaxDeltaTick;

	float m_fMaxFrames;

private:

};

#endif // __IGFEB11_IG220_CLOCK_H__

