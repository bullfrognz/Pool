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
CLine::SetDirection(CVector3& _rVector)
{
	m_Direction = _rVector;
}

CVector3&
CLine::GetDirection()
{
	return (m_Direction);
}