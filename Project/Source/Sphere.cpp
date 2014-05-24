//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Sphere.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cmath>

// Local Includes

// Framework

// Core

// Scene
#include "Plane.h"

// This Include
#include "Sphere.h"

// Static Variables

// Static Function Prototypes

// Implementation

CSphere::CSphere()
: m_fRadius(0.0f)
{
	//Empty
}

CSphere::~CSphere()
{
	//Empty
}

bool
CSphere::Initialise()
{
	CEntity::Initialise();

	return (true);
}

bool
CSphere::Deinitialise()
{
	CEntity::Deinitialise();

	return (true);
}

void
CSphere::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}

void
CSphere::Draw()
{
	CEntity::Draw();
}

void
CSphere::ReflectAgainstPlane(CPlane* _pPlane)
{
	CVector3 PlaneNormal = _pPlane->GetNormal();
	PlaneNormal.Normalise();

	CVector3 SphereResultantVelocity;

	float fScale = 2 * CVector3::Dot(CEntity::m_Velocity, PlaneNormal);

	CVector3 ScaledNormal = PlaneNormal;
	ScaledNormal.Scale(fScale);

	CVector3::Minus(CEntity::m_Velocity, ScaledNormal, SphereResultantVelocity);

	SetVelocity(SphereResultantVelocity);
}

void
CSphere::ReflectAgainstSphere(CSphere* _pSphere)
{
	CVector3 SpherePosition = _pSphere->GetPosition();
	CVector3 SphereVelocity = _pSphere->GetVelocity();
	float SphereMass = _pSphere->GetMass();

	CVector3 n;
	CVector3::Minus(CEntity::m_Position, SpherePosition, n);
	n.Normalise();

	float a1 = CVector3::Dot(CEntity::m_Velocity, n);
	float a2 = CVector3::Dot(SphereVelocity, n);

	float optimizedP = (2.0f * (a1 - a2)) / (m_fMass + SphereMass);

	n.Scale(SphereMass);

	CEntity::SetVelocity(X, CEntity::m_Velocity[X] - optimizedP * n[X] );
	CEntity::SetVelocity(Y, CEntity::m_Velocity[Y] - optimizedP * n[Y] );
	CEntity::SetVelocity(Z, CEntity::m_Velocity[Z] - optimizedP * n[Z] );

	_pSphere->SetVelocity(X, SphereVelocity[X] + optimizedP * n[X] );
	_pSphere->SetVelocity(Y, SphereVelocity[Y] + optimizedP * n[Y] );
	_pSphere->SetVelocity(Z, SphereVelocity[Z] + optimizedP * n[Z] );
}

bool
CSphere::IsGoingToCollidePlane(CPlane* _pPlane, float _fDeltaTick, float& _fImpactTime)
{
	CVector3 PlaneStartPoint = _pPlane->GetStartPoint();
	CVector3 PlaneEndPoint = _pPlane->GetStartPoint();
	CVector3 PlaneNormal = _pPlane->GetNormal();
	PlaneNormal.Normalise();

	float fPlaneD = _pPlane->GetD();

	float fImpactTime = 0.0f;
	fImpactTime  = fPlaneD;
	fImpactTime -= CVector3::Dot(CEntity::m_Position, PlaneNormal);
	fImpactTime += m_fRadius;
	fImpactTime /= CVector3::Dot(CEntity::m_Velocity, PlaneNormal);

	if (fImpactTime <= _fDeltaTick && fImpactTime > 0.0f)
	{
		float fHalfPlaneLength = _pPlane->GetLength() / 2.0f;

		CVector3 DifferenceSpherePlane;
		CVector3::Minus(CEntity::m_Position, _pPlane->GetMiddlePoint(), DifferenceSpherePlane);

		float fDistance = CVector3::GetMagnitude(DifferenceSpherePlane);

		float D = CVector3::Dot(PlaneNormal, CEntity::m_Position) - fPlaneD;

		if (fDistance <= fHalfPlaneLength + m_fRadius +0.1f && D >= m_fRadius)
		{
			_fImpactTime = fImpactTime;

			return (true);
		}
	}

	return (false);
}

bool
CSphere::IsGoingToCollideSphere(CSphere* _pSphere, float _fDeltaTick, float& _fImpactTime)
{
	CVector3 Sphere2Position = _pSphere->GetPosition();
	CVector3 Sphere2Velocity = _pSphere->GetVelocity();
	float Sphere2Radius = _pSphere->GetRadius();

	CVector3 RelativeVelocity;
	CVector3 RelativeVelocityNormalized;
	CVector3::Minus(Sphere2Velocity, CEntity::m_Velocity, RelativeVelocity);
	CVector3::Normalise(RelativeVelocity, RelativeVelocityNormalized);

	CVector3 RelativePosition;
	CVector3::Minus(Sphere2Position, CEntity::m_Position, RelativePosition);

	float fPositionDotVelocity = CVector3::Dot(RelativePosition, RelativeVelocityNormalized);
	float fPositionDotVelocitySquared = fPositionDotVelocity * fPositionDotVelocity;
	float fTotalRadiusSquared = pow(m_fRadius + Sphere2Radius, 2.0f);
	float fPositionDotPosition = CVector3::Dot(RelativePosition, RelativePosition);

	float fRoot = sqrt(fPositionDotVelocitySquared +
					   fTotalRadiusSquared - 
					   fPositionDotPosition);

	float fImpactTime1 = fPositionDotVelocity + fRoot;
	float fImpactTime2 = fPositionDotVelocity - fRoot;

	float fRelativeVelocityMagnitude = CVector3::GetMagnitude(RelativeVelocity);

	float fImpactTime = 0.0f;
	if (fImpactTime1 < fImpactTime2)
	{
		fImpactTime = fImpactTime2 / fRelativeVelocityMagnitude;
	}
	else
	{
		fImpactTime = fImpactTime1 / fRelativeVelocityMagnitude;
	}

	if (fImpactTime >= _fDeltaTick * -1.0f && fImpactTime < 0.0f)
	{
		_fImpactTime = abs(fImpactTime);

		return (true);
	}

	return (false);
}