//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   RotationSprite.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Include
#include "RotationSprite.h"

// Static Variables

// Static Function Prototypes

// Implementation

CRotationSprite::CRotationSprite()
: m_iAngleBetweenFrame(0)
, m_iNumSpriteAngles(0)
, m_iFacingAngle(0)
{
	//Empty
}

CRotationSprite::~CRotationSprite()
{
	//Emtpy
}

bool
CRotationSprite::Initialise(const int _kiSpriteResourceId, const int _kiMaskResourceId)
{
	CSprite::Initialise(_kiSpriteResourceId, _kiMaskResourceId);

	return (true);
}

void
CRotationSprite::Process(float _fDeltaTick)
{
	CSprite::Process(_fDeltaTick);
}

void
CRotationSprite::Draw()
{
	int iFrameWidth = 0;
	iFrameWidth = CSprite::GetFrameWidth();

	int iFacingFrame  = 0;

	if (m_iFacingAngle != 0)
	{
		iFacingFrame = (m_iFacingAngle / m_iAngleBetweenFrame);
	}

 	CSprite::SetFrameStartX(iFrameWidth * iFacingFrame);

	CSprite::Draw();
}