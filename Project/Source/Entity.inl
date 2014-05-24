//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Entity.inl
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cassert>

// Local Includes
#include "Vector3.h"

// This Include

// Static Variables

// Static Function Prototypes

// Implementation

void
CEntity::SetPosition(CVector3& _rVector)
{
	SetPosition(X, _rVector[X]);
	SetPosition(Y, _rVector[Y]);
	SetPosition(Z, _rVector[Z]);
}

void
CEntity::SetPosition(EVectorVariable _eVariable, float _fValue)
{
	m_Position[_eVariable] = _fValue;
}

void
CEntity::SetPosition(EVectorVariable _eVariable, int _iValue)
{
	SetPosition(_eVariable, static_cast<float>(_iValue));
}

void
CEntity::TranslatePosition(EVectorVariable _eVariable, float _fValue)
{
	SetPosition(_eVariable, m_Position[_eVariable] + _fValue);
}

void
CEntity::TranslatePosition(EVectorVariable _eVariable, int _iValue)
{
	TranslatePosition(_eVariable, static_cast<float>(_iValue));
}

void
CEntity::SetVelocity(CVector3& _rVector)
{
	SetVelocity(X, _rVector[X]);
	SetVelocity(Y, _rVector[Y]);
	SetVelocity(Z, _rVector[Z]);
}

void
CEntity::SetVelocity(EVectorVariable _eVariable, float _fValue)
{
	m_Velocity[_eVariable] = _fValue;
}

void
CEntity::SetVelocity(EVectorVariable _eVariable, int _iValue)
{
	SetVelocity(_eVariable, static_cast<float>(_iValue));
}

float
CEntity::GetPosition(EVectorVariable _eVariable)
{
	return (m_Position[_eVariable]);
}

float
CEntity::GetVelocity(EVectorVariable _eVariable)
{
	return (m_Velocity[_eVariable]);
}

CVector3
CEntity::GetPosition()
{
	return (m_Position);
}

CVector3
CEntity::GetVelocity()
{
	return (m_Velocity);
}

void
CEntity::SetMass(float _fValue)
{
	assert(_fValue >= 0.0f);

	m_fMass = _fValue;
}

float
CEntity::GetMass()
{
	return (m_fMass);
}

void
CEntity::SetFriction(float _fValue)
{
	assert(_fValue >= 0.0f);

	m_fFriction = _fValue;
}

float
CEntity::GetFriction()
{
	return (m_fFriction);
}

bool
CEntity::IsMoving()
{
	return (m_bMoving);
}