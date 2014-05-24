//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Sphere.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_SPHERE_H__
#define __IGFEB11_IG220_SPHERE_H__

// Library Includes

// Local Includes
#include "Entity.h"

// Types

// Constants

// Prototypes
class CPlane;

class CSphere : public CEntity
{
    // Member Functions
public:
	         CSphere();
	virtual ~CSphere();

	virtual bool Initialise();
	virtual bool Deinitialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	bool IsGoingToCollidePlane(CPlane* _pPlane, float _fDeltaTick, float& _fImpactTime);
	bool IsGoingToCollideSphere(CSphere* _pSphere, float _fDeltaTick, float& _fImpactTime);

	void ReflectAgainstPlane(CPlane* _pPlane);
	void ReflectAgainstSphere(CSphere* _pSphere2);

	// Member inline Functions
	inline void SetRadius(float _fValue);

	inline float GetRadius();

protected:

private:
	CSphere(const CSphere& _kr);
	CSphere& operator= (const CSphere& _kr);

    // Member Variables
public:

protected:
	float m_fRadius;

private:

};

#include "Sphere.inl"

#endif // __IGFEB11_IG220_SPHERE_H__
