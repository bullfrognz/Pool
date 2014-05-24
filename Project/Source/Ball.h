//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Ball.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_BALL_H__
#define __IGFEB11_IG220_BALL_H__

// Library Includes

// Local Includes
#include "Sphere.h"
#include "GameDefines.h"

// Types

// Constants

// Prototypes
class CSprite;

class CBall : public CSphere
{
    // Member Functions
public:
	         CBall();
	virtual ~CBall();

	virtual bool Initialise(const int _kiSpriteResourceId, const int _kiMaskResourceId);
	virtual bool Deinitialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	// Inline
	inline void SetPocketed(bool _bPocketed);
	inline void SetBallType(EBallType _eBallType);

	inline bool IsPocketed();
	inline EBallType GetBallType();

protected:

private:
	CBall(const CBall& _kr);
	CBall& operator= (const CBall& _kr);

    // Member Variables
public:

protected:
	CSprite* m_pSprite;
	EBallType m_eBallType;

	bool m_bPocketed;

private:

};

#include "Ball.inl"

#endif // __IGFEB11_IG220_BALL_H__
