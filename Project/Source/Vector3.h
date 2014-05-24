//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Vector3.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_VECTOR3_H__
#define __IGFEB11_IG220_VECTOR3_H__

// Library Includes

// Local Includes

// Types
enum EVectorVariable
{
	X = 1,
	Y = 2,
	Z = 3,
};

// Constants

// Prototypes


class CVector3
{
    // Member Functions
public:
	 CVector3();
	 CVector3(float _fX, float _fY, float _fZ);
	 //CVector3(CVector3& _krVector);
	~CVector3();

	void Scale(float _fValue);
	void Normalise();
	void Invert();
	void Zero();

	// Member inline Functions

	// Memer Static Functions
	static float GetMagnitude(CVector3& _krVector);
	static float Dot(CVector3& _krVector1, CVector3& _krVector2);
	static CVector3& Cross(CVector3& _krVector1, CVector3& _krVector2, CVector3& _rVectorResult);
	static CVector3& Add(CVector3& _krVector1, CVector3& _krVector2, CVector3& _rVectorResult);
	static CVector3& Minus(CVector3& _krVector1, CVector3& _krVector2, CVector3& _rVectorResult);
	static CVector3& Multiply(CVector3& _krVector1, CVector3& _krVector2, CVector3& _rVectorResult);

	static CVector3& Scale(CVector3& _krVector, float _fValue, CVector3& _rVectorResult);
	static CVector3& Normalise(CVector3& _krVector, CVector3& _rVectorResult);

	// Member Operator Overload Functions
	float& operator [] (EVectorVariable _eVariable);
	float& operator [] (EVectorVariable _eVariable) const;
	float& operator [] (int _iIndex);
	float& operator [] (int _iIndex) const;
	void operator = (CVector3& _rVector);

protected:

private:
	 

    // Member Variables
public:

protected:

private:
	float m_fX;
	float m_fY;
	float m_fZ;
	
};

#include "Vector3.inl"

#endif // __IGFEB11_IG220_VECTOR3_H__
