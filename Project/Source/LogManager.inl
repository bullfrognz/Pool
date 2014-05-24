//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   LogManager.inl
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// Framework

// Core

// Content

// This Include

// Static Variables

// Static Function Prototypes

// Implementation

void
CLogManager::WriteVariable(const char* _kcpTitle, int _piValue)
{
	sprintf_s(m_cpTextBuffer, s_kiTextBufferSize, "%s: %d", _kcpTitle, _piValue);
	Write(m_cpTextBuffer);
}

void
CLogManager::WriteVariable(const char* _kcpTitle, float _pfValue)
{
	sprintf_s(m_cpTextBuffer, s_kiTextBufferSize, "%s: %f", _kcpTitle, _pfValue);
	
	Write(m_cpTextBuffer);
}

void
CLogManager::WriteVariable(const char* _kcpTitle, char _pcValue)
{
	sprintf_s(m_cpTextBuffer, s_kiTextBufferSize, "%s: %d", _kcpTitle, _pcValue);
	
	Write(m_cpTextBuffer);
}

void
CLogManager::WriteVariable(const char* _kcpTitle, bool _pbValue)
{
	sprintf_s(m_cpTextBuffer, s_kiTextBufferSize, "%s: %d", _kcpTitle, _pbValue);
	
	Write(m_cpTextBuffer);
}
