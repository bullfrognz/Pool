//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Ball.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// Framework
#include "Sprite.h"

// Core

// Scene

// This Include
#include "Ball.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBall::CBall()
: m_pSprite(0)
, m_bPocketed(false)
, m_eBallType(BALLTYPE_INVALID)
{
	//Empty
}

CBall::~CBall()
{
	Deinitialise();
}

bool
CBall::Initialise(const int _kiSpriteResourceId, const int _kiMaskResourceId)
{
	CSphere::Initialise();
	
	m_pSprite = new CSprite();
	m_pSprite->Initialise(_kiSpriteResourceId, _kiMaskResourceId);

	return (true);
}

bool
CBall::Deinitialise()
{
	CSphere::Deinitialise();

	delete m_pSprite;
	m_pSprite = 0;

	return (true);
}

void
CBall::Process(float _fDeltaTick)
{
	CSphere::Process(_fDeltaTick);
	m_pSprite->Process(_fDeltaTick);
}

void
CBall::Draw()
{
	CSphere::Draw();
	m_pSprite->SetPosition(CEntity::m_Position[X], CEntity::m_Position[Y]);
	m_pSprite->Draw();
}