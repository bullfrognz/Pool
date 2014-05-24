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
#include <cassert>

// Local Includes

// Framework

// Core

// Content

// Static Variables

// Static Function Prototypes

// Implementation

void
CSphere::SetRadius(float _fValue)
{
	assert(_fValue >= 0.0f);

	m_fRadius = _fValue;
}

float
CSphere::GetRadius()
{
	return (m_fRadius);
}

