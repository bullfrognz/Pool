//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   PhysicsEngine.cpp
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cmath>

// Local Includes

// Framework
#include "LogManager.h"

// Core
#include "Sphere.h"
#include "Plane.h"

// Content

// This Include
#include "PhysicsEngine.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPhysicsEngine::CPhysicsEngine()
{
	//Empty
}

CPhysicsEngine::~CPhysicsEngine()
{
	//Empty
}

bool
CPhysicsEngine::Initialise()
{
	//Empty


	return (true);
}

bool
CPhysicsEngine::Deinitialise()
{
	//Empty

	return (true);
}

void
CPhysicsEngine::Process(float _fDeltaTick)
{
	ProcessSpheres(_fDeltaTick);
}

void
CPhysicsEngine::Draw()
{
	//Emtpy
}

void
CPhysicsEngine::ProcessSpheresDeltaTick()
{
	std::map<CSphere*, float>::iterator IterDeltaTick;
	IterDeltaTick = m_mapSphereDeltaTick.begin();

	for (IterDeltaTick; IterDeltaTick != m_mapSphereDeltaTick.end(); ++IterDeltaTick)
	{
		(*IterDeltaTick).first->Process((*IterDeltaTick).second);
	}
}

void
CPhysicsEngine::ProcessSpheres(float _fDeltaTick)
{
	std::vector<CSphere*>::iterator IterSphere;
	float fDeltaTickLeft = _fDeltaTick;
	for (IterSphere = m_vecSpheres.begin(); IterSphere != m_vecSpheres.end();)
	{
		float fLowestImpactTimePlane = 1000.0f;
		float fLowestImpactTimeSphere = 1000.0f;

		// Plane Collision
		CPlane* pCollidedPlane = 0;
		GetLowestImpactTimeSpherePlane((*IterSphere), fDeltaTickLeft, pCollidedPlane, fLowestImpactTimePlane);

		// Sphere Collision
		CSphere* pCollidedSphere = 0;
		GetLowestImpactTimeSphereSphere((*IterSphere), fDeltaTickLeft, pCollidedSphere, fLowestImpactTimeSphere);

		// Collision Processing
		if (pCollidedPlane != 0 || pCollidedSphere != 0)
		{
			float fLowestImpactTime = 0.0f;	
			
			if (fLowestImpactTimePlane < fLowestImpactTimeSphere)
			{
				fDeltaTickLeft -= fLowestImpactTimePlane;
				fLowestImpactTime = floor(fLowestImpactTimePlane * 10000.0f) / 10000.0f;
				(*IterSphere)->Process(fLowestImpactTime);
				ReflectSpherePlane((*IterSphere), pCollidedPlane);

				pCollidedPlane->SetColour(RGB(255,0,0));
			}
			else
			{
				fDeltaTickLeft -= fLowestImpactTimeSphere;
				fLowestImpactTime = floor(fLowestImpactTimeSphere * 10000.0f) / 10000.0f;
				(*IterSphere)->Process(fLowestImpactTime);
				ReflectSphereSphere((*IterSphere), pCollidedSphere);
			}
		}
		else
		{
			fDeltaTickLeft = floor(fDeltaTickLeft * 10000.0f) / 10000.0f;

			(*IterSphere)->Process(fDeltaTickLeft);

			++ IterSphere;
			fDeltaTickLeft = _fDeltaTick;
		}
	}
}

void
CPhysicsEngine::GetLowestImpactTimeSpherePlane(CSphere* _pSphere, float _fDeltaTick, CPlane*& _pImpactPlane ,float& _fLowestImpactTime)
{
	std::vector<CPlane*>::iterator IterPlane;
	IterPlane = m_vecPlanes.begin();

	for (IterPlane; IterPlane != m_vecPlanes.end(); ++IterPlane)
	{
		float fImpactTime = 0.0f;
		bool bResult = IsSpherePlaneGoingToCollide(_pSphere, (*IterPlane), _fDeltaTick, fImpactTime);

		if (bResult == true && fImpactTime < _fLowestImpactTime)
		{
			_pImpactPlane = (*IterPlane);
			_fLowestImpactTime = fImpactTime;
		}
	}
}

void
CPhysicsEngine::GetLowestImpactTimeSphereSphere(CSphere* _pSphere, float _fDeltaTick, CSphere*& _pImpactSphere, float& _fLowestImpactTime)
{
	std::vector<CSphere*>::iterator IterSphere;
	IterSphere = m_vecSpheres.begin();

	for (IterSphere; IterSphere != m_vecSpheres.end(); ++IterSphere)
	{
		float fImpactTime = 0.0f;
		bool bResult = bResult = IsSphereSphereGoingToCollide(_pSphere, (*IterSphere), _fDeltaTick, fImpactTime);

		if (bResult == true && fImpactTime < _fLowestImpactTime)
		{
			_fLowestImpactTime = fImpactTime;
			_pImpactSphere = (*IterSphere);
		}
	}
}

bool
CPhysicsEngine::IsSpherePlaneGoingToCollide(CSphere* _pSphere, CPlane* _pPlane, float _fDeltaTick, float& _fImpactTime)
{
	CVector3 PlaneStartPoint = _pPlane->GetStartPoint();
	CVector3 PlaneEndPoint = _pPlane->GetStartPoint();
	CVector3 PlaneNormal = _pPlane->GetNormal();
	PlaneNormal.Normalise();

	CVector3 SpherePosition = _pSphere->GetPosition();
	CVector3 SphereVelocity = _pSphere->GetVelocity();
	float fSphereRadius = _pSphere->GetRadius();

	float fPlaneD = _pPlane->GetD();

	float fImpactTime = 0.0f;
	fImpactTime  = fPlaneD;
	fImpactTime -= CVector3::Dot(SpherePosition, PlaneNormal);
	fImpactTime += fSphereRadius;
	fImpactTime /= CVector3::Dot(SphereVelocity, PlaneNormal);

	if (fImpactTime <= _fDeltaTick && fImpactTime > 0.0f)
	{
		float fHalfPlaneLength = _pPlane->GetLength() / 2.0f;

		CVector3 DifferenceSpherePlane;
		CVector3::Minus(SpherePosition, _pPlane->GetMiddlePoint(), DifferenceSpherePlane);

		float fDistance = abs(CVector3::GetMagnitude(DifferenceSpherePlane));

		if (fDistance <= fHalfPlaneLength + fSphereRadius + 0.1f)
		{
			_fImpactTime = fImpactTime;

			return (true);
		}
	}

	return (false);
}

bool
CPhysicsEngine::IsSphereSphereGoingToCollide(CSphere* _pSphere1, CSphere* _pSphere2, float _fDeltaTick, float& _fImpactTime)
{
	CVector3 Sphere1Position = _pSphere1->GetPosition();
	CVector3 Sphere1Velocity = _pSphere1->GetVelocity();
	float Sphere1Radius = _pSphere1->GetRadius();

	CVector3 Sphere2Position = _pSphere2->GetPosition();
	CVector3 Sphere2Velocity = _pSphere2->GetVelocity();
	float Sphere2Radius = _pSphere2->GetRadius();

	CVector3 RelativeVelocity;
	CVector3 RelativeVelocityNormalized;
	CVector3::Minus(Sphere2Velocity, Sphere1Velocity, RelativeVelocity);
	CVector3::Normalise(RelativeVelocity, RelativeVelocityNormalized);

	CVector3 RelativePosition;
	CVector3::Minus(Sphere2Position, Sphere1Position, RelativePosition);

	float fPositionDotVelocity = CVector3::Dot(RelativePosition, RelativeVelocityNormalized);
	float fPositionDotVelocitySquared = fPositionDotVelocity * fPositionDotVelocity;
	float fTotalRadiusSquared = pow(Sphere1Radius + Sphere2Radius, 2.0f);
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

void
CPhysicsEngine::ReflectSphereSphere(CSphere* _pSphere1, CSphere* _pSphere2)
{
	CVector3 Sphere1Position = _pSphere1->GetPosition();
	CVector3 Sphere1Velocity = _pSphere1->GetVelocity();
	float Sphere1Radius = _pSphere1->GetRadius();
	float Sphere1Mass = 15;

	CVector3 Sphere2Position = _pSphere2->GetPosition();
	CVector3 Sphere2Velocity = _pSphere2->GetVelocity();
	float Sphere2Radius = _pSphere2->GetRadius();
	float Sphere2Mass = 15;

	CVector3 n;
	CVector3::Minus(Sphere1Position, Sphere2Position, n);
	n.Normalise();

	float a1 = CVector3::Dot(Sphere1Velocity, n);
	float a2 = CVector3::Dot(Sphere2Velocity, n);

	float optimizedP = (2.0f * (a1 - a2)) / (Sphere1Mass + Sphere2Mass);

	n.Scale(Sphere2Mass);

	_pSphere1->SetVelocity(X, Sphere1Velocity[X] - optimizedP * n[X] );
	_pSphere1->SetVelocity(Y, Sphere1Velocity[Y] - optimizedP * n[Y] );
	_pSphere1->SetVelocity(Z, Sphere1Velocity[Z] - optimizedP * n[Z] );

	_pSphere2->SetVelocity(X, Sphere2Velocity[X] + optimizedP * n[X] );
	_pSphere2->SetVelocity(Y, Sphere2Velocity[Y] + optimizedP * n[Y] );
	_pSphere2->SetVelocity(Z, Sphere2Velocity[Z] + optimizedP * n[Z] );
}

void
CPhysicsEngine::ReflectSpherePlane(CSphere* _pSphere, CPlane* _pPlane)
{
	CVector3 PlaneNormal = _pPlane->GetNormal();
	PlaneNormal.Normalise();

	CVector3 SphereVelocity = _pSphere->GetVelocity();
	CVector3 SphereResultantVelocity;

	float fScale = 2 * CVector3::Dot(SphereVelocity, PlaneNormal);

	CVector3 ScaledNormal = PlaneNormal;
	ScaledNormal.Scale(fScale);

	CVector3::Minus(SphereVelocity, ScaledNormal, SphereResultantVelocity);

	_pSphere->SetVelocity(X, SphereResultantVelocity[X]);
	_pSphere->SetVelocity(Y, SphereResultantVelocity[Y]);
	_pSphere->SetVelocity(Z, SphereResultantVelocity[Z]);
}

void
CPhysicsEngine::RemoveSphere(CSphere* _pSphere)
{
	std::vector<CSphere*>::iterator IterSphere;
	IterSphere = m_vecSpheres.begin();

	while (IterSphere != m_vecSpheres.end())
	{
		if ((*IterSphere) == _pSphere)
		{
			m_vecSpheres.erase(IterSphere);
			break;
		}

		++ IterSphere;
	}
}

void
CPhysicsEngine::RemovePlane(CPlane* _pPlane)
{
	std::vector<CPlane*>::iterator IterPlane;
	IterPlane = m_vecPlanes.begin();

	while (IterPlane != m_vecPlanes.end())
	{
		if ((*IterPlane) == _pPlane)
		{
			m_vecPlanes.erase(IterPlane);
			break;
		}

		++ IterPlane;
	}
}