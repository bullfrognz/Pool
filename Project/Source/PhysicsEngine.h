//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   PhysicsEngine.h
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_PHYSICSENGINE_H__
#define __IGFEB11_IG220_PHYSICSENGINE_H__

// Library Includes
#include <vector>
#include <map>

// Local Includes

// Types

// Constants

// Prototypes
class CSphere;
class CPlane;
class CLogManager;

class CPhysicsEngine
{
	// Member Functions
public:
	 CPhysicsEngine();
	~CPhysicsEngine();

	bool Initialise();
	bool Deinitialise();
	void Process(float _fDeltaTick);
	void Draw();

	void ProcessSpheres(float _fDeltaTick);
	void ProcessSpheresDeltaTick();
	void AddSphereDeltatick(CSphere* _pSphere, float _fDeltaTick);

	void GetLowestImpactTimeSpherePlane(CSphere* _pSphere, float _fDeltaTick, CPlane*& _pImpactPlane ,float& _fImpactTime);
	void GetLowestImpactTimeSphereSphere(CSphere* _pSphere, float _fDeltaTick, CSphere*& _pImpactSphere, float& _fImpactTime);

	bool IsSpherePlaneGoingToCollide(CSphere* _pSphere, CPlane* _pPlane, float _fDeltaTick, float& _fImpactTime);
	bool IsSphereSphereGoingToCollide(CSphere* _pSphere1, CSphere* _pSphere2, float _fDeltaTick, float& _fImpactTime);

	void ReflectSphereSphere(CSphere* _pSphere1, CSphere* _pSphere2);
	void ReflectSpherePlane(CSphere* _pSphere, CPlane* _pPlane);

	void RemoveSphere(CSphere* _pSphere);
	void RemovePlane(CPlane* _pPlane);

	// Member Inline Functions
	inline void IncludeSphere(CSphere* _pSphere);
	inline void IncludePlane(CPlane* _pPlane);

	inline void SetLogManager(CLogManager* _pLogManager);

protected:

private:

	// Member Variables
public:

protected:
	std::vector<CSphere*> m_vecSpheres;
	std::vector<CPlane*> m_vecPlanes;

	std::map<CSphere*, float> m_mapSphereDeltaTick;

	CLogManager* m_pLogManager;

private:

};

#include "PhysicsEngine.inl"

#endif // __IGFEB11_IG220_PHYSICSENGINE_H__