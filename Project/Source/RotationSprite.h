//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   RotationSprite.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_ROTATORSPRITE_H__
#define __IGFEB11_IG220_ROTATORSPRITE_H__

// Library Includes

// Local Includes
#include "Sprite.h"

// Types

// Constants

// Prototypes

class CRotationSprite : public CSprite
{
    // Member Functions
public:
	         CRotationSprite();
	virtual ~CRotationSprite();

	virtual bool Initialise(const int _kiSpriteResourceId, const int _kiMaskResourceId);
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	// Member Inline Functions
	inline void SetNumSpriteAngles(int _iNumAngles);
	inline void SetFacingAngle(int _iAngle);
	inline void SetFacingAngle(float _iAngle);
	inline void SetAngleBetweenFrame(int _iAngle);

	inline int GetNumSpriteAngles() const;
	inline int GetFacingAngle() const;
	inline int GetAngleBetweenFrame() const;

protected:

private:
	CRotationSprite(const CRotationSprite& _kr);
	CRotationSprite& operator= (const CRotationSprite& _kr);

    // Member Variables
public:

protected:

private:
	int m_iAngleBetweenFrame;
	int m_iNumSpriteAngles;
	int m_iFacingAngle;

};

#include "RotationSprite.inl"

#endif // __IGFEB11_IG220_ROTATORSPRITE_H__
