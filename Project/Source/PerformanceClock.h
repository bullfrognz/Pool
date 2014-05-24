//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   PerformanceClock.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_PERFORMANCECLOCK_H__
#define __IGFEB11_IG220_PERFORMANCECLOCK_H__

// Library Includes

// Local Includes
	//Framework
	#include "Clock.h"
	//Core
	//Game

// Types

// Constants

// Prototypes


class CPerformanceClock : public CClock
{
    // Member Functions
public:
	 CPerformanceClock();
	~CPerformanceClock();

	virtual bool Initialise();
	virtual bool Deintiialise();
	virtual void Process();
	virtual void Draw();

	

protected:

private:
	CPerformanceClock(const CPerformanceClock& _kr);
	CPerformanceClock& operator= (const CPerformanceClock& _kr);

    // Member Variables
public:

protected:

private:
	// High performance member data.
	__int64 m_i64CurrentTime;
	__int64 m_i64LastTime;
	__int64 m_i64CountsPerSecond;
	double m_dPerfCounterTimeScale;

};

#endif // __IGFEB11_IG220_PERFORMANCECLOCK_H__
