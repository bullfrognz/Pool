//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   ------.inl
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
CBall::SetPocketed(bool _bPocketed)
{
	m_bPocketed = _bPocketed;
}

void
CBall::SetBallType(EBallType _eBallType)
{
	m_eBallType = _eBallType;
}

bool
CBall::IsPocketed()
{
	return (m_bPocketed);
}

EBallType
CBall::GetBallType()
{
	return (m_eBallType);
}