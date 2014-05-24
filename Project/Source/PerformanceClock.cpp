//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   PerformanceClock.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// Framework

// Core

// Scene

// This Include
#include "PerformanceClock.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPerformanceClock::CPerformanceClock()
: m_i64CurrentTime(0) 
, m_i64LastTime(0)
, m_i64CountsPerSecond(0)
, m_dPerfCounterTimeScale(0.0)
{
	//Empty
}

CPerformanceClock::~CPerformanceClock()
{
	//Empty
}


bool
CPerformanceClock::Initialise()
{
	CClock::Initialise();

	QueryPerformanceFrequency((LARGE_INTEGER*)&m_i64CountsPerSecond);
	m_dPerfCounterTimeScale = 1.0 / (double)(m_i64CountsPerSecond);

	return (true);
}

bool
CPerformanceClock::Deintiialise()
{
	return (true);
}

void
CPerformanceClock::Process()
{
	m_i64LastTime = m_i64CurrentTime;
		
	QueryPerformanceCounter((LARGE_INTEGER*)&m_i64CurrentTime);

	if(m_i64LastTime == 0)
	{
		m_i64LastTime = m_i64CurrentTime;
	}

	m_fDeltaTime = (m_i64CurrentTime - m_i64LastTime) * static_cast<float>(m_dPerfCounterTimeScale);

	const float MinDeltaTick = 1.0f / m_fMaxFrames; // Minium the delta tick can be for the max frames
	float StartTime = 0.0f;
	while (m_fDeltaTime < MinDeltaTick)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_i64CurrentTime);
		m_fDeltaTime = (m_i64CurrentTime - m_i64LastTime) * static_cast<float>(m_dPerfCounterTimeScale);
	}

	m_fTimeElapsed += m_fDeltaTime;

	CClock::ProcessFPSText();
}


void
CPerformanceClock::Draw()
{
	CClock::Draw();
}