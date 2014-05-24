//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   AnimatedEntity.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "RotationSprite.h"

// This Include
#include "RotationEntity.h"

// Static Variables

// Static Function Prototypes

// Implementation
CRotationEntity::CRotationEntity()
: m_fFacingAngle(0.0f)
, m_pRotationSprite(0)
{
	m_pRotationSprite = new CRotationSprite;
}

CRotationEntity::~CRotationEntity()
{
	if (m_pRotationSprite != 0)
	{
		delete m_pRotationSprite;
		m_pRotationSprite = 0;
	}
}

bool
CRotationEntity::Initialise(const int _kiSpriteResourceId, const int _kiMaskResourceId,
							int _iFrameWidth, int _NumSpriteAngles, int _iAngleBetweenFrame)
{
	CEntity::Initialise();

	m_pRotationSprite->Initialise(_kiSpriteResourceId, _kiMaskResourceId);
	m_pRotationSprite->SetNumSpriteAngles(_NumSpriteAngles);
	m_pRotationSprite->SetFrameWidth(_iFrameWidth);
	m_pRotationSprite->SetAngleBetweenFrame(_iAngleBetweenFrame);

	return (true);
}

void
CRotationEntity::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);

	m_pRotationSprite->Process(_fDeltaTick);
}

void
CRotationEntity::Draw()
{
	CEntity::Draw();

	m_pRotationSprite->SetPosition(CEntity::m_fPositionX, CEntity::m_fPositionY);
	m_pRotationSprite->SetFacingAngle(m_fFacingAngle);

	m_pRotationSprite->Draw();
}