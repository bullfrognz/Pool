//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Entity.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Include
#include "Entity.h"

// Static Variables

// Static Function Prototypes

// Implementation
CEntity::CEntity()
: m_fFriction(0.0f)
, m_fMass(0.0f)
, m_bMoving(false)
{
	//Empty
}

CEntity::~CEntity()
{
	Deinitialise();
}

bool
CEntity::Initialise()
{
	return (true);
}

bool
CEntity::Deinitialise()
{
	return (true);
}

void
CEntity::Process(float _fDeltaTick)
{
	const float kfVelocityX = m_Velocity[X];
	const float kfVelocityY = m_Velocity[Y];

	if (kfVelocityX != 0.0f)
	{
		float fDisplacementX = kfVelocityX * _fDeltaTick;
		TranslatePosition(X, fDisplacementX);
	}

	if (kfVelocityY != 0.0f)
	{
		float fDisplacementY = kfVelocityY * _fDeltaTick;
		TranslatePosition(Y, fDisplacementY);
	}

	ProcessFriction(_fDeltaTick, X);

	if (kfVelocityX == 0.0f && kfVelocityY == 0.0f)
	{
		m_bMoving = false;
	}
	else
	{
		m_bMoving = true;
	}
}

void
CEntity::ProcessFriction(float _fDeltaTick, EVectorVariable _eVariable)
{
	CVector3 NormalisedVelocity;
	CVector3::Normalise(m_Velocity, NormalisedVelocity);

	NormalisedVelocity.Scale(m_fFriction * _fDeltaTick);

	CVector3::Minus(m_Velocity, NormalisedVelocity, m_Velocity);

	if (m_Velocity[X] < 1.0f && m_Velocity[X] > -1.0f)
	{
		m_Velocity[X] = 0.0f;
	}
	if (m_Velocity[Y] < 1.0f && m_Velocity[Y] > -1.0f)
	{
		m_Velocity[Y] = 0.0f;
	}
}

void
CEntity::Draw()
{
	//Emtpy
}