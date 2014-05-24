//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Line.cpp
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cmath>

// Local Includes

// Framework

// Core
#include "Sphere.h"
#include "Plane.h"

// Content

// This Include
#include "Line.h"

// Static Variables

// Static Function Prototypes

// Implementation

CLine::CLine()
{
	//Empty
}

CLine::~CLine()
{
	//Empty
}

bool
CLine::Initialise()
{
	//Empty

	return (true);
}

bool
CLine::Deinitialise()
{
	//Empty

	return (true);
}

void
CLine::Process(float _fDeltaTick)
{
	//Empty
}

void
CLine::Draw()
{
	//Emtpy
}

bool
CLine::IsGoingToCollidePlane(CPlane* _pPlane, float _fDeltaTick, float& _fImpactTime)
{
	CVector3 LinePosition  = CEntity::m_Position;
	CVector3 LineDirection = m_Direction;

	float PlaneD = _pPlane->GetD();
	CVector3 PlaneNormal = _pPlane->GetNormal();
	PlaneNormal.Normalise();

	float fImpactTime = 0.0f;
	fImpactTime  = PlaneD;
	fImpactTime -= CVector3::Dot(LinePosition, PlaneNormal);
	fImpactTime /= CVector3::Dot(LineDirection, PlaneNormal);

	if (fImpactTime > 0.0f)
	{
		float fHalfPlaneLength = _pPlane->GetLength() / 2.0f;

		CVector3 DifferenceLinePlane;
		CVector3 CollisionPosition = LineDirection;
		CollisionPosition.Scale(fImpactTime);
		CVector3::Add(CollisionPosition, LinePosition, CollisionPosition);
		CVector3::Minus(CollisionPosition, _pPlane->GetMiddlePoint(), DifferenceLinePlane);

		float fDistance = CVector3::GetMagnitude(DifferenceLinePlane);

		if (fDistance <= fHalfPlaneLength)
		{
			_fImpactTime = fImpactTime;

			return (true);
		}
	}

	return (false);
}

bool
CLine::IsGoingToCollideSphere(CSphere* _pSphere, float _fDeltaTick, float& _fImpactTime)
{
	CVector3 LinePosition  = CEntity::m_Position;
	CVector3 LineDirection = m_Direction;

	CVector3 SpherePosition = _pSphere->GetPosition();
	float fSphereRadius = _pSphere->GetRadius() * 2.0f;

	CVector3 e; // e . d
	CVector3::Minus(SpherePosition, LinePosition, e);
	
	float a = CVector3::Dot(e, LineDirection);

	float e2 = CVector3::Dot(e, e);

	float fSquareRoot = pow(fSphereRadius, 2.0f) - e2 + pow(a, 2.0f);

	if (fSquareRoot > 0.0f)
	{
		float f = sqrt(fSquareRoot);

		float fImpactTime = a - f;
		
		if (fImpactTime > 0.0f)
		{

			_fImpactTime = fImpactTime;

			return (true);
		}
	}

	return (false);
}