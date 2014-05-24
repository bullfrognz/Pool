//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   RotationEntity.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_ROTATIONENTITY_H__
#define __IGFEB11_IG220_ROTATIONENTITY_H__

// Library Includes

// Local Includes
#include "Entity.h"

// Types

// Constants

// Prototypes
class CRotationSprite;

class CRotationEntity : public CEntity
{
    // Member Functions
public:
	         CRotationEntity();
	virtual ~CRotationEntity();

	virtual bool Initialise(const int _kiSpriteResourceId, const int _kiMaskResourceId, int _iFrameWidth,
							int _iNumSpriteAngles, int _iAngleBetweenFrame);
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	// Member Inline Functions
	inline void SetFacingAngle(float m_fAngle);

	inline float GetFacingAngle() const;

	inline CRotationSprite& GetRotationSprite();

protected:

private:
	CRotationEntity(const CRotationEntity& _kr);
	CRotationEntity& operator= (const CRotationEntity& _kr);

    // Member Variables
public:

protected:
	float m_fFacingAngle;

	CRotationSprite* m_pRotationSprite;

private:

};

#include "RotationEntity.inl"

#endif // __IGFEB11_IG220_ANIMATEDENTITY_H__
