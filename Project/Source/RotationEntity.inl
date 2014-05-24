//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   RotationEntity.inl
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cassert>

// Local Includes

// This Include

// Static Variables

// Static Function Prototypes

// Implementation

void
CRotationEntity::SetFacingAngle(float m_fAngle)
{
	assert(m_fAngle >= 0.0f && m_fAngle <= 360); //Invalid value

	m_fFacingAngle = m_fAngle;
}

float
CRotationEntity::GetFacingAngle() const
{
	return (m_fFacingAngle);
}

CRotationSprite&
CRotationEntity::GetRotationSprite()
{
	return (*m_pRotationSprite);
}