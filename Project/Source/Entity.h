//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Entity.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_ENTITY_H__
#define __IGFEB11_IG220_ENTITY_H__

// Library Includes

// Local Includes
#include "Vector3.h"

// Types

// Constants

// Prototypes

class CEntity
{
    // Member Functions
public:
	         CEntity();
	virtual ~CEntity();

	virtual bool Initialise();
	virtual bool Deinitialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	void ProcessFriction(float _fDeltaTick, EVectorVariable _eVariable);

	// Member inline Functions
	inline void SetPosition(CVector3& _rVector);
	inline void SetPosition(EVectorVariable _eVariable, float _fValue);
	inline void SetPosition(EVectorVariable _eVariable, int _iValue);

	inline void SetVelocity(CVector3& _rVector);
	inline void SetVelocity(EVectorVariable _eVariable, float _fValue);
	inline void SetVelocity(EVectorVariable _eVariable, int _iValue);

	inline void TranslatePosition(EVectorVariable _eVariable, float _fValue);
	inline void TranslatePosition(EVectorVariable _eVariable, int _iValue);

	inline float GetPosition(EVectorVariable _eVariable);
	inline float GetVelocity(EVectorVariable _eVariable);

	inline CVector3 GetPosition();
	inline CVector3 GetVelocity();

	inline void SetMass(float _fValue);
	inline float GetMass();

	inline void SetFriction(float _fValue);
	inline float GetFriction();

	inline bool IsMoving();

protected:

private:
	CEntity(const CEntity& _kr);
	CEntity& operator= (const CEntity& _kr);

    // Member Variables
public:

protected:
	CVector3 m_Velocity;
	CVector3 m_Position;

	float m_fFriction;
	float m_fMass;

	bool m_bMoving;

private:

};

#include "Entity.inl"

#endif // __IGFEB11_IG220_ENTITY_H__
