//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   RotationSprite.inl
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
CRotationSprite::SetNumSpriteAngles(int _iNumAngles)
{
	assert((_iNumAngles % 2) == 0); //Number of angles must be even.

	m_iNumSpriteAngles = _iNumAngles;
}

void
CRotationSprite::SetFacingAngle(int _iAngle)
{
	if (_iAngle < 0)
	{
		_iAngle = 0;
	}

	m_iFacingAngle = _iAngle;
}

void
CRotationSprite::SetFacingAngle(float _iAngle)
{
	SetFacingAngle(static_cast<int>(_iAngle));
}

void
CRotationSprite::SetAngleBetweenFrame(int _iAngle)
{
	assert(_iAngle > 0); //Invalid value.

	m_iAngleBetweenFrame = _iAngle;
}

int
CRotationSprite::GetNumSpriteAngles() const
{
	return (m_iNumSpriteAngles);
}

int
CRotationSprite::GetFacingAngle() const
{
	return (m_iFacingAngle);
}

int
CRotationSprite::GetAngleBetweenFrame() const
{
	return (m_iAngleBetweenFrame);
}