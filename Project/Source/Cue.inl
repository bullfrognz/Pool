//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Cue.inl
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// Framework

// Core

// Content

// Static Variables

// Static Function Prototypes

// Implementation

void
CCue::SetDisplay(bool _bDisplay)
{
	m_bDisplay = _bDisplay; 
}

void
CCue::SetOrigin(CVector3& _rOrigin)
{
	m_Origin = _rOrigin;
}

bool
CCue::IsDisplaying()
{
	return (m_bDisplay);
}

CVector3&
CCue::GetOrigin()
{
	return (m_Origin);
}

CLine&
CCue::GetLine()
{
	return (*m_pDirectionLine);
}

CLine&
CCue::GetReflectLine()
{
	return (*m_pReboundLine);
}

CBall&
CCue::GetDummyBall()
{
	return (*m_pDummyBall);
}