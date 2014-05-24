//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   PhysicsEngine.inl
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// Framework

// Core

// Content

// Static Variables

// Static Function Prototypes

// Implementation

void
CPhysicsEngine::IncludeSphere(CSphere* _pSphere)
{
	m_vecSpheres.push_back(_pSphere);
	m_mapSphereDeltaTick.insert( std::pair<CSphere*, float>(_pSphere, 0.0f) );
}

void
CPhysicsEngine::IncludePlane(CPlane* _pPlane)
{
	m_vecPlanes.push_back(_pPlane);
}

void
CPhysicsEngine::SetLogManager(CLogManager* _pLogManager)
{
	m_pLogManager = _pLogManager;
}