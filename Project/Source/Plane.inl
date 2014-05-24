//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   ------.inl
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cassert>

// Local Includes

// Framework

// Core

// Content

// Static Variables

// Static Function Prototypes

// Implementation

void
CPlane::SetStartPoint(float _fValueX, float _fValueY, float _fValueZ)
{
	m_StartPoint[X] = _fValueX;
	m_StartPoint[Y] = _fValueY;
	m_StartPoint[Z] = _fValueZ;

	CalculateNormal();
	CaluclateD();
}

void
CPlane::SetEndPoint(float _fValueX, float _fValueY, float _fValueZ)
{
	m_EndPoint[X] = _fValueX;
	m_EndPoint[Y] = _fValueY;
	m_EndPoint[Z] = _fValueZ;

	CalculateNormal();
	CaluclateD();
}

void
CPlane::SetColour(COLORREF _colrefColour)
{
	m_colrefColour = _colrefColour;
}

CVector3
CPlane::GetStartPoint() const
{
	return (m_StartPoint);
}

CVector3
CPlane::GetEndPoint() const
{
	return (m_EndPoint);
}

COLORREF
CPlane::GetColour()
{
	return (m_colrefColour);
}

CVector3
CPlane::GetNormal() const
{
	return (m_Normal);
}

float
CPlane::GetD()
{
	return (m_fD);
}

float
CPlane::GetLength()
{
	return (m_fLength);
}
CVector3
CPlane::GetMiddlePoint()
{
	return (m_MiddlePoint);
}