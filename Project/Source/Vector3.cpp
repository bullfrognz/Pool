//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Vector3.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cassert>
#include <cmath>

// Local Includes

// Framework

// Core

// Scene

// This Include
#include "Vector3.h"

// Static Variables

// Static Function Prototypes

// Implementation

CVector3::CVector3()
: m_fX(0.0f)
, m_fY(0.0f)
, m_fZ(0.0f)
{
	//Empty
}

CVector3::CVector3(float _fX, float _fY, float _fZ)
: m_fX(_fX)
, m_fY(_fY)
, m_fZ(_fZ)
{
	//Empty
}

CVector3::~CVector3()
{
	//Empty
}

void
CVector3::Invert()
{
	m_fX *= -1;
	m_fY *= -1;
	m_fZ *= -1;
}

void
CVector3::Zero()
{
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_fZ = 0.0f;
}

float
CVector3::Dot(CVector3& _krVector1, CVector3& _krVector2)
{
	float fResult = 0.0f;

	fResult  = _krVector1[X] * _krVector2[X];
	fResult += _krVector1[Y] * _krVector2[Y];
	fResult += _krVector1[Z] * _krVector2[Z];

	return (fResult);
}

CVector3&
CVector3::Cross( CVector3& _krVector1,  CVector3& _krVector2, CVector3& _rVectorResult)
{
	_rVectorResult[X] = (_krVector1[Y] * _krVector2[Z]) - (_krVector1[Z] * _krVector2[Y]);
	_rVectorResult[Y] = (_krVector1[Z] * _krVector2[X]) - (_krVector1[X] * _krVector2[Z]);
	_rVectorResult[Z] = (_krVector1[X] * _krVector2[Y]) - (_krVector1[Y] * _krVector2[X]);

	return (_rVectorResult);
}

CVector3&
CVector3::Add( CVector3& _krVector1,  CVector3& _krVector2, CVector3& _rVectorResult)
{
	_rVectorResult[X] = _krVector1[X] + _krVector2[X];
	_rVectorResult[Y] = _krVector1[Y] + _krVector2[Y];
	_rVectorResult[Z] = _krVector1[Z] + _krVector2[Z];

	return (_rVectorResult);
}

CVector3&
CVector3::Minus( CVector3& _krVector1,  CVector3& _krVector2, CVector3& _rVectorResult)
{
	_rVectorResult[X] = _krVector1[X] - _krVector2[X];
	_rVectorResult[Y] = _krVector1[Y] - _krVector2[Y];
	_rVectorResult[Z] = _krVector1[Z] - _krVector2[Z];

	return (_rVectorResult);
}

CVector3&
CVector3::Multiply( CVector3& _krVector1,  CVector3& _krVector2, CVector3& _rVectorResult)
{
	_rVectorResult[X] = _krVector1[X] * _krVector2[X];
	_rVectorResult[Y] = _krVector1[Y] * _krVector2[Y];
	_rVectorResult[Z] = _krVector1[Z] * _krVector2[Z];

	return (_rVectorResult);
}

void
CVector3::Scale(float _fValue)
{
	m_fX *= _fValue;
	m_fY *= _fValue;
	m_fZ *= _fValue;
}

void
CVector3::Normalise()
{
	float fUnit = sqrt(m_fX*m_fX + m_fY*m_fY + m_fZ*m_fZ);

	if (fUnit != 0.0f)
	{
		m_fX /= fUnit;
		m_fY /= fUnit;
		m_fZ /= fUnit;
	}
}

float
CVector3::GetMagnitude(CVector3& _krVector)
{
	float fX = _krVector[X];
	float fY = _krVector[Y];
	float fZ = _krVector[Z];

	float fMagnitude = 0.0f;
	fMagnitude = sqrt(fX*fX + fY*fY + fZ*fZ);

	return (fMagnitude);
}

CVector3&
CVector3::Scale(CVector3& _krVector, float _fValue, CVector3& _rVectorResult)
{
	float fX = _krVector[X];
	float fY = _krVector[Y];
	float fZ = _krVector[Z];

	fX *= _fValue;
	fY *= _fValue;
	fZ *= _fValue;

	_rVectorResult[X] = fX;
	_rVectorResult[Y] = fY;
	_rVectorResult[Z] = fZ;

	return (_rVectorResult);
}

CVector3&
CVector3::Normalise(CVector3& _krVector, CVector3& _rVectorResult)
{
	float fX = _krVector[X];
	float fY = _krVector[Y];
	float fZ = _krVector[Z];

	float fUnit = sqrt(fX*fX + fY*fY + fZ*fZ);
	if (fUnit != 0.0f)
	{
		fX /= fUnit;
		fY /= fUnit;
		fZ /= fUnit;
	}

	_rVectorResult[X] = fX;
	_rVectorResult[Y] = fY;
	_rVectorResult[Z] = fZ;

	return (_rVectorResult);
}

float&
CVector3::operator [] (EVectorVariable _eVariable)
{
	if (_eVariable == X)
	{
		return (m_fX);
	}
	else if (_eVariable == Y)
	{
		return (m_fY);
	}
	else
	{
		return (m_fZ);
	}
}

float&
CVector3::operator [] (int _iIndex)
{
	if (_iIndex == 1)
	{
		return (m_fX);
	}
	else if (_iIndex == 2)
	{
		return (m_fY);
	}
	else if (_iIndex == 3)
	{
		return (m_fZ);
	}
	else
	{
		assert(false); //Unknown value
		return (m_fZ);
	}
}

void
CVector3::operator = (CVector3& _rVector)
{
	m_fX = _rVector[X];
	m_fY = _rVector[Y];
	m_fZ = _rVector[Z];
}