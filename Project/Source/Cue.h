//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Cue.h
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_CUE_H__
#define __IGFEB11_IG220_CUE_H__

// Library Includes
#include <windows.h>

// Local Includes
#include "Line.h"

// Types

// Constants

// Prototypes
class CRotationSprite;
class CLogManager;
class CVector;
class CBall;

class CCue : public CLine
{
	// Member Functions
public:
	 CCue();
	~CCue();

	bool Initialise();
	bool Deinitialise();
	void Process(float _fDeltaTick);
	void Draw();

	void CalculateFacingAngle();

	// Inline
	inline void SetDisplay(bool _bDisplay);
	inline void SetOrigin(CVector3& _rOrigin);

	inline bool IsDisplaying();
	inline CVector3& GetOrigin();

	inline CLine& GetLine();
	inline CLine& GetReflectLine();
	inline CBall& GetDummyBall();

protected:

private:

	// Member Variables
public:

protected:

private:
	CVector3 m_Origin;

	CRotationSprite* m_pCueSprite;
	CLine* m_pDirectionLine;
	CLine* m_pReboundLine;

	CBall* m_pDummyBall;

	bool m_bDisplay;

};

#include "Cue.inl"

#endif // __IGFEB11_IG220_CUE_H__