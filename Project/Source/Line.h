//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Line.h
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_LINE_H__
#define __IGFEB11_IG220_LINE_H__

// Library Includes

// Local Includes
#include "Entity.h"

// Types

// Constants

// Prototypes
class CPlane;
class CSphere;
class CVector;

class CLine : public CEntity
{
	// Member Functions
public:
	 CLine();
	~CLine();

	bool Initialise();
	bool Deinitialise();
	void Process(float _fDeltaTick);
	void Draw();

	bool IsGoingToCollidePlane(CPlane* _pPlane, float _fDeltaTick, float& _fImpactTime);
	bool IsGoingToCollideSphere(CSphere* _pSphere, float _fDeltaTick, float& _fImpactTime);

	// Inline
	inline void SetDirection(CVector3& _rVector);

	inline CVector3& GetDirection();

protected:

private:

	// Member Variables
public:

protected:
	CVector3 m_Direction;

private:

};

#include "Line.inl"

#endif // __IGFEB11_IG220_LINE_H__